import io
import json
import os
import time
import requests
import zipfile

#BASE_URL = "http://175.116.181.25:8000/api"
BASE_URL = ""

#도커 환경변수로 받기    
def get_pc_ip(env_var):
    pc_ip =  os.getenv(env_var)
    return "http://" + pc_ip + ":8000/api"

def login_and_get_token() -> str:

    res = requests.post(f"{BASE_URL}/token-auth/", data = { "username" : "admin", "password" : "admin" }).json()
    return res["token"]

def read_images_with_odm_format(image_paths : list[str]) -> list[tuple[str, tuple[any, io.BufferedReader, str]]]:
    images = []
    for image_file in image_paths:
        images.append(("images", (os.path.basename(image_file), open(image_file, "rb"), "image/jpg")))
    
    return images

def make_odm_project(headers : dict[str, str], project_name : str) -> str:
    # 프로젝트 목록을 가져옵니다.
    response = requests.get(f"{BASE_URL}/projects/", headers=headers)
    projects = response.json()

    # 프로젝트 목록에서 동일한 이름의 프로젝트를 찾음
    for project in projects:
        if project["name"] == project_name:
            return project["id"]
    
    # 동일한 이름의 프로젝트가 없으면 새로운 프로젝트를 생성
    response = requests.post(f"{BASE_URL}/projects/", headers=headers, data={"name": project_name})
    project_id = response.json()["id"]

    return project_id
    
def run_a_task(pid : str, headers : dict[str, str], images : list[any], options : str):
    res = requests.post(f"{BASE_URL}/projects/{pid}/tasks/", 
                headers = headers,
                files = images,
                data = { "options": options, "resize_to": 2048 }).json()
    return res["id"]
    
def get_task_status(pid : str, tid : str, headers : dict[str, str]) -> tuple[int, float, float, float, list[str]]:
    res = requests.get(f"{BASE_URL}/projects/{pid}/tasks/{tid}/", headers = headers).json()
    return (res["status"], res['upload_progress'], res['resize_progress'], res['running_progress'], res['available_assets'])

def download_asset(pid : str, tid : str, headers : dict[str, str], output_dir : str, asset_name : str) -> str:
    res = requests.get(f"{BASE_URL}/projects/{pid}/tasks/{tid}/download/{asset_name}", headers = headers, stream = True)
    
    filename = f"{output_dir}/{asset_name}"
    with open(filename, 'wb') as f:
        for chunk in res.iter_content(chunk_size = 1024): 
            if chunk:
                f.write(chunk)
                
    return filename

def wait_task(pid : str, tid : str, headers : dict[str, str], output_dir : str, target_assets : set[str]) -> list[str]:
    class status_codes:
        QUEUED = 10
        RUNNING = 20
        FAILED = 30
        COMPLETED = 40
        CANCELED = 50
    status_strings = {
        None : "not ready",
        
        status_codes.QUEUED : "queued",
        status_codes.RUNNING : "running",
        status_codes.FAILED : "failed",
        status_codes.COMPLETED : "completed",
        status_codes.CANCELED : "canceled",
    }
    
    downloaded_assets_list = []

    def print_progress_bar(progress: float, total: int = 100, length: int = 50):
        progress_int = int(progress)
        filled_length = int(length * progress_int // total)
        bar = '█' * filled_length + '-' * (length - filled_length)
        print(f'\rProgress: |{bar}| {progress_int}%', end='', flush=True)
        if progress_int == total:
            print()

    while True:
        (status, upload_progress, resize_progress, running_progress, available_assets) = get_task_status(pid, tid, headers)
        
        progress_percentage = running_progress * 100
        print_progress_bar(progress_percentage)
        
        if status == status_codes.COMPLETED:
            print(available_assets)
            for asset in available_assets:
                if target_assets.__contains__(asset):
                    downloaded_assets_list.append(download_asset(pid, tid, headers, output_dir, asset))
                    target_assets.discard(asset)
            
        if (status == status_codes.COMPLETED or status == status_codes.FAILED or status == status_codes.CANCELED):
            break
        
        time.sleep(1.0)
        
    return downloaded_assets_list

def call_odm(image_paths : list[str], output_dir : str) -> list[str]:
    def option_as_json(key : str, value : any)->dict[str, any]:
        return {"name": key, "value": value}
    
    options = json.dumps([
        option_as_json("3d-tiles", True),
        option_as_json("dsm", True),
        option_as_json("texturing-skip-global-seam-leveling", True),
        option_as_json("texturing-skip-local-seam-leveling", True),
        option_as_json("use-exif", True),
        option_as_json("use-hybrid-bundle-adjustment", True),
        option_as_json("use-opensfm-pointcloud", True)
    ])
    
    images = read_images_with_odm_format(image_paths)
    
    ACCESS_TOKEN = login_and_get_token()
    DEFAULT_HEADERS = { "Authorization": F"JWT {ACCESS_TOKEN}"}
    print(f"login success, access token : {ACCESS_TOKEN}")
    
    PROJECT_ID = make_odm_project(DEFAULT_HEADERS, f"python odm call")
    print(f"pid : {PROJECT_ID}")
    
    TASK_ID = run_a_task(PROJECT_ID, DEFAULT_HEADERS, images, options)
    print(f"tid : {TASK_ID}")
    
    print(f"ODM is working~~")
    downloaded = wait_task(PROJECT_ID, TASK_ID, DEFAULT_HEADERS, output_dir, { "orthophoto.tif", "3d_tiles_pointcloud.zip" })
    
    # images
    for (_, (_, buffer, _)) in images:
        buffer.close()

    print(f"Doing unzip~~")
    # _tiles_pointcloud.zip
    for i, filename in enumerate(downloaded):
        if (filename.endswith(".zip")):
            dir_name = filename[:len(filename) - 4]
            os.makedirs(f"{dir_name}", exist_ok = True)
            with zipfile.ZipFile(f"{filename}", 'r') as zf:
                zf.extractall(f"{dir_name}")
            downloaded[i] = dir_name
            #zip 삭제
            os.remove(filename)
            requests.delete(f"{BASE_URL}/projects/{PROJECT_ID}", headers = DEFAULT_HEADERS)

    return downloaded

def get_image_paths(directory: str) -> list[str]:
    # 디렉토리 내의 모든 파일을 읽어와서 .jpg 파일만 필터링
    return [os.path.join(directory, file) for file in os.listdir(directory) if file.lower().endswith(".jpg")]

if __name__ == "__main__":
    # 이미지 파일이 저장된 디렉토리 경로
    #image_directory = r"C:\Users\user\Downloads\input"
    #output_directory = r"C:\Users\user\Downloads\eo_output"
    #config_dir = r"C:\Users\user\Downloads\test_config"
    image_directory = r"/photos"
    output_directory = r"/output"
    #config_dir = r"/config" 

    #도커 환경변수를 읽음
    BASE_URL = get_pc_ip('PC_IP')

    # 디렉토리 내의 이미지 파일 경로를 읽어옴
    image_paths = get_image_paths(image_directory)
    
    # call_odm 함수 호출하여 작업 수행
    downloaded_files = call_odm(image_paths, output_directory)
    print("Downloaded files:", downloaded_files)