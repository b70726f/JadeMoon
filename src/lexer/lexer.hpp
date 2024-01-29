#pragma once

#include <optional>
#include <stdexcept>
#include <vector>

#include "lexer/source_file_handler.hpp"
#include "source/i_source.hpp"
#include "token/token.hpp"

class Lexer {
public:
    Lexer(ISource const&);
    std::vector<Token> analise();

private:
    bool discard_comment_();
    bool is_whitespace_(char const) const;
    bool is_alphanumeric_(char const) const;
    bool is_alpha_(char const) const;
    void discard_whitespaces_();
    std::optional<Token> identifier_();
    std::optional<Token> constant_();
    Token token_();
    TokenKind token_kind_(char const) const;

    SourceFileHandler source_file_;
};