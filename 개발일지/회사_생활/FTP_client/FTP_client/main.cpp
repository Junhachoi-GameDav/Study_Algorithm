// std
#include <iostream>
#include <filesystem>
#include <print>

// tbb
#include <oneapi/tbb/task_group.h>

// 
#include "build_config.h"
#include "signal_receiver.h"
#include "drone.h"

int main()
{
	namespace fs = ::std::filesystem;

	// json
	configuration::read_config();

	// signal 촬영 시작-종료
	signal_receiver& sig = signal_receiver::instance();
	while (sig.acquisition_status.empty())
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	// FTP(드론) 정보 읽기
	std::map<unsigned int, drone> drones;
	for (const configuration::config::_drone& drone_config : target_config.drones)
	{
		const auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = drone_config;
		for (const auto& [received_address, in_acquisition] : sig.acquisition_status)
		{
			if (address.empty() || drones.contains(drone_key))
				continue;

			if (address != received_address)
				continue;

			// 드론 객체 생성 후 접속됨을 알림
			drones.emplace(drone_key, drone_config);
			std::println("drone {} has emplaced : {}\n", drone_key, address);
		}
	}

	// 경로 읽고 다운로드
	tbb::task_group tg;
	//tbb::concurrent_vector<fs::path> images;
	for (auto& [key, drone] : drones)
	{
		if (key != 0)
			continue;

		tg.run([&key, &drone]()->void
			{
				while (not drone.file_get_mode.done())
				{
					drone.file_get_mode.resume();

					const fs::path image_path = std::move(drone.file_get_mode.handle.promise().value);

					if (image_path.empty())
					{
						std::println("\nimage_path is empty......");
						continue;
					}
				 }
			});
	}
	tg.wait();
	std::println("test done!!");
	return 0;
}