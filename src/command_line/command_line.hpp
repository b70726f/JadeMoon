#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "command_line/option_builder.hpp"
#include "handlers/source_handler.hpp"

class CommandLine;

namespace utils {
[[nodiscard]] std::vector<std::string> c_string_array_to_string_vector(u8 const, char const*[]);
void initialize_cli_options(CommandLine&);
} // namspace utils

class CommandLine {
    using OptionalArguments = std::optional<std::vector<std::string>>;

public:
    CommandLine(std::vector<std::string> const&);
    void parse();
    void register_option(Option const&);
    OptionalArguments remaining() const;
    OptionalArguments option_arguments(std::string const&) const;
    bool is_option_present(std::string const&) const;

private:
    bool regular_option_();
    bool reserved_option_();

    std::unordered_map<std::string, OptionalArguments> provided_options_;
    std::vector<Option> options_;
    std::vector<std::string> remaining_;
    SourceHandler<std::string> handler_;
};