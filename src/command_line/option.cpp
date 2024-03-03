#include "command_line/option.hpp"

Option::Option([[maybe_unused]] OptionConstructionKey&& consturction_key)
    : name_ {}
    , alternative_name_ { std::nullopt }
    , arguments_count_ { 0 }
    , help_message_ {}
{
}

std::string Option::name() const
{
    return name_;
}

std::optional<std::string> Option::alternative_name() const
{
    return alternative_name_;
}

u8 Option::arguments_count() const
{
    return arguments_count_;
}

std::string Option::help_message() const
{
    return help_message_;
}