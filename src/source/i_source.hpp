#pragma once

#include <string_view>
#include <type_traits>

#include "jmc/concepts.hpp"
#include "jmc/types.hpp"

template <jmc::NonPtrNonRef T>
class ISource {
public:
    virtual std::remove_const_t<T> at(u32) const = 0;
    virtual T const* data() const = 0;
    virtual u32 length() const = 0;
};