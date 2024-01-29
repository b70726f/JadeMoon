#include "lexer/source_file_handler.hpp"

SourceFileHandler::SourceFileHandler(ISource const& source)
    : position_(0)
    , source_(source)
{
}

void SourceFileHandler::discard()
{
    if (end() == false) {
        ++position_;
    }
}

bool SourceFileHandler::end()
{
    return is_at_or_beyond_end_(position_);
}

bool SourceFileHandler::match(char const character)
{
    if (character == peek()) {
        discard();
        return true;
    }

    return false;
}

char SourceFileHandler::peek(u8 const look_ahead)
{
    if (is_at_or_beyond_end_(position_ + look_ahead)) {
        return '\0';
    }

    return source_.at(position_ + look_ahead);
}

std::string SourceFileHandler::sub_str(u16 const position_start, u16 const position_end)
{
    auto string_begin = source_.data() + position_start;
    std::size_t length = (position_end - position_start + 1);
    return std::string { string_begin, length };
}

u32 SourceFileHandler::position() const
{
    return position_;
}

bool SourceFileHandler::is_at_or_beyond_end_(u8 const position)
{
    return position >= source_.length();
}