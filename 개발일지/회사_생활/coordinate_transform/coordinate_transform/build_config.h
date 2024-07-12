#pragma once
#ifndef CONFIGURATION_JSON
#define CONFIGURATION_JSON
#include <filesystem>
#include <string>

#include "coordinate_transform.hpp"

namespace configuration
{
	static struct config
	{
		std::string sig_recv_host_address;
		//std::filesystem::path dem_directory;
		struct postgresql_dem_table
		{
			std::string dbname;
			std::string username;
			std::string password;
			std::string hostaddr;
			unsigned short port = 0;
		} dem_table;
		std::filesystem::path file_saving_directory;
		struct _drone
		{
			unsigned int drone_key = 0;
			std::string address;
			int port = 0;
			std::string id;
			std::string pw;
			std::filesystem::path iop_eo_path;
			std::filesystem::path iop_ir_path;
			std::filesystem::path syscal_path;
		} drones[4]{};
		struct _mapping
		{
			struct _eo
			{
				double gsd = 0.0;
				std::string output_coord = "4326";
				std::string output_extension;
				unsigned int save_interval = 0;
			} eo;
			struct _ir
			{
				double gsd = 0.0;
				std::string output_coord = "4326";
				std::string output_extension;
				unsigned int save_interval = 0;
			} ir;
			struct _odm
			{
				std::string run_ip_eo;
				std::string run_ip_ir;
				//std::filesystem::path python_path;
				//std::filesystem::path debug_dll_dir;
				//std::filesystem::path py_filename;
				//std::string function_name;
				bool enable_eo = true;
				bool enable_ir = true;
				//std::filesystem::path eo_input_dir;
				//std::filesystem::path ir_input_dir;
			} odm;
			std::filesystem::path proj_data_path;
		} mapping;
		struct _web
		{
			std::string uri;
		} web;
	} default_config[]{ config{}, config{}, };

	void read_config();
}
extern const configuration::config& target_config;

#endif

#define ADMIN_CHECK
#ifdef ADMIN_CHECK
bool is_running_as_admin();
#ifdef _WIN32
void enableANSI();
#endif
#endif