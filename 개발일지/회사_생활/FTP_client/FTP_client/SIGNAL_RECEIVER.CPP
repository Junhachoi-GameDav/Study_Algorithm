// std
#include <map>
#include <functional>
#include <regex>

// cpprestsdk
#include <cpprest/filestream.h>
#include <cpprest/http_headers.h>
#include <cpprest/uri.h>

// nlohmann's json
#include <nlohmann/json.hpp>

// this project
#include "signal_receiver.h"
//#include "../global_logger.h"
#include "build_config.h"
signal_receiver::signal_receiver() : listener(utility::conversions::to_string_t(target_config.sig_recv_host_address)/*U("http://175.116.181.24:40000")*/), bsmph(1)
{
	try
	{
		// Define a handler for GET requests
		listener.support(web::http::methods::POST, [this](web::http::http_request request)->void
		{
			const std::string body = request.extract_utf8string().get();
			
			nlohmann::json j;
			try
			{
				j = nlohmann::json::parse(body);
				const std::string acq_signal = j["value"].get<std::string>();
				const std::string address = j["address"].get<std::string>();

				if (acq_signal == "ACQUISITION_START")
				{
					web::http::http_response response(web::http::status_codes::OK);
					response.headers().add(U("Content-Type"), U("text/plain"));

					if (acquisition_status.contains(address))
					{
						response.set_body(U("START_IGNORED"));
						return request.reply(response).get();
					}

					estimated_drone_count = j["count"].get<int>();
					const double heading = j["heading"].get<double>();

					bsmph.acquire();
					acquisition_status.emplace(address, true);
					initial_headings.emplace(address, heading);
					bsmph.release();

					response.set_body(U("START_RECEIVED"));
					return request.reply(response).get();
				}
				if (acq_signal == "ACQUISITION_END")
				{
					web::http::http_response response(web::http::status_codes::OK);
					response.headers().add(U("Content-Type"), U("text/plain"));

					if (not acquisition_status.contains(address))
					{
						response.set_body(U("END_IGNORED"));
						return request.reply(response).get();
					}

					bsmph.acquire();
					acquisition_status.at(address) = false;
					bsmph.release();
					
					response.set_body(U("END_RECEIVED"));
					return request.reply(response).get();
				}

				return request.reply(web::http::http_response(web::http::status_codes::BadRequest)).get();
			}
			catch (const nlohmann::json::exception& e)
			{
				return request.reply(web::http::http_response(web::http::status_codes::BadRequest)).get();
			}
		});

		// Open the listener
		listener
			.open()
			.then([]()->void { std::wcout << L"HTTP server is listening." << std::endl; })
			.wait();
	}
	catch (const web::http::http_exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


signal_receiver::~signal_receiver()
{
	listener.close().wait();
}

void signal_receiver::remove_drone(const std::string& drone_address)
{
	bsmph.acquire();

	if (acquisition_status.contains(drone_address))
		acquisition_status.erase(drone_address);

	bsmph.release();
}

void signal_receiver::remove_heading(const std::string& drone_address)
{
	bsmph.acquire();

	if (initial_headings.contains(drone_address))
		initial_headings.erase(drone_address);
	
	bsmph.release();
}