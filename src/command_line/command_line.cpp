#include "command_line/command_line.hpp"
#include <iostream>
#include <ranges>
#include <stdexcept>

namespace detail {
std::string peek(SourceHandler<std::string> const& source_handler)
{
    return source_handler.peek().value_or("");
}
} // namespace detail

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
    : options_ {}
    , handler_ { input_args }
{
}

void CommandLine::parse()
{
    while (!handler_.eos()) {
        if (reserved_option_()) {
            continue;
        }

        if (regular_option_()) {
            continue;
        }

        remaining_.push_back(detail::peek(handler_));
        handler_.discard();
    }
}

void CommandLine::register_option(Option const& option)
{
    options_.push_back(option);
}

CommandLine::OptionalArguments CommandLine::remaining() const
{
    return remaining_.size() ? std::optional { remaining_ } : std::nullopt;
}

CommandLine::OptionalArguments CommandLine::option_arguments(std::string const& name) const
{
    return provided_options_.at(name);
}

bool CommandLine::is_option_present(std::string const& name) const
{
    return provided_options_.contains(name);
}

bool CommandLine::regular_option_()
{
    auto arg = detail::peek(handler_);

    auto comparison = [&arg = std::as_const(arg)](Option const& option) {
        if (option.alternative_name().has_value()) {
            return (option.name() == arg) || (option.alternative_name().value() == arg);
        }

        return option.name() == arg;
    };

    auto const option = std::find_if(options_.begin(), options_.end(), comparison);
    bool const option_found = (option != options_.end());

    if (option_found) {
        handler_.discard();

        std::vector<std::string> input;
        for (u8 i = 0; i < option->arguments_count(); ++i) {
            auto option_arg = detail::peek(handler_);
            handler_.discard();

            if (option_arg.empty()) {
                throw std::runtime_error("Missing input argument"); // TODO temporary solution
            }

            input.push_back(option_arg);
        }

        provided_options_[arg] = input.size() ? std::optional { input } : std::nullopt;

        return true;
    }

    return false;
}

bool CommandLine::reserved_option_()
{
    if (handler_.match("--help") || handler_.match("-h")) {
        provided_options_["--help"] = std::nullopt;
        return true;
    }

    return false;
}