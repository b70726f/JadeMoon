#pragma once

#include <optional>
#include <string>

#include "jmc/types.hpp"

/*
 * OptionConstructionKey is provided to allow creation of Option only
 * for OptionBuilder. We cannot create private Option constructor and declare OptionBuilder as friend
 * because that will not allow us to create Option via unique_ptr
 */

class OptionConstructionKey {
    friend class OptionBuilder;

private:
    OptionConstructionKey() = default;
};

class Option {
    friend class OptionBuilder;

public:
    explicit Option(OptionConstructionKey&&);
    std::string name() const;
    std::optional<std::string> alternative_name() const;
    u8 arguments_count() const;
    std::string help_message() const;

private:
    std::string name_;
    std::optional<std::string> alternative_name_;
    u8 arguments_count_;
    std::string help_message_;
};