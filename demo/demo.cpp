#include <cstddef>
#include <string>

#include "utility_cpp.hpp"
#include "sentence_generator.hpp"
#include <iostream>

#include <map>
#include <vector>
#include "grammar.hpp"
#include "monospace_sizer.hpp"
#include <memory>

int main()
{
    auto sentence_generator = Sentence_Generator<
        Grammar<
            std::string,
            std::vector<std::string>,
            std::vector<std::string>::iterator
            >,
        std::string,
        std::vector<std::string>,
        std::vector<std::string>::iterator
        >
        (std::make_unique<Monospace_Sizer<std::string>>());
    sentence_generator.print_grammar(std::cout);
    sentence_generator.shuffle();
    sentence_generator.print_grammar(std::cout);

    for (auto i = 0u; i < 10; ++i)
    {
        auto screen = sentence_generator.get_screen(16, 2);

        std::cout << "---" << std::endl;
        for (auto it = screen.begin(); it < screen.end(); ++it)
        {
            std::cout << *it << std::endl;
        }
        std::cout << "---" << std::endl;
    }
}