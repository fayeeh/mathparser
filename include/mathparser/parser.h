#pragma once

#include "lexer.h"
#include <memory>

namespace mathparser {
    class Parser {
    public:
        Parser(std::string_view);

        std::unique_ptr<Node> parse();

    private:
        Lexer lexer;

        std::unique_ptr<Node> parse_expr();
        std::unique_ptr<Node> parse_term();
        std::unique_ptr<Node> parse_power();
        std::unique_ptr<Node> parse_factor();
    };
} // namespace mathparser
