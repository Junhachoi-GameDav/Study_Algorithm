// std
#include <iostream>
#include <filesystem>
#include <string>
#include <format>

// this header
#include "drone_db_connection.h"
#include "build_config.h"

const auto& [dbname, username, password, hostaddr, port] = target_config.dem_table;

// origin = dbname=FIM 
drone_db_connection::drone_db_connection() : con(std::format("dbname=test user={} password={} hostaddr={} port={}", username, password, hostaddr, port)), w(std::make_unique<pqxx::work>(con)), bsmph(1)
{
	std::println("connected DB!!");
	assert(con.is_open());
}


drone_db_connection::~drone_db_connection()
{
	if (con.is_open())
		con.close();
}

void drone_db_connection::insert_query_directory(int idx, const std::filesystem::path& remote_dir, const std::filesystem::path& local_dir) const
{
	semaphore_acq_rel acq_rel(this->bsmph);
	
	const auto result = w->exec_params
	(
		"INSERT INTO remote_table (remote_dir, local_dir) VALUES ($1, $2)",
		remote_dir.generic_string(),
		local_dir.generic_string()
	);

	if (result.inserted_oid() != pqxx::oid_none)
	{
		// error handling process if you need...
	}

	w->commit();
	std::println("INSERT INTO remote_table......");
	w = std::make_unique<pqxx::work>(con);
}

void drone_db_connection::insert_query_file_index(const std::filesystem::path& remote_abs_filename, const std::filesystem::path& local_abs_filename) const
{
	semaphore_acq_rel acq_rel(this->bsmph);
	
	const auto result = w->exec_params
	(
		"INSERT INTO file_index (remote_dir, remote_filename, local_dir, local_filename) VALUES ($1, $2, $3, $4)",
		remote_abs_filename.parent_path().generic_string(),
		remote_abs_filename.filename().generic_string(),
		local_abs_filename.parent_path().generic_string(),
		local_abs_filename.filename().generic_string()
	);

	if (result.inserted_oid() != pqxx::oid_none)
	{
		// error handling process if you need...
	}

	w->commit();
	std::println("INSERT INTO file_index......\n");
	w = std::make_unique<pqxx::work>(con);
};

std::map<int64_t, std::tuple<std::filesystem::path, std::filesystem::path>> drone_db_connection::select_query_directory(std::string where_clause) const
{
	semaphore_acq_rel acq_rel(this->bsmph);
	
	const auto query_result = w->exec(std::format("SELECT * FROM remote_table WHERE {}" , where_clause));
	if (query_result.empty())
	{
		std::println("query_result is empty from dir......");
		return {};
	}

	std::map<int64_t, std::tuple<std::filesystem::path, std::filesystem::path>> result;
	int64_t primary_key = 0ULL;
	std::tuple<std::filesystem::path, std::filesystem::path> values{};

	const std::unordered_map<std::string, std::function<void(const pqxx::const_row_iterator::reference&)>> behavior
	{
		{
			"idx",
			[&primary_key](const pqxx::const_row_iterator::reference& field)->void
			{
				primary_key = std::atoll(field.c_str());
			}
		},
		{
			"remote_dir",
			[&values](const pqxx::const_row_iterator::reference& field)->void
			{
				auto& [remote, local] = values;
				remote = field.c_str();
			}
		},
		{
			"local_dir",
			[&values](const pqxx::const_row_iterator::reference& field)->void
			{
				auto& [remote, local] = values;
				local = field.c_str();
			}
		}
	};

	for (const auto& row : query_result)
	{
		for (const auto& field : row)
		{
			if (not behavior.contains(field.name()))
				continue;

			behavior.at(field.name())(field);
		}

		result.emplace(primary_key, values);
		
		primary_key = 0ULL;
		values = {};
	}

	return result;
};

std::map<int64_t, std::tuple<std::filesystem::path, std::filesystem::path>> drone_db_connection::select_query_file_index(std::string where_clause) const
{
	semaphore_acq_rel acq_rel(this->bsmph);
	
	try
	{
		const auto query_result = w->exec(std::format("SELECT * FROM file_index WHERE ({})", where_clause));
		if (query_result.empty())
		{
			//std::println("query_result is empty from file_idx......");
			return {};
		}

		std::map<int64_t, std::tuple<std::filesystem::path, std::filesystem::path>> result;
		std::filesystem::path remote;
		std::filesystem::path local;

		int64_t primary_key = 0ULL;
		std::tuple<std::filesystem::path, std::filesystem::path> values{};
		const std::unordered_map<std::string, std::function<void(const pqxx::const_row_iterator::reference&)>> behavior
		{
		{
			"remote_dir",
			[&values](const pqxx::const_row_iterator::reference& field)->void
			{
				auto& [remote, local] = values;
				remote = field.c_str() / remote;
			}
		},
		{
			"remote_filename",
			[&values](const pqxx::const_row_iterator::reference& field)->void
			{
				auto& [remote, local] = values;
				remote = remote / field.c_str();
			}
		},
		{
			"local_dir",
			[&values](const pqxx::const_row_iterator::reference& field)->void
			{
				auto& [remote, local] = values;
				local = field.c_str() / local;
			}
		},
		{
			"local_filename",
			[&values](const pqxx::const_row_iterator::reference& field)->void
			{
				auto& [remote, local] = values;
				local = local / field.c_str();
			}
		},
		{
			"idx",
			[&primary_key](const pqxx::const_row_iterator::reference& field)->void
			{
				primary_key = std::atoll(field.c_str());
			}
		}
		};

		for (const auto& row : query_result)
		{
			for (const auto& field : row)
			{
				if (not behavior.contains(field.name()))
					continue;

				behavior.at(field.name())(field);
			}

			result.emplace(primary_key, values);
			
			primary_key = 0ULL;
			values = {};
		}
		return result;
	}
	catch (std::exception& e)
	{
		std::string what = e.what();
		std::u8string whatu8(what.begin(), what.end());
		std::println("{}", what);
		return {};
	}
};
