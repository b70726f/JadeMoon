#include "token/token.hpp"

Token::Token(TokenKind const kind, std::string const literal)
    : kind_(kind)
    , literal_(literal)
{
}

TokenKind Token::kind() const
{
    return kind_;
}

std::string const Token::literal() const
{
    return literal_;
}