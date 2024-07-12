// std
#include <iostream>
#include <map>
#include <mutex>

// cpp-httplib
#include <httplib.h>

// nlohmann's json
#include <nlohmann/json.hpp>

// fmt
#include <fmt/format.h>

using json = nlohmann::json;

std::map<std::string, bool> acquisition_status;
std::map<std::string, double> initial_headings;
std::mutex mtx;

/*
* 클라에 신호 보내는 함수
*/
void send_signal_to_ip(const std::string& ip, int port, const std::string& endpoint, const std::string& value, const std::string& address, double heading = 0.0)
{
	httplib::Client cli(ip.c_str(), port);
	json j;
	j["value"] = value;
	j["address"] = address;

	if (value == "ACQUISITION_START")
		j["heading"] = heading;

	httplib::Result res = cli.Post(endpoint.c_str(), j.dump(), "application/json");
	if (res)
		std::cout << fmt::format("Response from {} : {} - {}\n", ip, res->body, res->status);
	else 
		std::cout << fmt::format("Failed to send signal to {}\n", ip);
}

/*
* json을 읽어서 시작-종료 받는 함수
*/
void handle_post(const httplib::Request& req, httplib::Response& res)
{
	std::lock_guard<std::mutex> lock(mtx);
	// 정보 출력 (들어왔는지 나갔는지 등등)
	std::cout << fmt::format("Request body: {}\n", req.body);

	auto j = json::parse(req.body, nullptr, false);
	if (j.is_discarded() || not j.contains("value") || not j.contains("address"))
	{
		res.status = 400; // Bad Request
		return;
	}

	std::string acq_signal = j["value"];
	std::string address = j["address"];
	double heading = 0.0;

	if (acq_signal == "ACQUISITION_START")
	{
		if (acquisition_status.find(address) != acquisition_status.end())
		{
			res.set_content("START_IGNORED", "text/plain");
			return;
		}
		heading = j["heading"];

		acquisition_status[address] = true;
		initial_headings[address] = heading;
		res.set_content("START_RECEIVED", "text/plain");
	}

	if (acq_signal == "ACQUISITION_END")
	{
		if (acquisition_status.find(address) == acquisition_status.end())
		{
			res.set_content("END_IGNORED", "text/plain");
			return;
		}

		acquisition_status.erase(address); //지우면 false
		initial_headings.erase(address);
		res.set_content("END_RECEIVED", "text/plain");
	}

	// 클라 주소
	send_signal_to_ip("175.116.181.37", 40000, "/", acq_signal, address, heading);
}

int main() {
	httplib::Server svr;

	svr.Post("/", handle_post);

	svr.listen("175.116.181.37", 40001);

	return 0;
}
