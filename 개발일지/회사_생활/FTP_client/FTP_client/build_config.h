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
		std::filesystem::path dem_directory;
		struct postgresql_dem_table
		{
			std::string dbname;
			std::string username;
			std::string password;
			std::string hostaddr;
			unsigned short port;
		} dem_table;
		std::filesystem::path file_saving_directory;
		struct _drone
		{
			unsigned int drone_key;
			std::string address;
			int port;
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
				double gsd;
				coordinates output_coord;
				std::string output_extension;
				unsigned int save_interval;
			} eo;
			struct _ir
			{
				double gsd;
				coordinates output_coord;
				std::string output_extension;
				unsigned int save_interval;
			} ir;
			struct _odm
			{
				std::string run_ip_eo;
				std::string run_ip_ir;
				std::filesystem::path python_path;
				std::filesystem::path debug_dll_dir;
				std::filesystem::path py_filename;
				std::string function_name;
				bool enable_eo;
				bool enable_ir;
				std::filesystem::path eo_input_dir;
				std::filesystem::path ir_input_dir;
			} odm;
		} mapping;
		struct _web
		{
			std::string uri;
		} web;
	} default_config[]{ config{}, config{}, };

	void read_config();
}
extern configuration::config& target_config;

#endif

#define ADMIN_CHECK
#ifdef ADMIN_CHECK
bool is_running_as_admin();
#endif