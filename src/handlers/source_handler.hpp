#pragma once

#include "jmc/concepts.hpp"
#include "jmc/types.hpp"
#include "source/i_source.hpp"

template <jmc::NonPtrNonRef T>
class SourceHandler {
public:
    SourceHandler(ISource<T> const&);

    void discard();
    bool end();
    T peek(u8 const = 0);
    u32 position() const;
    ISource<T> const& raw() { return source_; }

    template <jmc::NonPtrNonRef U>
    bool match(U const)
        requires jmc::IsComparable<T, U>;

private:
    inline bool is_at_or_beyond_end(u32) const;

    ISource<T> const& source_;
    u32 position_;
};

template <jmc::NonPtrNonRef T>
SourceHandler<T>::SourceHandler(ISource<T> const& source)
    : source_(source)
    , position_(0)
{
}

template <jmc::NonPtrNonRef T>
void SourceHandler<T>::discard()
{
    if (!end()) {
        ++position_;
    }
}

template <jmc::NonPtrNonRef T>
bool SourceHandler<T>::end()
{
    return is_at_or_beyond_end(position_);
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
T SourceHandler<T>::peek(u8 const look_ahead)
{
    if (is_at_or_beyond_end(position_ + look_ahead)) {
        return source_.at(position_);
    }

    return source_.at(position_ + look_ahead);
}

template <jmc::NonPtrNonRef T>
u32 SourceHandler<T>::position() const
{
    return position_;
}

template <jmc::NonPtrNonRef T>
inline bool SourceHandler<T>::is_at_or_beyond_end(u32 position) const
{
    return position >= source_.length() - 1;
}