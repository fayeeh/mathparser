#pragma once

#include <memory>

namespace mathparser {
    enum class Operator {
        Plus,             // +
        Minus,            // -
        Multiply,         // *
        Divide,           // /
        Power,            // ^
        LeftParenthesis,  // (
        RightParenthesis, // )
        Number,           // double
        Sin = 10,         // sin
        Cos,              // cos
        Abs,              // abs
        Tan,              // tan
        Sqrt,             // sqrt
    };

    class Token {
    public:
        Token(Operator);
        Token(double);
        ~Token();

        double* value;
        Operator op;
    };

    enum class NodeType {
        Sum,
        Subtraction,
        Multiplication,
        Division,
        Power,
        Number,
        Neg,
        Sin = 10,
        Cos,
        Abs,
        Tan,
        Sqrt
    };

    class Node {
    public:
        Node(std::unique_ptr<Node>, std::unique_ptr<Node>, NodeType);
        Node(double);
        Node();
        ~Node();

        NodeType type;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        double* value;
    };
} // namespace mathparser
