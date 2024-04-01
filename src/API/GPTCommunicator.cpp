#include "GPTCommunicator.h"
#include "../Utils/FileHandler.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include <vector>


std::string read_api_key()
{
#ifdef _WIN32
	std::ifstream file("C:/projekte/terminalhelper/apikey.txt"); // Open the text file
#else
	std::ifstream file("/home/adminlokal/projekte/terminalhelper/apikey.txt"); // Open the text file
#endif

	if (!file)
	{ // If the file opening failed
		std::cerr << "Failed to open the API key file!" << std::endl;
	}

	std::string api_key;
	std::getline(file, api_key); // Read the API key (assuming it's on the first line)

	file.close(); // Close the file

	return api_key;
}


std::string chat_with_gpt(const std::string& message_content, const std::string& system_message = "")
{
	const std::string API_ENDPOINT = "https://api.openai.com/v1/chat/completions";
	const std::string API_KEY = read_api_key(); // Replace this with your actual API Key

	nlohmann::json payload;

	if (system_message != "")
	{
		// Construct the request payload
		payload = {
			{"model", "gpt-3.5-turbo"},
#ifdef _WIN32

			//{"messages", {{{"role", "user"}, {"content", message_content}}}},
			{"messages",
				nlohmann::json::array({
					nlohmann::json::object({{"role", "system"}, {"content",  system_message + " \n This is cmd output, TerminalHelper.exe is a programm to use the openai api, so you don't have to care about that."}}),
					//mkdirnlohmann::json::object({{"role", "user"}, {"content", system_message + " \n This is cmd output, TerminalHelper.exe is a programm to use the openai api, so you don't have to care about that."}}),
					nlohmann::json::object({{"role", "user"}, {"content", message_content}})
					})
			},
#else
			//{"messages", {{{"role": "system", "content" : "You are an expert for terminal commands on linux."}, {"role", "user"}, {"content", "linux terminal command for: " + message_content}}}},
			{"messages",
				nlohmann::json::array({
					nlohmann::json::object({{"role", "system"}, {"content", "You are an expert for terminal commands on linux."}}),
					nlohmann::json::object({{"role", "user"}, {"content", "linux terminal command for: " + message_content}})
					})
			},
#endif
			{"temperature", 0.3} };
	}
	else
	{
		// Construct the request payload
		payload = {
			{"model", "gpt-3.5-turbo"},
#ifdef _WIN32

			//{"messages", {{{"role", "user"}, {"content", message_content}}}},
			{"messages",
				nlohmann::json::array({
					nlohmann::json::object({{"role", "system"}, {"content", "You are an expert for the cmd on windows."}}),
					nlohmann::json::object({{"role", "user"}, {"content", "windows cmd command for: " + message_content}})
					})
			},
#else
			//{"messages", {{{"role": "system", "content" : "You are an expert for terminal commands on linux."}, {"role", "user"}, {"content", "linux terminal command for: " + message_content}}}},
			{"messages",
				nlohmann::json::array({
					nlohmann::json::object({{"role", "system"}, {"content", "You are an expert for terminal commands on linux."}}),
					nlohmann::json::object({{"role", "user"}, {"content", "linux terminal command for: " + message_content}})
					})
			},
#endif
			{"temperature", 0.3} };
	}
	saveRawMessage(payload);

	// Send the POST request
	cpr::Response r = cpr::Post(
		cpr::Url{ API_ENDPOINT },
		cpr::Header{
			{"Content-Type", "application/json"},
			{"Authorization", "Bearer " + API_KEY} },
			cpr::Body{ payload.dump() });

	saveRawResponse(r);
	// std::cerr << payload << std::endl;
	// Parse the response
	// std::cerr << "Raw API response: " << r.text << std::endl;
	// std::cout << " \n \n  end of raw API response \n \n" << std::endl;
	auto response_data = nlohmann::json::parse(r.text);
	return response_data["choices"][0]["message"]["content"].get<std::string>();
}
