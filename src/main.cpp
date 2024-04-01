#include <iostream>
#include "API/GPTCommunicator.h"
#include "Utils/BashCommandExtractor.h"
#include "Utils/FileHandler.h"
#include "Utils/OutputHandler.h"
#include "Utils/InputHandler.h"

#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

#include <regex>
#include <vector>



int main(int argc, char* argv[])
{
    std::string arg;
    if(argc > 1) 
        arg = argv[1];

    std::string context;
#ifdef _WIN32
    if (arg == "-c") {
        context = readFromTerminal();
    }
#endif
   
    std::string query;
    std::string response;
#ifdef _WIN32
    if (arg == "-c") {
        std::cout << "i am aware of the visible part of your cmd, how can i help you? ";
        std::getline(std::cin, query);
        response = chat_with_gpt(query, context);
    }
    else {
        std::cout << "what do you want to do in the cmd? ";
        std::getline(std::cin, query);
        response = chat_with_gpt(query, "");
    }
#else
    std::cerr << "what do you want to do? ";
    std::getline(std::cin, query);
    // send user input to chatgpt and recive the response
    response = chat_with_gpt(query);
#endif

    // output the complete response message (not the complete json recived just the plain answer text)
    outputResponse(response);
    // extract the commands from the chat gpt answer
    std::vector<std::string> commands = extract_bash_commands(response);

    // handle what is done with the commands. its not possible to save them to history in windows
#ifdef _WIN32
    stdCoutCommandsWindows(commands);
#else
    // For the purpose of adding to history, print just the commands (linux with bash script):
    stdCoutCommands(commands);
    // system("script /home/adminlokal/projekte/terminalhelper/mylog.txt");
#endif

    return 0;
}
