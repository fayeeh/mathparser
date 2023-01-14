#include "../include/mathparser/mathparser.h"
#include <cmath>
#include <iostream>

// std::ostream& operator<<(std::ostream& os, std::unique_ptr<mathparser::Node> node) {
//     switch (node->type) {
//     case mathparser::NodeType::Sum:
//         return os << '(' << std::move(node->left) << '+' << std::move(node->right) << ')';
//     case mathparser::NodeType::Subtraction:
//         return os << '(' << std::move(node->left) << '-' << std::move(node->right) << ')';
//     case mathparser::NodeType::Multiplication:
//         return os << '(' << std::move(node->left) << '*' << std::move(node->right) << ')';
//     case mathparser::NodeType::Division:
//         return os << '(' << std::move(node->left) << '/' << std::move(node->right) << ')';
//     case mathparser::NodeType::Power:
//         return os << '(' << std::move(node->left) << '^' << std::move(node->right) << ')';
//     case mathparser::NodeType::Sin:
//         return os << "sin(" << std::move(node->left) << ')';
//     case mathparser::NodeType::Cos:
//         return os << "cos(" << std::move(node->left) << ')';
//     case mathparser::NodeType::Abs:
//         return os << "abs(" << std::move(node->left) << ')';
//     case mathparser::NodeType::Number:
//         return os << *node->value;
//     }
// }

double mathparser::calculate(std::string_view str) {
    Parser parser(str);

    auto tree = parser.parse();

    auto result = eval(std::move(tree));

    return result;
}

double mathparser::eval(std::unique_ptr<Node> node) {
    switch (node->type) {
    case NodeType::Sum:
        return eval(std::move(node->left)) + eval(std::move(node->right));
    case NodeType::Subtraction:
        return eval(std::move(node->left)) - eval(std::move(node->right));
    case NodeType::Number:
        return *node->value;
    case NodeType::Neg:
        return -(eval(std::move(node->left)));
    case NodeType::Power:
        return std::pow(eval(std::move(node->left)), eval(std::move(node->right)));
    case NodeType::Sin:
        return std::sin(eval(std::move(node->left)) * 3.14159265 / 180);
    case NodeType::Cos:
        return std::cos(eval(std::move(node->left)) * 3.14159265 / 180);
    case NodeType::Abs:
        return std::abs(eval(std::move(node->left)));
    case NodeType::Tan:
        return std::tan(eval(std::move(node->left)) * 3.14159265 / 180);
    case NodeType::Sqrt:
        return std::sqrt(eval(std::move(node->left)));
    case NodeType::Multiplication: {
        auto lhs = eval(std::move(node->left));
        auto rhs = eval(std::move(node->right));
        if (lhs == 0 || rhs == 0)
            return 0;
        return lhs * rhs;
    }
    case NodeType::Division: {
        auto rhs = eval(std::move(node->right));
        if (rhs == 0)
            throw error::MathParserError::new_error("ZeroDivisionError: division by zero");
        return eval(std::move(node->left)) / rhs;
    }
    }

    return 0;
}