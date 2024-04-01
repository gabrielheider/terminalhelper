#!/bin/bash

# Run the helper and capture the commands
COMMANDS=$(/home/adminlokal/projekte/terminalhelper/build/TerminalHelper | tee /dev/tty)

# Add each command to the shell's history
IFS=$'\n' # Use newline as the delimiter
for cmd in $COMMANDS; do
    history -s "$cmd"
done

echo "Commands have been added to history. Use up/down arrow keys."

