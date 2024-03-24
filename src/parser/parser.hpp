#pragma once

#include <optional>

#include "handlers/source_handler.hpp"
#include "token/token.hpp"

class Parser {

public:
    Parser(std::vector<Token> const&);
    void parse();

private:
    std::optional<bool> variable_();
    std::optional<bool> function_();
    void type_();
    void expr_();
    std::optional<std::vector<std::string>> template_();
    std::optional<bool> function_arguments_();
    std::optional<bool> single_stmt_();
    std::optional<bool> stmt_block_();
    std::optional<bool> namespace_();
    std::optional<bool> member_variable_();
    std::optional<bool> struct_();
    void struct_block_();
    std::optional<bool> while_();
    std::optional<bool> if_();
    std::optional<bool> stmt_();

    SourceHandler<Token> handler_;
};