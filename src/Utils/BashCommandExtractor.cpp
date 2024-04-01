#include "BashCommandExtractor.h"
#include <regex>
#include <sstream>

std::vector<std::string> extract_bash_commands(const std::string &content)
{
    std::vector<std::string> commands;

    // Making recognition of "shell", "bash", or other identifiers optional
    std::regex code_block_pattern(R"(```(?:shell|bash)?\s*((?:.|\n)+?)```)");
    std::smatch code_block_matches;

    std::string::const_iterator search_start(content.cbegin());
    while (std::regex_search(search_start, content.cend(), code_block_matches, code_block_pattern))
    {
        std::string block_content = code_block_matches[1].str();

        // Now, we'll break the block_content into individual lines and process them
        std::stringstream ss(block_content);
        std::string line;
        while (std::getline(ss, line))
        {
            // Remove any trailing and leading whitespace
            line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

            if (!line.empty())
            {
                commands.push_back(line);
            }
        }

        search_start = code_block_matches.suffix().first;
    }
    // If the first pattern did not find anything, use the second pattern
    if (commands.empty())
    {
        std::regex pattern(R"("(.*?)"")"); // regex pattern to match content between double quotes
        std::smatch matches;

        if (std::regex_search(content, matches, pattern))
        {
            commands.push_back(matches[1].str());
        }
    }
    return commands;
}