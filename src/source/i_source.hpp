#pragma once

#include <string_view>

#include "jm_int.hpp"

class ISource {
public:
    virtual char at(u32 index) const = 0;
    virtual std::string_view line(u16 const) const = 0;
};