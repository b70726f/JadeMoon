#pragma once

#include <optional>
#include <stdexcept>
#include <vector>

#include "handlers/source_handler.hpp"
#include "lexer/keyword_map.hpp"
#include "source/i_source.hpp"
#include "token/token.hpp"

class Lexer {
public:
    Lexer(std::vector<char> const&);
    std::vector<Token> analise();

private:
    bool discard_comment_();
    bool is_whitespace_(char const) const;
    bool is_alphanumeric_(char const) const;
    bool is_alpha_(char const) const;
    bool discard_whitespaces_();
    std::optional<Token> identifier_();
    std::optional<Token> keyword_(std::string const&) const;
    std::optional<Token> constant_();
    Token token_();
    TokenKind token_kind_(char const) const;

    SourceHandler<char> source_file_;
    bool whitespace_preceding_;
};