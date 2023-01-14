mathparser is a library that calculates math operations from string.

Runs on C++17 or higher version. (Please do not hesitate to tell me if it isn't working, thank you)  

# Example

```cpp
#include <iostream>
#include <mathparser/mathparser.h>

auto main() -> int {
    try {
        auto res = mathparser::calculate("2 + 2");

        std::cout << "Res: " << res << '\n';
    } catch (mathparser::error::MathParserError& e) {
        std::cout << e.what();
    }
    return 0;
}
```

# Build

## Meson
```bash
$ meson build
$ cd build
$ ninja
$ sudo ninja install # Optional
```

# Use with your Project

```meson
# Clone mathparser under <root>/subprojects or install it
project('name', 'cpp', default_options: ['cpp_standart=c++17'])

mathparser_dep = dependency('mathparser', fallback: ['mathparser', 'mathparser_dep'])

executable('main', 
  src/main.cpp,
  dependencies: mathparser_dep,
)

