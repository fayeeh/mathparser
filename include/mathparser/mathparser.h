#pragma once

#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "types.h"

namespace mathparser {
    double calculate(std::string_view str);

    double eval(std::unique_ptr<Node> node);
} // namespace mathparser
