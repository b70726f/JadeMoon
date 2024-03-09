#pragma once

#include "handlers/source_handler.hpp"
#include "token/token.hpp"

class Parser {
public:
    Parser(std::vector<Token> const&);
    void parse();

private:
    SourceHandler<Token> handler_;
};