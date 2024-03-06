#pragma once

#include <string>
#include <vector>

#include "command_line/option_builder.hpp"
#include "handlers/source_handler.hpp"

class CommandLine;

namespace utils {
[[nodiscard]] std::vector<std::string> c_string_array_to_string_vector(u8 const, char const*[]);
void initialize_cli_options(CommandLine&);
} // namspace utils

class CommandLine {
public:
    CommandLine(std::vector<std::string> const&);
    void parse();
    void register_option(Option const&);

private:
    std::vector<Option> options_;
    SourceHandler<std::string> handler_;
};