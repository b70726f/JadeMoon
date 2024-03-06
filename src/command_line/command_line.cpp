#include "command_line/command_line.hpp"

namespace utils {
std::vector<std::string> c_string_array_to_string_vector(u8 const array_size, char const* array[])
{
    std::vector<std::string> vector;
    for (u8 i = 0; i < array_size; ++i) {
        vector.push_back(std::string { array[i] });
    }

    return vector;
}

void initialize_cli_options(CommandLine& cl)
{
    OptionBuilder option_bulider;
    option_bulider.set_name("--output", "-o")
        .set_arguments_count(1)
        .set_help_message("This option set output file name");

    cl.register_option(*option_bulider.create());
}
} // namespace utils

CommandLine::CommandLine(std::vector<std::string> const& input_args)
    : handler_(input_args)
{
}

void CommandLine::parse()
{
}

void CommandLine::register_option(Option const& option)
{
    options_.push_back(option);
}