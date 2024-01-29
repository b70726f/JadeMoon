#include "lexer/lexer.hpp"

Lexer::Lexer(ISource const& source_file)
    : source_file_(source_file)
{
}

std::vector<Token> Lexer::analise()
{
    std::vector<Token> tokens;

    while (!source_file_.end()) {
        discard_whitespaces_();

        if (discard_comment_()) {
            continue;
        }

        tokens.push_back(token_());
    }

    return tokens;
}

bool Lexer::discard_comment_()
{
    if (source_file_.match('#')) {
        if (source_file_.match('#')) {
            while (!source_file_.end()) {
                if (source_file_.match('#') && source_file_.match('#')) {
                    return true;
                }

                source_file_.discard();
            }

            throw std::runtime_error("Unterminated comment"); // TODO temporary solution
        } else {
            while (!source_file_.end() && !source_file_.match('\n')) {
                source_file_.discard();
            }

            return true;
        }
    }

    return false;
}

bool Lexer::is_alphanumeric_(char const character) const
{
    return is_alpha_(character) || std::isdigit(character);
}

bool Lexer::is_alpha_(char const character) const
{
    return std::isalpha(character) || (character == '_');
}

void Lexer::discard_whitespaces_()
{
    while (!source_file_.end() && is_whitespace_(source_file_.peek())) {
        source_file_.discard();
    }
}

std::optional<Token> Lexer::identifier_()
{
    if (is_alpha_(source_file_.peek())) {
        auto lexeme_start = source_file_.position();
        source_file_.discard();

        while (is_alphanumeric_(source_file_.peek())) {
            source_file_.discard();
        }

        auto lexeme_end = source_file_.position() - 1;

        return Token { TokenKind::identifier, source_file_.sub_str(lexeme_start, lexeme_end) };
    }

    return std::nullopt;
}

std::optional<Token> Lexer::constant_()
{
    if (std::isdigit(source_file_.peek())) {
        auto constant_start = source_file_.position();
        source_file_.discard();

        while (std::isdigit(source_file_.peek())) {
            source_file_.discard();
        }

        auto constant_end = source_file_.position() - 1;

        return Token { TokenKind::constant, source_file_.sub_str(constant_start, constant_end) };
    }

    return std::nullopt;
}

Token Lexer::token_()
{
    auto identifier = identifier_();
    if (identifier.has_value()) {
        return identifier.value();
    }

    auto constant = constant_();
    if (constant.has_value()) {
        return constant.value();
    }

    auto token = Token { token_kind_(source_file_.peek()), std::string { source_file_.peek() } };
    source_file_.discard();

    return token;
}

TokenKind Lexer::token_kind_(char const character) const
{
    switch (character) {
    case '\0':
        return TokenKind::eof;
    default:
        return TokenKind::unknown;
    }
}

bool Lexer::is_whitespace_(char const character) const
{
    switch (character) {
    case '\n':
    case ' ':
    case '\t':
    case '\r':
    case '\f':
        return true;
    default:
        return false;
    }
}