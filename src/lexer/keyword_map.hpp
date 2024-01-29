#pragma once

#include <string_view>
#include <utility>

#include "token/token_kind.hpp"

class KeywordMap {
    friend class Lexer;

private:
    inline static std::pair<std::string_view, TokenKind> map_[] = {
        { "fn", TokenKind::kw_fn },
        { "var", TokenKind::kw_var },
        { "while", TokenKind::kw_while },
        { "if", TokenKind::kw_if },
        { "return", TokenKind::kw_return },
        { "else", TokenKind::kw_else },
        { "struct", TokenKind::kw_struct }
    };
};