cmake_minimum_required(VERSION 3.11) # 3.11 or higher for FetchContent
project(TerminalHelper)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent for cpr
include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba # This is for 1.10.x, update if needed
)
FetchContent_MakeAvailable(cpr)

# Add your include directories
include_directories(src)

# Your source files
file(GLOB_RECURSE SOURCES
    src/main.cpp
    src/API/GPTCommunicator.cpp
    src/Utils/FileHandler.cpp
    src/Utils/BashCommandExtractor.cpp
    src/Utils/InputHandler.cpp
    src/Utils/OutputHandler.cpp
)

# Your header files (for better organization in some IDEs)
file(GLOB_RECURSE HEADERS
    src/API/GPTCommunicator.h
    src/Utils/FileHandler.h
    src/Utils/BashCommandExtractor.h
    src/Utils/InputHandler.h
    src/Utils/OutputHandler.h
)

# Create executable with both source and header files
add_executable(TerminalHelper ${SOURCES} ${HEADERS})

# Link libraries to your project
target_link_libraries(TerminalHelper PRIVATE cpr::cpr)
