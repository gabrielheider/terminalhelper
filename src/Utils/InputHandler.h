#pragma once
#ifdef _WIN32
#include <windows.h>
#include <vector>
#include <iostream>
#include <cwctype>
#include <algorithm>
#include <string>


std::wstring trimAndReduceSpaces(const std::wstring& input);

std::string  readFromTerminal();
#endif