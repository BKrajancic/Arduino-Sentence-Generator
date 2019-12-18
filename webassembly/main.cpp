#include <cstddef>
#include <string>

#include "../lib/utility_cpp.hpp"
#include "../lib/sentence_generator.hpp"
#include <iostream>

#include <map>
#include <vector>
#include "../lib/grammar.hpp"
#include "../lib/monospace_sizer.hpp"
#include <memory>
#include <emscripten/emscripten.h>

typedef Grammar<
            std::string,
            std::vector<std::string>,
            std::vector<std::string>::iterator
            > WASM_Grammar;

typedef Sentence_Generator<
            WASM_Grammar,
            std::string,
            std::vector<std::string>,
            std::vector<std::string>::iterator
        > WASM_Sentence_Generator;
typedef Monospace_Sizer<std::string> WASM_Sizer;

auto generator = WASM_Sentence_Generator(std::make_unique<WASM_Sizer>());

#ifdef __cplusplus
extern "C" {
#endif

void EMSCRIPTEN_KEEPALIVE print()
{
    const auto screen = generator.get_screen(0u - 1, 1);
    std::cout << screen[0];
    std::cout << std::endl;
    std::cout << std::endl;
}
#ifdef __cplusplus
}
#endif
int main()
{
    WASM_Grammar g = WASM_Grammar();
    #include "../arduino/personal_grammar.hpp"
    generator.set_grammar(g);
    generator.shuffle();
    generator.get_screen(0u - 1, 1);

    for (auto i = 0u; i < 2; ++i)
    {
        print();
    }
}

