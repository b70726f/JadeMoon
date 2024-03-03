#pragma once

#include <memory>

#include "command_line/option.hpp"

class OptionBuilder {
public:
    OptionBuilder();
    OptionBuilder& set_name(std::string const&, std::optional<std::string const> = std::nullopt);
    OptionBuilder& set_arguments_count(u8 const);
    OptionBuilder& set_help_message(std::string const&);
    std::unique_ptr<Option> create();

private:
    void reset_();
    std::unique_ptr<Option> option_;
};