#include "parser/parser.hpp"

namespace detail {
Token peek(SourceHandler<Token> const& handler)
{
    return handler.peek().value_or(Token {});
}
} // namespace detail

Parser::Parser(std::vector<Token> const& tokens)
    : handler_ { tokens }
{
}

void Parser::parse()
{
    while (!handler_.eos()) {
    }
}

std::optional<bool> Parser::variable_()
{
    if (handler_.match(TokenKind::kw_var)) {
        if (!detail::peek(handler_).is(TokenKind::identifier)) {
            // TODO ERROR CASE
        }

        auto variable_name = detail::peek(handler_).literal();
        handler_.discard();

        if (!handler_.match(TokenKind::colon)) {
            // TODO ERROR CASE
        }

        type_();

        if (handler_.match(TokenKind::equal)) {
            expr_();
        }

        if (!handler_.match(TokenKind::semicolon)) {
            // TODO ERROR CASE
        }

        return true;
    }

    return std::nullopt;
}

std::optional<bool> Parser::function_()
{
    if (handler_.match(TokenKind::kw_fn)) {
        return true;
    }

    if (!detail::peek(handler_).is(TokenKind::identifier)) {
        // TODO ERROR CASE
    }

    auto function_name = detail::peek(handler_).literal();
    handler_.discard();

    template_();

    if (!handler_.match(TokenKind::open_paren)) {
        // TODO ERROR CASE
    }

    function_arguments_();

    if (!handler_.match(TokenKind::close_paren)) {
        // TODO ERROR CASE
    }

    if (!handler_.match(TokenKind::minus)) {
        // TODO ERROR CASE
    }

    if (!handler_.match(TokenKind::grater_then)) {
        // TODO ERROR CASE
    }

    type_();

    stmt_block_();

    return std::nullopt;
}

void Parser::type_()
{
}

void Parser::expr_()
{
}

std::optional<std::vector<std::string>> Parser::template_()
{
    if (handler_.match(TokenKind::less_then)) {
        if (!detail::peek(handler_).is(TokenKind::identifier)) {
            // TODO ERROR CASE
        }

        std::vector<std::string> template_args {};

        template_args.push_back(detail::peek(handler_).literal());
        handler_.discard();

        while (handler_.match(TokenKind::comma)) {
            if (!detail::peek(handler_).is(TokenKind::identifier)) {
                // TODO ERROR CASE
            }

            template_args.push_back(detail::peek(handler_).literal());
            handler_.discard();
        }

        if (!handler_.match(TokenKind::grater_then)) {
            // TODO ERROR CASE
        }

        return template_args;
    }

    return std::nullopt;
}

std::optional<bool> Parser::function_arguments_()
{
    auto arg = member_variable_();

    if (arg.has_value()) {
        while (handler_.match(TokenKind::comma)) {
            auto argg = member_variable_();
            if (!argg.has_value()) {
                // TODO ERROR CASE
            }
        }

        return true;
    }

    return std::nullopt;
}

std::optional<bool> Parser::stmt_block_()
{
    if (handler_.match(TokenKind::open_brace)) {
        while (true) {
            auto stmt = stmt_();
            if (!stmt.has_value()) {
                break;
            }
        }

        if (!handler_.match(TokenKind::close_brace)) {
            // TODO ERROR CASE
        }
    }

    return std::nullopt;
}

std::optional<bool> Parser::member_variable_()
{
    if (detail::peek(handler_).is(TokenKind::identifier)) {
        auto argument_name = detail::peek(handler_).literal();
        handler_.discard();

        if (!handler_.match(TokenKind::colon)) {
            // TODO ERROR CASE
        }

        type_();

        return true;
    }

    return std::nullopt;
}

std::optional<bool> Parser::namespace_()
{
    if (handler_.match(TokenKind::kw_namespace)) {
        if (!detail::peek(handler_).is(TokenKind::identifier)) {
            // TODO ERROR CASE
        }

        auto namespace_name = detail::peek(handler_).literal();

        stmt_block_();

        return true;
    }

    std::nullopt;
}

std::optional<bool> Parser::struct_()
{
    if (handler_.match(TokenKind::kw_struct)) {
        if (!detail::peek(handler_).is(TokenKind::identifier)) {
            // TODO ERROR CASE
        }

        auto struct_name = detail::peek(handler_).literal();
        handler_.discard();

        struct_block_();
    }

    return std::nullopt;
}

void Parser::struct_block_()
{
    if (!handler_.match(TokenKind::open_brace)) {
        // TODO ERROR CASE
    }

    while (true) {
        auto struct_member = member_variable_();
        if (!struct_member.has_value()) {
            break;
        }

        if (!handler_.match(TokenKind::semicolon)) {
            // TODO ERROR CASE
        }
    }

    if (!handler_.match(TokenKind::close_brace)) {
        // TODO ERROR CASE
    }
}

std::optional<bool> Parser::while_()
{
    if (handler_.match(TokenKind::kw_while)) {
        if (!handler_.match(TokenKind::open_paren)) {
            // TODO ERROR CASE
        }

        expr_();

        if (!handler_.match(TokenKind::close_paren)) {
            // TODO ERROR CASE
        }

        single_stmt_();

        stmt_block_();
    }

    return std::nullopt;
}

std::optional<bool> Parser::if_()
{
    if (handler_.match(TokenKind::kw_if)) {
    }

    return std::nullopt;
}

std::optional<bool> Parser::single_stmt_()
{
    if (handler_.match(TokenKind::colon)) {
        stmt_();
    }

    return std::nullopt;
}

std::optional<bool> Parser::stmt_()
{
    return std::nullopt;
}