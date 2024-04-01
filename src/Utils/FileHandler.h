#pragma once
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

bool stop_script_session();
std::string read_script_session();
void saveRawMessage(nlohmann::json m);
void saveRawResponse(cpr::Response r);
