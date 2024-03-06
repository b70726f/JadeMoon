#include <iostream>

#include "command_line/command_line.hpp"
#include "jmc/types.hpp"
#include "lexer/lexer.hpp"
#include "source/source_file.hpp"

i32 main(i32 argc, char const* argv[])
{
    CommandLine cl(utils::c_string_array_to_string_vector(argc - 1, argv + 1));
    utils::initialize_cli_options(cl);

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