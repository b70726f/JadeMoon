#pragma once

#include <string>

#include "jm_int.hpp"
#include "token/token_kind.hpp"

class Token {
public:
    Token(TokenKind const, std::string const, bool const = false);
    bool is(TokenKind const) const;
    bool is_chained() const;
    TokenKind kind() const;
    std::string const literal() const;

private:
    bool const chained_;
    TokenKind const kind_;
    std::string const literal_;
};