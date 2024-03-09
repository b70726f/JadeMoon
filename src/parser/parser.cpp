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