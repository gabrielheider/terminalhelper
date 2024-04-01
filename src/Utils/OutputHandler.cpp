#include "OutputHandler.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#endif

void stdCoutCommands(std::vector<std::string> commands) {
    // For the purpose of adding to history, print just the commands (linux with bash script):
    for (const auto& cmd : commands)
    {
        std::cout << cmd << std::endl;
    }
    /*// Set text color to blue
    std::cout << "\033[34mThis is blue text.\033[0m" << std::endl;
    
    // Reset text color
    std::cout << "\033[0mThis is default text." << std::endl;*/
}
#ifdef _WIN32
void stdCoutCommandsWindows(std::vector<std::string> commands) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set text color to blue
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    int num = 1;
    for (int i = 0; i < commands.size(); i++)
    {
        if (commands[i] == "")
            continue;

        std::cout << num << ". " << commands[i] << std::endl;
        num++;
    }
    // Reset text color to white
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
#endif

void outputResponse(std::string output) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Set text color to blue
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    // output
    std::cout << output << "\n" << std::endl;
    // Reset text color to white
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

#else
    // we use std::cerr so it doesnt get read from bash script
    std::cerr << "\033[32m" << output << "\033[0m" << "\n" << std::endl;
#endif
}