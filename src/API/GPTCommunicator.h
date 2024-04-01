#pragma once
#include <string>


std::string read_api_key();

std::string chat_with_gpt(const std::string &message_content, const std::string& system_message);