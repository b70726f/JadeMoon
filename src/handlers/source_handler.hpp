#pragma once

#include <optional>
#include <vector>

#include "jmc/concepts.hpp"
#include "jmc/types.hpp"
#include "source/i_source.hpp"

template <jmc::NonPtrNonRef T>
class SourceHandler {
public:
    SourceHandler(std::vector<T> const&);

    void discard();
    bool eos();
    std::optional<T> peek(u8 const = 0) const;
    u32 position() const;

    template <jmc::NonPtrNonRef U>
    bool match(U const)
        requires jmc::IsComparable<T, U>;

    std::vector<T> const& raw() const;

private:
    inline bool is_end_(u32) const;

    std::vector<T> const source_;
    u32 position_;
};

template <jmc::NonPtrNonRef T>
SourceHandler<T>::SourceHandler(std::vector<T> const& source)
    : source_(source)
    , position_(0)
{
}

template <jmc::NonPtrNonRef T>
void SourceHandler<T>::discard()
{
    if (!eos()) {
        ++position_;
    }
}

template <jmc::NonPtrNonRef T>
bool SourceHandler<T>::eos()
{
    return is_end_(position_);
}

template <jmc::NonPtrNonRef T>
template <jmc::NonPtrNonRef U>
bool SourceHandler<T>::match(U const target)
    requires jmc::IsComparable<T, U>
{
    if (source_.at(position_) == target) {
        ++position_;
        return true;
    }

    return false;
}

template <jmc::NonPtrNonRef T>
std::optional<T> SourceHandler<T>::peek(u8 const look_ahead) const
{
    if (is_end_(position_ + look_ahead)) {
        return std::nullopt;
    }

    return source_.at(position_ + look_ahead);
}

template <jmc::NonPtrNonRef T>
u32 SourceHandler<T>::position() const
{
    return position_;
}

template <jmc::NonPtrNonRef T>
inline bool SourceHandler<T>::is_end_(u32 position) const
{
    return position >= source_.capacity();
}

template <jmc::NonPtrNonRef T>
std::vector<T> const& SourceHandler<T>::raw() const
{
    return source_;
}