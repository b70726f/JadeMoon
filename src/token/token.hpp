#pragma once

#include <string>

#include "jm_int.hpp"
#include "token/token_kind.hpp"

class Token {
public:
    Token(TokenKind const, std::string const);
    TokenKind kind() const;
    std::string const literal() const;

private:
    TokenKind const kind_;
    std::string const literal_;
};