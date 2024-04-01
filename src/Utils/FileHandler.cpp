#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <deque>



bool stop_script_session()
{
    // Try to find the process ID of 'script'
    int ret = system("pgrep script > /tmp/script_pid.txt");
    if (ret == 0)
    { // If the command succeeded
        std::ifstream pidFile("/tmp/script_pid.txt");
        std::string pid;
        if (std::getline(pidFile, pid))
        {
            std::cerr << "Found script process with PID: " << pid << std::endl;
            std::string killCommand = "kill " + pid;
            system(killCommand.c_str()); // Terminate the script process
            std::cerr << "Terminated script process." << std::endl;
        }
        pidFile.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return true;
    }
    else
    {
        std::cerr << "No running script process found." << std::endl;
        return false;
    }
}
std::string read_script_session()
{
    std::ifstream file("/home/adminlokal/projekte/terminalhelper/mylog.txt");
    std::string line;
    std::deque<std::string> last_50_lines; // Use a deque to easily push/pop front

    while (std::getline(file, line))
    {
        last_50_lines.push_back(line);
        if (last_50_lines.size() > 50)
        {
            last_50_lines.pop_front();
        }
    }
    file.close();

    std::string result;

    for (const auto &line : last_50_lines)
    {
        result += line + "\n"; // Append each line and a newline character
    }

    return result;
}

void saveRawMessage(nlohmann::json m) {
    // Save the response to a txt file (append mode)
#ifdef _WIN32
    std::ofstream outFile("C:/Projekte/terminalhelper/rawcommunication.txt", std::ios_base::app);  // Open file in append mode
#else
    std::ofstream outFile("rawcommunication.txt", std::ios_base::app);
#endif

    if (outFile.is_open()) {
        // add date and time to the file
        time_t t = time(0);
        struct tm* now = localtime(&t);
        outFile << "Date: " << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday << " Time: " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << "\n";

        outFile << "Message: \n" << m << "\n";  // Write the response text and a newline for separation
        outFile.close();
    }
    else {
        std::cerr << "Failed to open the file for writing!" << std::endl;
    }
}

void saveRawResponse(cpr::Response r) {
    // Save the response to a txt file (append mode)
#ifdef _WIN32
    std::ofstream outFile("C:/Projekte/terminalhelper/rawcommunication.txt", std::ios_base::app);  // Open file in append mode
#else
    std::ofstream outFile("rawcommunication.txt", std::ios_base::app);
#endif

    if (outFile.is_open()) {
        // add date and time to the file
        time_t t = time(0);
        struct tm* now = localtime(&t);
        outFile << "Date: " << now->tm_year + 1900 << '-' << now->tm_mon + 1 << '-' << now->tm_mday << " Time: " << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << "\n";

        outFile <<"Response: \n" << r.text << "\n \n";  // Write the response text and a newline for separation
        outFile.close();
    }
    else {
        std::cerr << "Failed to open the file for writing!" << std::endl;
    }
}