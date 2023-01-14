#pragma once

#include <cctype>
#include <string>

namespace mathparser::error {
    class MathParserError {
    public:
        MathParserError(std::string, std::string, std::size_t);
        MathParserError(std::string);

        static MathParserError new_error(std::string, std::string, std::size_t);
        static MathParserError new_error(std::string);

        char* what();

    private:
        std::string expr;
        std::string msg;
        std::size_t pos;

        std::string generate_message();
    };
} // namespace mathparser::error
