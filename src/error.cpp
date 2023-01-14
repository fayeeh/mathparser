#include "../include/mathparser/error.h"
#include <cstring>
#include <iostream>
#include <string>

mathparser::error::MathParserError::MathParserError(std::string _expr, std::string _msg, std::size_t _pos) : expr(_expr), msg(_msg), pos(_pos) {}
mathparser::error::MathParserError::MathParserError(std::string _msg) : expr(""), msg(_msg), pos(-1) {}

char* mathparser::error::MathParserError::what() {
    return strdup(generate_message().c_str());
}

std::string mathparser::error::MathParserError::generate_message() {
    if (expr == "")
        return std::string(msg);

    std::string buff = std::string(expr.length(), ' ');

    if (static_cast<int>(pos) > -1)
        buff[pos] = '^';
    else if (pos > expr.length() - 1)
        buff.push_back('^');

    return msg + "\n" + expr + "\n" + buff;
}

mathparser::error::MathParserError mathparser::error::MathParserError::new_error(std::string expr, std::string msg, std::size_t pos) {
    return MathParserError(expr, msg, pos);
}

mathparser::error::MathParserError mathparser::error::MathParserError::new_error(std::string msg) {
    return MathParserError(msg);
}