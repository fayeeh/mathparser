#include "../include/mathparser/types.h"
#include <iostream>
#include <memory>

mathparser::Token::Token(mathparser::Operator op) {
    value = nullptr;
    this->op = op;
}

mathparser::Token::Token(double num) {
    value = new double;
    *value = num;
    this->op = Operator::Number;
}

mathparser::Token::~Token() {
    if (value != nullptr)
        delete value;
}

mathparser::Node::Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r, NodeType t) : left(std::move(l)), right(std::move(r)) {
    value = nullptr;
    type = t;
}

mathparser::Node::Node(double d) {
    left = nullptr;
    right = nullptr;
    value = new double;
    *value = d;
    type = NodeType::Number;
}

mathparser::Node::~Node() {
    delete value;
}