#include "token/token.hpp"

Token::Token()
    : chained_ { false }
    , kind_ { TokenKind::eof }
    , literal_ {}
{
}

Token::Token(TokenKind const kind, std::string const literal, bool const chained)
    : chained_(chained)
    , kind_(kind)
    , literal_(literal)
{
}

bool Token::is(TokenKind const kind) const
{
    return kind_ == kind;
}

bool Token::is_chained() const
{
    return chained_;
}

TokenKind Token::kind() const
{
    return kind_;
}

std::string const Token::literal() const
{
    return literal_;
}