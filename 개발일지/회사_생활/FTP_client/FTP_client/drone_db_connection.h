#pragma once
// std
#include <semaphore>
#include <memory>
#include <print>

// libpqxx
#include <pqxx/pqxx>

// forward declarations
namespace std { namespace filesystem { class path; } }

class drone_db_connection
{
	mutable std::binary_semaphore bsmph;
	class semaphore_acq_rel
	{
		std::binary_semaphore& bsmph_ref;
	public:
		semaphore_acq_rel(std::binary_semaphore& smph) : bsmph_ref(smph) { bsmph_ref.acquire(); }
		~semaphore_acq_rel() { bsmph_ref.release(); }
	};

	mutable pqxx::connection con;
	mutable std::unique_ptr<pqxx::work> w;

public:
	drone_db_connection();
	~drone_db_connection();

	void insert_query_directory(int idx, const std::filesystem::path& remote_dir, const std::filesystem::path& local_dir) const;
	void insert_query_file_index(const std::filesystem::path& remote_abs_filename, const std::filesystem::path& local_abs_filename) const;

	std::map<int64_t, std::tuple<std::filesystem::path, std::filesystem::path>> select_query_directory(std::string where_clause = "true") const;
	std::map<int64_t, std::tuple<std::filesystem::path, std::filesystem::path>> select_query_file_index(std::string where_clause = "true") const;
};