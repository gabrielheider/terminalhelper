#pragma once
#include <string>
#include <vector>

// used in linux with bash script
void stdCoutCommands(std::vector<std::string> commands);
#ifdef _WIN32
void stdCoutCommandsWindows(std::vector<std::string> commands);
#endif

void outputResponse(std::string);