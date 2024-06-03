#pragma once
// std
#include <filesystem>
#include <array>
#include <string>
#include <locale>
#include <system_error>

//namespace std
//{
//	namespace filesystem
//	{
//		class path;
//	}
//}
// OpenCV
#include <opencv2/core.hpp>

//#include "point_cloud.h"
//#include "dem_manager.h"

//.img 확장자 dem용 v2
class demv2
{
	// DEM 내에서의 좌상단 위치, 일반적으로는 이미지의 상하좌우와 DEM의 북남서동을 맞추기 때문에 지상좌표에서는 일반적으로 (min x, max y) 이다.
	cv::Point2d left_top;

	// 영상좌표 x, y축 변화량(픽셀) 당 DEM x, y축 지상좌표 변화량. 단위는 DEM이 포함하는 좌표계에 달려있다. 보통 미터.
	// left-top이 일반적으로 (min x, max y)라서 delta는 (+, -)인 경우가 많다.
	cv::Point2d delta;

	// 각 x, y 내에서 z축의 높이가 담긴 Mat
	// dem은 이미지이므로 격자화 되어있다. subpixel의 높이는 쌍선형(bilinear) 보간해서 사용한다.
	// x, y 위치는 다음과 같이 계산한다.
	// x = left_top.x + m(horizontal pixel offset) * delta.x
	// y = left_top.y + n(vertical pixel offset) * delta.y
	// z(x, y) = dem_matrix(m, n)
	mutable cv::Mat dem_matrix;

	// dem_matrix의 크기, 별도로 갖고 있는 이유는 관리하는 DEM이 많아지면서 메모리 용량이 넉넉치 않아서
	// dem_matrix를 잠시 내려도 영역을 검색할 수는 있도록 하기 위함.
	cv::Size dem_size;

	// 메모리 관리를 위해 임시로 내려야 할 때 파일을 찾기 위한 경로(unload()/reload() 함수 참고)
	// dem_matrix.release() 하여 메모리를 줄이되 영역을 검색할 수는 있도록 사이즈는 별도로 갖고 있는다.
	std::filesystem::path abs_path;

	// internal ctors
	demv2() = default;
	//demv2(const double& dx, const double& dy, const cv::Mat& dem_mat);

public:
	// public ctors
	demv2(const std::filesystem::path& dem_file);

	// copyable
	demv2(const demv2&) = default;
	demv2& operator=(const demv2&) = default;

	// movable
	demv2(demv2&&) = default;
	demv2& operator=(demv2&&) = default;

	// default dtor
	~demv2() = default;

	// 영역 내 해당 좌표 포함 여부
	// 정확하게 그 값이 없더라도 DEM이 포함하는 영역 내에 있는지 판단한다.
	bool contains(const double& x, const double& y) const;

	// 해당 좌표 높이 찾기
	// 대부분 해당 좌표를 정확하게 담고 있지 않기 때문에 정확한 높이값은 없다.
	// 대신 최인접 4개 점을 찾아 쌍선형 보간(bilinear interpolation) 한다.
	// 영역 내에 없으면(contains(x, y) == false) nan을 리턴한다.
	double find_ground_height(const double& x, const double& y) const;

	// 메모리 관리를 위해 용량이 상대적으로 큰 dem_matrix를 언로드/리로드 하는 함수
	// 메모리 사용량과 대규모 File IO로 인한 성능 하락 간 타협점을 찾아 적절히 올리고 내릴 것 
	void unload() const;
	void reload() const;

	friend class dem_manager;
};
