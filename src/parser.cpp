#include "../include/mathparser/parser.h"
#include "../include/mathparser/error.h"
#include "../include/mathparser/lexer.h"
#include <iostream>
#include <stdexcept>
#include <string_view>

using mathparser::Node;
using mathparser::Parser;

Parser::Parser(std::string_view input) : lexer(input) {}

std::unique_ptr<Node> Parser::parse() {
    if (lexer.is_curr_null())
        throw error::MathParserError::new_error("ParserError: Expression is empty");

    auto tree = parse_expr();

    if (lexer.has_next())
        throw error::MathParserError::new_error("ParserError: Couldn't parse all tokens");

    return tree;
}

std::unique_ptr<Node> Parser::parse_expr() {
    auto result = parse_term();
    while (lexer.has_next()) {
        auto token = lexer.peek_token();
        auto op_int = static_cast<int>(token->op);
        if (op_int > 1)
            break;

        lexer.advance();
        auto x = parse_term();
        result = std::make_unique<Node>(std::move(result), std::move(x), static_cast<NodeType>(op_int));
    }

    return result;
}

std::unique_ptr<Node> Parser::parse_term() {
    auto result = parse_power();

    while (lexer.has_next()) {
        auto token = lexer.peek_token();

        auto op_int = static_cast<int>(token->op);
        if (op_int > 3 || op_int < 2)
            break;
        lexer.advance();
        result = std::make_unique<Node>(std::move(result), parse_power(), static_cast<NodeType>(op_int));
    }

    return result;
}

std::unique_ptr<Node> Parser::parse_power() {
    auto result = parse_factor();

    while (lexer.has_next()) {
        auto token = lexer.peek_token();

        if (token->op != Operator::Power)
            break;

        lexer.advance();
        result = std::make_unique<Node>(std::move(result), parse_factor(), NodeType::Power);
    }

    return result;
}

std::unique_ptr<Node> Parser::parse_factor() {
    auto token = lexer.peek_token();

    switch (token->op) {
    case Operator::LeftParenthesis: {
        lexer.advance();
        auto node = parse_expr();

        auto tok = lexer.peek_token();

        if (tok.get() == nullptr || tok->op != Operator::RightParenthesis)
            throw error::MathParserError::new_error(lexer.get_input(), "SyntaxError: Not Closed Parenthesis", lexer.get_pos());

        lexer.advance();
        return node;
    }
    case Operator::Number: {
        return std::make_unique<Node>(*token->value);
    }
    case Operator::Sin:
    case Operator::Cos:
    case Operator::Abs:
    case Operator::Sqrt: {
        auto next_tok = lexer.peek_token();
        if (next_tok->op != Operator::LeftParenthesis)
            throw error::MathParserError::new_error(lexer.get_input(), "SyntaxError: Unopened Parenthesis", lexer.get_pos());

        auto num = parse_factor();
        return std::make_unique<Node>(std::move(num), nullptr, static_cast<NodeType>(token->op));
    }
    case Operator::Minus: {
        lexer.advance();
        auto next_tok = lexer.peek_token();

        if (next_tok->op == Operator::Minus) {
            return parse_factor();
        }

        if (next_tok->op == Operator::Number) {
            return std::make_unique<Node>(std::make_unique<Node>(*next_tok->value), nullptr, NodeType::Neg);
        }

        return std::make_unique<Node>(parse_factor(), nullptr, NodeType::Neg);
    }
    default:
        throw error::MathParserError::new_error(lexer.get_input(), "SyntaxError: invalid syntax", lexer.get_pos());
    }
}