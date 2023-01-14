#include "../include/mathparser/lexer.h"
#include "../include/mathparser/error.h"
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <string_view>

mathparser::Lexer::Lexer(std::string_view input) : input(input), curr('\0'), pos(-1) {
    advance();
}

std::unique_ptr<mathparser::Token> mathparser::Lexer::next_token() {
    std::unique_ptr<mathparser::Token> tok = peek_token();
    auto op = tok->op;
    if (static_cast<int>(op) < 6)
        advance();

    return tok;
}

std::unique_ptr<mathparser::Token> mathparser::Lexer::peek_token() {
    switch (curr) {
    case '+':
        return std::make_unique<Token>(Operator::Plus);
    case '-':
        return std::make_unique<Token>(Operator::Minus);
    case '*':
        return std::make_unique<Token>(Operator::Multiply);
    case '/':
        return std::make_unique<Token>(Operator::Divide);
    case '^':
        return std::make_unique<Token>(Operator::Power);
    case '(':
        return std::make_unique<Token>(Operator::LeftParenthesis);
    case ')':
        return std::make_unique<Token>(Operator::RightParenthesis);
    case ' ':
    case '\t':
    case '\n':
        advance();
        return peek_token();
    default:
        if (std::isdigit(curr)) {
            auto x = get_number();
            return std::make_unique<Token>(x);
        }
        if (std::isalpha(curr)) {
            return get_function();
        }
    }
    throw error::MathParserError::new_error(input, "Unexpected token", pos);
}

bool mathparser::Lexer::has_next() {
    return pos < input.length() - 1;
}

bool mathparser::Lexer::is_curr_null() {
    return curr == '\0';
}

void mathparser::Lexer::advance() {
    if (pos == input.length() - 1) {
        curr = '\0';
        pos++;
    } else {
        curr = input[++pos];
    }
}

std::string mathparser::Lexer::get_input() { return input; }
std::size_t mathparser::Lexer::get_pos() { return pos; }

double mathparser::Lexer::get_number() {
    std::stringstream ss;
    std::size_t dot_count = 0;

    while (curr != '\0' && (std::isdigit(curr) || curr == '.')) {
        if (curr == '.') {
            if (dot_count > 0) {
                throw error::MathParserError::new_error(input, "SyntaxError: invalid syntax", pos);
            }
            ss << '.';
            dot_count++;
            advance();
            continue;
        }
        ss << curr;
        advance();
    }

    std::string str = ss.str();

    return std::stod(str);
}

std::unique_ptr<mathparser::Token> mathparser::Lexer::get_function() {
    std::stringstream ss;

    while (curr != '\0' && (std::isalpha(curr))) {
        ss << curr;
        advance();
    }

    std::string keyword = ss.str();

    if (keyword == "sin") {
        // return new Token(Operator::Sin);
        return std::make_unique<Token>(Operator::Sin);
    } else if (keyword == "cos") {
        // return new Token(Operator::Cos);
        return std::make_unique<Token>(Operator::Cos);
    } else if (keyword == "tan") {
        // return new Token(Operator::Tan);
        return std::make_unique<Token>(Operator::Tan);
    } else if (keyword == "sqrt") {
        // return new Token(Operator::Sqrt);
        return std::make_unique<Token>(Operator::Sqrt);
    } else {
        throw error::MathParserError::new_error(input, std::string("There's no function named: ") + keyword, pos - 1);
    }
}