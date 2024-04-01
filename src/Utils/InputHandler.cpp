#include "InputHandler.h"
#ifdef _WIN32

std::wstring trimAndReduceSpaces(const std::wstring& input) {
    std::wstring result = input;

    // Trim spaces from the start
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](wchar_t ch) {
        return !std::iswspace(ch);
        }));

    // Trim spaces from the end
    result.erase(std::find_if(result.rbegin(), result.rend(), [](wchar_t ch) {
        return !std::iswspace(ch);
        }).base(), result.end());

    // Reduce internal sequences of spaces to a single space
    auto newEnd = std::unique(result.begin(), result.end(), [](wchar_t a, wchar_t b) {
        return std::iswspace(a) && std::iswspace(b) && a == b;
        });
    result.erase(newEnd, result.end());

    return result;
}

std::string  readFromTerminal() {
    // Get a handle to the console screen buffer:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get the current buffer info:
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Failed to get console buffer info." << std::endl;
        return "";
    }

    // Define the size and region of the buffer to read
    SMALL_RECT readRect;
    readRect.Left = 0;
    readRect.Top = 0;
    readRect.Right = csbi.dwSize.X - 1;
    readRect.Bottom = csbi.dwSize.Y - 1;

    COORD coordBufSize;
    coordBufSize.X = csbi.dwSize.X;
    coordBufSize.Y = csbi.dwSize.Y;

    COORD coordBufCoord;
    coordBufCoord.X = 0;
    coordBufCoord.Y = 0;

    // Define a buffer to hold the data
    std::vector<CHAR_INFO> chiBuffer(coordBufSize.X * coordBufSize.Y);

    // Read the console output into chiBuffer
    if (!ReadConsoleOutput(hConsole, chiBuffer.data(), coordBufSize, coordBufCoord, &readRect)) {
        std::cerr << "Failed to read console output." << std::endl;
        return "";
    }

    try {
        // std::cout << "Allocating: " << coordBufSize.X * coordBufSize.Y << " elements." << std::endl;
        std::vector<wchar_t> textBuffer(coordBufSize.X * coordBufSize.Y + 1);

        int index = 0;
        for (int i = 0; i < coordBufSize.Y; i++) {
            for (int j = 0; j < coordBufSize.X; j++) {
                textBuffer[index++] = chiBuffer[i * coordBufSize.X + j].Char.UnicodeChar;
            }
        }
        textBuffer[index] = L'\0';  // Null-terminate the string if you're building a string.

        // Calculate the start position
        int startPos = 0;

        // Convert to std::wstring
        std::wstring fullWindow(textBuffer.begin() + startPos, textBuffer.end());
        //trim empty spaces
        std::wstring trimed = trimAndReduceSpaces(fullWindow);

        std::string str(trimed.begin(), trimed.end());
        // Set text color to blue
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
        // std::cout << str << std::endl;
        // Reset text color to white
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        return str;

    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    }
}
#endif