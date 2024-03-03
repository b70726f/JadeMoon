#include <iostream>

#include "jmc/types.hpp"
#include "lexer/lexer.hpp"
#include "source/source_file.hpp"

i32 main([[maybe_unused]] i32 argc, [[maybe_unused]] char* argv[])
{
    SourceFile sf { "testfile" };
    sf.load();
    auto source = sf.source();
    Lexer lex { source };
    auto tokens = lex.analise();

    std::cout << tokens.capacity();
    for (auto const& token : tokens) {
        std::cout << token.literal() << std::endl;
    }

    return 0;
}