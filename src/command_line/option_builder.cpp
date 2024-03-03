#include "command_line/option_builder.hpp"

OptionBuilder::OptionBuilder()
{
    reset_();
}

OptionBuilder& OptionBuilder::set_name(std::string const& name,
    std::optional<std::string const> alternative_name)
{
    option_->name_ = name;
    option_->alternative_name_ = alternative_name;

    return *this;
}

OptionBuilder& OptionBuilder::set_arguments_count(u8 const arguments_count)
{
    option_->arguments_count_ = arguments_count;

    return *this;
}

OptionBuilder& OptionBuilder::set_help_message(std::string const& help_message)
{
    option_->help_message_ = help_message;

    return *this;
}

std::unique_ptr<Option> OptionBuilder::create()
{
    std::unique_ptr<Option> tmp = std::move(option_);
    reset_();

    return tmp;
}

void OptionBuilder::reset_()
{
    option_ = std::make_unique<Option>(OptionConstructionKey {});
}