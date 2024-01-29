#pragma once

#include <string>

#include "source/i_source.hpp"

class SourceFileHandler {
public:
    SourceFileHandler(ISource const&);
    void discard();
    bool end();
    bool match(char const);
    char peek(u8 const = 0);
    std::string sub_str(u16 const, u16 const);
    u32 position() const;

private:
    bool is_at_or_beyond_end_(u8 const);
    u32 position_;
    ISource const& source_;
};