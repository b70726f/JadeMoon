#pragma once

#include <array>
#include <string_view>
#include <utility>

#include "token/token_kind.hpp"

class KeywordMap {
    friend class Lexer;
    using Keyword = std::pair<std::string_view, TokenKind>;

private:
    static constexpr u8 KEYWORD_COUNT = 7;
    static constexpr std::array<Keyword, KEYWORD_COUNT> map_[] = {
        std::make_pair("fn", TokenKind::kw_fn),
        std::make_pair("var", TokenKind::kw_var),
        std::make_pair("while", TokenKind::kw_while),
        std::make_pair("if", TokenKind::kw_if),
        std::make_pair("return", TokenKind::kw_return),
        std::make_pair("else", TokenKind::kw_else),
        std::make_pair("struct", TokenKind::kw_struct)
    };
};