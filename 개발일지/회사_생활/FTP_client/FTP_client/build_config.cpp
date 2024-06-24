#include "build_config.h"
#ifdef CONFIGURATION_JSON

// std
#include <cassert>
#include <fstream>

#include <nlohmann/json.hpp>


configuration::config& target_config = configuration::default_config[0];
namespace configuration
{
	void from_json(const nlohmann::json& j, std::filesystem::path& p)
	{
		p = j.get<std::string>();
	}

	void from_json(const nlohmann::json& j, config::postgresql_dem_table& dem_table)
	{
		auto& [dbname, username, password, hostaddr, port] = dem_table;
		j.at("dbname").get_to(dbname);
		assert(not dbname.empty());
		
		j.at("username").get_to(username);
		assert(not username.empty());
		
		j.at("password").get_to(password);
		assert(not password.empty());

		j.at("hostaddr").get_to(hostaddr);
		assert(not hostaddr.empty());

		j.at("port").get_to(port);
		// 포트 검사도 해야 하나?
		//assert(port != 0);

	}

	void from_json(const nlohmann::json& j, config::_drone& d)
	{
		auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = d;
		
		drone_key = static_cast<unsigned int>(j.at("drone_key").get<uint64_t>());
		j.at("address").get_to(address);
		j.at("port").get_to(port);
		j.at("id").get_to(id);
		j.at("pw").get_to(pw);
		j.at("iop_eo_path").get_to(iop_eo_path);
		j.at("iop_ir_path").get_to(iop_ir_path);
		j.at("syscal_path").get_to(syscal_path);
	}

	void from_json(const nlohmann::json& j, config::_mapping::_eo& eo)
	{
		auto& [gsd, output_coord, output_extension, save_interval] = eo;

		j.at("gsd").get_to(gsd);

		static const std::map<std::string, coordinates> coord_map
		{
			{ "3857", coordinates::c3857 },
			{ "4326", coordinates::c4326 },
			{ "5179", coordinates::c5179 },
			{ "5186", coordinates::c5186 },
			{ "5187", coordinates::c5187 },
			{ "5714", coordinates::c5714 },
			{ "32652", coordinates::c32652 }
		};
		output_coord = coord_map.at(j.at("output_coord").get<std::string>());
		//j.at("output_coord").get_to(output_coord);
		//std::string coord_string;
		//output_coord = coord_map.at(coord_string);

		j.at("output_extension").get_to(output_extension);
		assert(not output_extension.empty() and output_extension[0] == '.');

		j.at("save_interval").get_to(save_interval);
	}

	void from_json(const nlohmann::json& j, config::_mapping::_ir& ir)
	{
		auto& [gsd, output_coord, output_extension, save_interval] = ir;

		j.at("gsd").get_to(gsd);

		static const std::map<std::string, coordinates> coord_map
		{
			{ "3857", coordinates::c3857 },
			{ "4326", coordinates::c4326 },
			{ "5179", coordinates::c5179 },
			{ "5186", coordinates::c5186 },
			{ "5187", coordinates::c5187 },
			{ "5714", coordinates::c5714 },
			{ "32652", coordinates::c32652 }
		};
		output_coord = coord_map.at(j.at("output_coord").get<std::string>());
		//std::string coord_string;
		//output_coord = coord_map.at(coord_string);

		j.at("output_extension").get_to(output_extension);
		assert(not output_extension.empty() and output_extension[0] == '.');

		j.at("save_interval").get_to(save_interval);
	}

	void from_json(const nlohmann::json& j, config::_mapping::_odm& odm)
	{
		auto& [run_ip_eo, run_ip_ir, python_path, debug_dll_dir, py_filename, function_name, enable_eo, enable_ir, eo_input_dir, ir_input_dir] = odm;
		j.at("run_ip_eo").get_to(run_ip_eo);
		assert(not run_ip_eo.empty());
		j.at("run_ip_ir").get_to(run_ip_ir);
		assert(not run_ip_ir.empty());
		j.at("python_path").get_to(python_path);
		j.at("debug_dll_dir").get_to(debug_dll_dir);
		j.at("py_filename").get_to(py_filename);
		j.at("function_name").get_to(function_name);
		j.at("enable_eo").get_to(enable_eo);
		j.at("enable_ir").get_to(enable_ir);
		j.at("eo_input_dir").get_to(eo_input_dir);
		j.at("ir_input_dir").get_to(ir_input_dir);
	}

	void from_json(const nlohmann::json& j, config::_mapping& m)
	{
		auto& [eo, ir, odm] = m;
		j.at("eo").get_to(eo);
		j.at("ir").get_to(ir);
		j.at("odm").get_to(odm);
	}

	void from_json(const nlohmann::json& j, config::_web& w)
	{
		j.at("uri").get_to(w.uri);
		assert(not w.uri.empty());

	}

	void from_json(const nlohmann::json& j, config& c)
	{
		auto& [sig_recv_host_address, dem_dir, dem_table, file_saving_dir, drones, mapping, web] = c;

		j.at("sig_recv_host_address").get_to(sig_recv_host_address);
		assert(not sig_recv_host_address.empty());
		j.at("dem_dir").get_to(dem_dir);
		j.at("postgresql_dem_table").get_to(dem_table);
		
		j.at("file_saving_dir").get_to(file_saving_dir);
		j.at("drones").get_to(drones);

		//for (auto& drone : drones)
		//	drone.output_dir = file_saving_dir / drone.output_dir;

		j.at("mapping").get_to(mapping);
		j.at("web").get_to(web);
	}
}

void configuration::read_config()
{
	const std::filesystem::path config_file(std::filesystem::current_path() / "configuration.json");
	assert(std::filesystem::exists(config_file));
	
	nlohmann::json j = nlohmann::json::parse(std::ifstream(config_file));
	
	j.at("config").get_to(target_config);
}

#endif



#ifdef ADMIN_CHECK
//#include <winnt.h>
//#include <winbase.h>
#include <windows.h>

bool is_running_as_admin()
{
	BOOL fIsRunAsAdmin = FALSE;
	PSID pAdministratorsGroup = NULL;

	// Allocate and initialize a SID of the administrators group.
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (not AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdministratorsGroup))
		return false;

	// Determine whether the SID of administrators group is enabled in 
	// the primary access token of the process.
	if (not CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
		fIsRunAsAdmin = FALSE;

	// Free the allocated SID.
	if (pAdministratorsGroup)
		FreeSid(pAdministratorsGroup);

	return fIsRunAsAdmin;
}
#endif