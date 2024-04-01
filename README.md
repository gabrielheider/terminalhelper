

# TerminalHelper

**TerminalHelper** is an intuitive tool designed to harness the power of ChatGPT, allowing you to convert natural language inquiries into terminal commands. No longer do you need to memorize commands or look them up online; just ask TerminalHelper in plain English!

![TerminalHelper Logo](path_to_logo_image)

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Advanced Functionalities](#advanced-functionalities)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Features

- Convert natural language input into useful cmd/terminal commands.
- On windows it is possible to include the visible part of the cmd to the question


## Prerequisites

- A modern C++ compiler with support for C++17.
- CMake (version 3.11 or higher, due to the use of FetchContent).
- OpenAI API-Key.
- Internet connection to interact with ChatGPT.
- cpr library for making HTTP requests (automatically fetched during CMake build).
- nlohmann JSON library for handling JSON data.

## Installation

**Clone the Repository**:
```bash
git clone https://github.com/gabrielheider/terminalhelper.git
cd terminalhelper
```
**Install nlohman**
if you have vcpkg (on windows) do: vcpkg install nlohmann-json:x64-windows


**Build from Source using CMake**:
```bash
mkdir build && cd build
cmake ..
make
```

## Usage

### Windows:

Start TerminalHelper by running:
```bash
terminalhelper.exe
```

On Windows, you can provide an `-c` argument to provide a specific context from the terminal:
```bash
terminalhelper.exe -c
```

### Linux:

On Linux, use the provided bash script `run_helper.sh` to start the program. This script will also manipulate the terminal command history so that the generated commands are appended:
```bash
./run_helper.sh
```

**Bash Script Content (`run_helper.sh`)**:
```bash
#!/bin/bash

# Run the helper and capture the commands
COMMANDS=$(/home/adminlokal/projekte/terminalhelper/build/TerminalHelper | tee /dev/tty)

# Add each command to the shell's history
IFS=$'\n' # Use newline as the delimiter
for cmd in $COMMANDS; do
    history -s "$cmd"
done

echo "Commands have been added to history. Use up/down arrow keys."
```

Once started, you'll be prompted to enter your natural language query. For instance:
```css
> How do I list all files in a directory?
```
TerminalHelper will then provide the respective command:
```bash
ls -l
```

## Contributing

We welcome contributions! Please follow the standard GitHub pull request process.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgements

- Thanks to OpenAI for the incredible ChatGPT model.
- Shoutout to the cpr library for HTTP request functionality and nlohmann JSON library for JSON parsing.
- All contributors and testers who made TerminalHelper possible.

---
