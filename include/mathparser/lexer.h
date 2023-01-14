#pragma once

#include "types.h"
#include <memory>
#include <string_view>
#include <string>

namespace mathparser {
    class Lexer {
    public:
        Lexer(std::string_view);

        std::unique_ptr<Token> next_token();
        std::unique_ptr<Token> peek_token();

        bool has_next();
        void advance();
        bool is_curr_null();

        std::size_t get_pos();
        std::string get_input();

    private:
        std::string input;
        char curr;
        std::size_t pos;

        std::unique_ptr<Token> get_function();
        double get_number();
    };
} // namespace mathparser
