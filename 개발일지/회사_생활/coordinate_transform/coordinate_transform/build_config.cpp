#include "build_config.h"
#ifdef CONFIGURATION_JSON

// std
#include <cassert>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>


const configuration::config& target_config = configuration::default_config[0];
namespace configuration
{
	template<typename _Ty>
	concept from_json_callable = requires (const nlohmann::json & j, const std::string & key, _Ty & _arg)
	{
		j.at(key).get_to(_arg);
		//{ j.at(key).get_to(_arg) } -> std::same_as<void>;
		//{ from_json(j, key, _arg) } -> std::same_as<void>;
	};
	
	template<typename _check_type, typename _raw_type>
	concept type_like = requires
	{
		std::is_object_v<_raw_type>;
		not std::is_pointer_v<_raw_type>;
		not std::is_reference_v<_raw_type>;
		std::same_as<std::remove_cvref_t<_check_type>, _raw_type>;
	};

	template<typename _Ty>
	concept string_like = requires
	{
		std::is_same_v<_Ty, const char*> or std::is_same_v<std::remove_cvref_t<_Ty>, std::string> or std::is_same_v<std::remove_cvref_t<_Ty>, std::string_view>;
	};

	//template<typename _Ty>
	void get_json_element(const type_like<nlohmann::json> auto& j, string_like auto&& key, from_json_callable auto&& value)
	{
		try
		{
			j.at(key).get_to(value);
		}
		catch (const std::string& errored_element)
		{
			throw std::format("{}.{}", key, errored_element);
		}
		catch ([[maybe_unused]] nlohmann::json::exception& e)
		{
			throw std::format("{}", key);
		}
	}
	void from_json(const nlohmann::json& j, std::filesystem::path& p)
	{
		p = j.get<std::string>();
	}

	void from_json(const nlohmann::json& j, config::postgresql_dem_table& dem_table)
	{
		auto& [dbname, username, password, hostaddr, port] = dem_table;
		get_json_element(j, "dbname",   dbname);
		get_json_element(j, "username", username);
		get_json_element(j, "password", password);
		get_json_element(j, "hostaddr", hostaddr);
		get_json_element(j, "port",     port);
		
		assert(not dbname.empty());
		assert(not username.empty());
		assert(not password.empty());
		assert(not hostaddr.empty());
		// 포트 검사도 해야 하나?
		//assert(port != 0);
	}

	void from_json(const nlohmann::json& j, config::_drone& d)
	{
		auto& [drone_key, address, port, id, pw, iop_eo_path, iop_ir_path, syscal_path] = d;
		
		drone_key = static_cast<unsigned int>(j.at("drone_key").get<uint64_t>());
		get_json_element(j, "address",     address);
		get_json_element(j, "port",        port);
		get_json_element(j, "id",          id);
		get_json_element(j, "pw",          pw);
		get_json_element(j, "iop_eo_path", iop_eo_path);
		get_json_element(j, "iop_ir_path", iop_ir_path);
		get_json_element(j, "syscal_path", syscal_path);
	}

	void from_json(const nlohmann::json& j, config::_mapping::_eo& eo)
	{
		auto& [gsd, output_coord, output_extension, save_interval] = eo;

		get_json_element(j, "gsd", gsd);

		/*static const std::map<std::string, coordinates> coord_map
		{
			{ "3857", coordinates::c3857 },
			{ "4326", coordinates::c4326 },
			{ "5179", coordinates::c5179 },
			{ "5186", coordinates::c5186 },
			{ "5187", coordinates::c5187 },
			{ "5714", coordinates::c5714 },
			{ "32652", coordinates::c32652 }
		};*/
		//output_coord = coord_map.at(j.at("output_coord").get<std::string>());
		get_json_element(j, "output_coord", output_coord);
		//std::string coord_string;
		//output_coord = coord_map.at(coord_string);

		get_json_element(j, "output_extension", output_extension);
		get_json_element(j, "save_interval", save_interval);

		assert(not output_extension.empty() and output_extension[0] == '.');
	}

	void from_json(const nlohmann::json& j, config::_mapping::_ir& ir)
	{
		auto& [gsd, output_coord, output_extension, save_interval] = ir;

		get_json_element(j, "gsd", gsd);

		/*static const std::map<std::string, coordinates> coord_map
		{
			{ "3857", coordinates::c3857 },
			{ "4326", coordinates::c4326 },
			{ "5179", coordinates::c5179 },
			{ "5186", coordinates::c5186 },
			{ "5187", coordinates::c5187 },
			{ "5714", coordinates::c5714 },
			{ "32652", coordinates::c32652 }
		};*/
		//output_coord = coord_map.at(j.at("output_coord").get<std::string>());
		//std::string coord_string;
		//output_coord = coord_map.at(coord_string);
		get_json_element(j, "output_coord", output_coord);
		get_json_element(j, "output_extension", output_extension);
		get_json_element(j, "save_interval", save_interval);

		assert(not output_extension.empty() and output_extension[0] == '.');
	}

	void from_json(const nlohmann::json& j, config::_mapping::_odm& odm)
	{
		auto& [run_ip_eo, run_ip_ir, enable_eo, enable_ir] = odm;

		get_json_element(j, "run_ip_eo", run_ip_eo);
		get_json_element(j, "run_ip_ir", run_ip_ir);
		get_json_element(j, "enable_eo", enable_eo);
		get_json_element(j, "enable_ir", enable_ir);

		assert(not run_ip_eo.empty());
		assert(not run_ip_ir.empty());
	}

	void from_json(const nlohmann::json& j, config::_mapping& m)
	{
		auto& [eo, ir, odm, p_path] = m;

		get_json_element(j, "eo",  eo);
		get_json_element(j, "ir",  ir);
		get_json_element(j, "odm", odm);
		get_json_element(j, "proj_data_path", p_path);
	}

	void from_json(const nlohmann::json& j, config::_web& w)
	{
		get_json_element(j, "uri", w.uri);
		assert(not w.uri.empty());
	}

	void from_json(const nlohmann::json& j, config& c)
	{
		auto& [sig_recv_host_address, dem_table, file_saving_dir, drones, mapping, web] = c;

		get_json_element(j, "sig_recv_host_address", sig_recv_host_address);
		get_json_element(j, "postgresql_dem_table",  dem_table);	
		get_json_element(j, "file_saving_dir",       file_saving_dir);
		get_json_element(j, "drones",                drones);
		get_json_element(j, "mapping",               mapping);
		get_json_element(j, "web",                   web);
	}
}

void configuration::read_config()
{
	const std::filesystem::path config_file(std::filesystem::current_path() / "configuration.json");
	assert(std::filesystem::exists(config_file));
	nlohmann::json j;
	try
	{
		j = nlohmann::json::parse(std::ifstream(config_file));
	}
	catch ([[maybe_unused]] nlohmann::json::exception& e)
	{
		throw "'configuration.json'.'cannot parse the file, it's either file does not exist or json is possibly malformat.'\n";
	}
	try
	{
		get_json_element(j, "config", const_cast<configuration::config&>(target_config));
	}
	catch(std::string& errored_element)
	{
		throw std::exception(std::format("'configuration.json'.'some required element {} doesn't exists.'\n", errored_element).c_str());
	}
}

#endif



#ifdef ADMIN_CHECK
#ifdef _WIN32
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

void enableANSI()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
		return;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
		return;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
		return;
}

#elif defined(__linux__)
#include <unistd.h>

bool is_running_as_admin()
{
	// check if the effective user ID is 0(root)
	return geteuid() == 0;
}

void enableANSI() {}

#endif
#endif