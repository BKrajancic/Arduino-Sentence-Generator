#ifndef ARDUINO
#define BOOST_TEST_MAIN
#include "utility_cpp.hpp"
#include <boost/test/unit_test.hpp>
#define PC 1
#include "../lib/sentence_generator.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <memory>
#include "grammar.hpp"
#include <vector>
#include "monospace_sizer.hpp"

typedef Grammar<std::string,
                std::vector<std::string>,
                std::vector<std::string>::iterator>
        Grammar_Test;

typedef std::string Word;

typedef std::vector<Word> Sentence;

typedef Sentence_Generator< Grammar_Test,
                            std::string,
                            std::vector<std::string>,
                            std::vector<std::string>::iterator>
        Sentence_Generator_Test;

typedef Monospace_Sizer<std::string> Monospace_Sizer_Test;

BOOST_AUTO_TEST_CASE(ToVec)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("T1"), Word("_2")}};
    g[Word("_2")] = {{Word("T2"), Word("_3")}};
    g[Word("_3")] = {{Word("T3")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);

    const auto str = generator.generate_sentence(Word("_1"));
    const auto expected = {"T1", "T2", "T3"};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.cbegin(), str.cend(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(ToString)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("T1"), Word("_2")}};
    g[Word("_2")] = {{Word("T2")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));
    const auto expected = {Word("T1"), Word("T2")};

    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(First_Is_Transition)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("_2")}};
    g[Word("_2")] = {{Word("T2")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T2")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(LeftGrammar)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("T1"), Word("_2")}};
    g[Word("_2")] = {{Word("T2"), Word("_3")}};
    g[Word("_3")] = {{Word("T3")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T1"), Word("T2"), Word("T3")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(RightGrammar)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("_2"), Word("T1")}};
    g[Word("_2")] = {{Word("_3"), Word("T2")}};
    g[Word("_3")] = {{Word("T3")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T3"), Word("T2"), Word("T1")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(LeftAndRightGrammar)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("_2"), Word("T1")}};
    g[Word("_2")] = {{Word("T2"), Word("_3")}};
    g[Word("_3")] = {{Word("T3")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T2"), Word("T3"), Word("T1")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(NoWhitespace)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("_2"), Word("T1")}};
    g[Word("_2")] = {{Word("T2"), Word("_3")}};
    g[Word("_3")] = {{Word("")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T2"), Word("T1")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Simple)
{
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("T1"), Word("_2")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T1"), Word("_2")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Randomisation_1)
{
    srand(1);
    auto g = Grammar_Test();
    g[Word("_1")] = {{Word("T1"), Word("_2")}, {Word("T2"), Word("_2")}};
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T2"), Word("_2")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}
BOOST_AUTO_TEST_CASE(Randomisation_2)
{
    srand(2);
    auto g = Grammar_Test();
    g[Word("_1")] = {
        {Word("T1"), Word("_2")},
        {Word("T2"), Word("_2")}
    };

    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);

    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("T2"), Word("_2")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());

    const auto str2 = generator.generate_sentence(Word("_1"));
    const auto expected2 = {Word("T1"), Word("_2")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str2.begin(),str2.end(),
                                  expected2.begin(), expected2.end());

    const auto str3 = generator.generate_sentence(Word("_1"));
    BOOST_CHECK_EQUAL_COLLECTIONS(str3.begin(),str3.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(EscapeLoops)
{
    srand(2);
    auto g = Grammar_Test();
    g[Word("_1")] = {
        {Word("Loop"), Word("_1")},
        {Word("")},
        {Word("Loop"), Word("_1")},
        {Word("Loop"), Word("_1")},
    };

    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));
    const auto expected = {Word("Loop"), Word("Loop")};

    BOOST_CHECK_EQUAL_COLLECTIONS(str.cbegin(), str.cend(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(EscapeLoopsNoWhitespace)
{
    srand(2);
    auto g = Grammar_Test();
    g[Word("_1")] = {
        {Word("Loop"), Word("_1")},
        {Word("")},
        {Word("Loop"), Word("_1")},
        {Word("Loop"), Word("_1")}
    };
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    generator.set_grammar(g);
    const auto str = generator.generate_sentence(Word("_1"));

    const auto expected = {Word("Loop"), Word("Loop")};
    BOOST_CHECK_EQUAL_COLLECTIONS(str.begin(),str.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(Repeating_Characters)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    const auto out = generator.repeating_characters(2,"X");
    BOOST_CHECK_EQUAL(out, Word("XX"));
}

BOOST_AUTO_TEST_CASE(Repeating_Characters_empty)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    const auto out = generator.repeating_characters(0,"X");
    BOOST_CHECK_EQUAL(out, Word(""));
}

BOOST_AUTO_TEST_CASE(trim_end_basic)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());

    const auto text = Word("Sample_text ");
    const auto out = generator.trim_end(text);
    BOOST_CHECK_EQUAL(out, Word("Sample_text"));
}

BOOST_AUTO_TEST_CASE(trim_end_do_all)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());

    const auto text = Word("Sample_text    ");
    const auto out = generator.trim_end(text);
    BOOST_CHECK_EQUAL(out, Word("Sample_text"));
}

BOOST_AUTO_TEST_CASE(trim_end_Ignore_Start)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());

    const auto text = Word(" Sample_text");
    const auto out = generator.trim_end(text);
    BOOST_CHECK_EQUAL(out, Word(" Sample_text"));
}

BOOST_AUTO_TEST_CASE(trim_end_Ignore_Middle)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());

    const auto text = Word("Sample text");
    const auto out = generator.trim_end(text);
    BOOST_CHECK_EQUAL(out, Word("Sample text"));
}

BOOST_AUTO_TEST_CASE(trim_end_only_end)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    const auto text = Word(" Sample text ");
    const auto out = generator.trim_end(text);
    BOOST_CHECK_EQUAL(out, Word(" Sample text"));
}

BOOST_AUTO_TEST_CASE(expect_first_empty)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{"0","2","4","6","8"}};
    generator.set_grammar(g);

    const auto empty = generator.get_screen(5, 2);
    const Sentence expected_empty = {Word(), Word()};

    BOOST_CHECK_EQUAL_COLLECTIONS(  empty.begin(), empty.end(),
                                    expected_empty.begin(), expected_empty.end());
}

BOOST_AUTO_TEST_CASE(add_linebreaks_basic)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{"0","2","4","6","8"}};
    generator.set_grammar(g);

    generator.get_screen(5, 2); // Empty
    const auto out = generator.get_screen(5, 2);
    const auto expected = {Word("0 2 4"), Word("6 8")};

    BOOST_CHECK_EQUAL_COLLECTIONS(out.begin(),out.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(not_empty_after)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{"0","2","4","6","8"}};
    generator.set_grammar(g);
    generator.get_screen(5, 2); // empty
    generator.get_screen(5, 2); // content
    const auto out = generator.get_screen(5, 2);
    const auto expected = {Word("0 2 4"), Word("6 8")};

    BOOST_CHECK_EQUAL_COLLECTIONS(out.begin(),out.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(overflow)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{"0123456"}};
    generator.set_grammar(g);
    generator.get_screen(5, 1); // empty
    const auto out1 = generator.get_screen(5, 1);
    const auto out2 = generator.get_screen(5, 1);

    const auto expected1 = {Word("0123-")};
    const auto expected2 = {Word("456")};

    BOOST_CHECK_EQUAL_COLLECTIONS(out1.begin(),out1.end(),
                                expected1.begin(), expected1.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(out2.begin(),out2.end(),
                                expected2.begin(), expected2.end());
}

BOOST_AUTO_TEST_CASE(overflow_elipsis)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{"123", "456"}};
    generator.set_grammar(g);
    generator.get_screen(6, 1); // empty
    const auto out1 = generator.get_screen(6, 1);
    const auto out2 = generator.get_screen(6, 1);

    const auto expected1 = {Word("123...")};
    const auto expected2 = {Word("456")};

    BOOST_CHECK_EQUAL_COLLECTIONS(out1.begin(),out1.end(),
                                expected1.begin(), expected1.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(out2.begin(),out2.end(),
                                expected2.begin(), expected2.end());
}

BOOST_AUTO_TEST_CASE(overflow_but_fits)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{"123", "45"}};
    generator.set_grammar(g);
    generator.get_screen(6, 1); // empty
    const auto out1 = generator.get_screen(6, 1);

    const auto expected1 = {Word("123 45")};

    BOOST_CHECK_EQUAL_COLLECTIONS(out1.begin(),out1.end(),
                                expected1.begin(), expected1.end());

}

BOOST_AUTO_TEST_CASE(overflow_whith_ws)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{"123", "456789"}};
    generator.set_grammar(g);
    generator.get_screen(7, 1); // empty
    const auto out1 = generator.get_screen(7, 1);
    const auto out2 = generator.get_screen(7, 1);

    const auto expected1 = {Word("123...")};
    const auto expected2 = {Word("456789")};
    BOOST_CHECK_EQUAL_COLLECTIONS(out1.begin(),out1.end(),
                                expected1.begin(), expected1.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(out2.begin(),out2.end(),
                            expected2.begin(), expected2.end());
}

BOOST_AUTO_TEST_CASE(test_no_space)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());

    const Sentence text = {{"I[NO_SPACE]"},{"love"}};
    const auto out = generator.run_macros(text);
    const Sentence expect = {{"Ilove"}};

    BOOST_CHECK_EQUAL_COLLECTIONS(
        out.begin(),out.end(),
        expect.begin(), expect.end());
}

BOOST_AUTO_TEST_CASE(test_no_space_lhs_rhs_2)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());

    const Sentence text = {{"I"},{"[NO_SPACE]love"}};
    const auto out = generator.run_macros(text);

    const Sentence expect = {{"Ilove"}};

    BOOST_CHECK_EQUAL_COLLECTIONS(
        out.begin(),out.end(),
        expect.begin(), expect.end());
}

BOOST_AUTO_TEST_CASE(test_no_space_lhs_rhs)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    const Sentence text = {{"I[NO_SPACE]"}, {""}};

    const auto out = generator.run_macros(text);
    const auto out2 = generator.run_macros(text);

    const Sentence expect = {{"I"}};
    BOOST_CHECK_EQUAL_COLLECTIONS(
        out.begin(),out.end(),
        expect.begin(), expect.end());

    BOOST_CHECK_EQUAL_COLLECTIONS(
        out2.begin(),out2.end(),
        expect.begin(), expect.end());
}

BOOST_AUTO_TEST_CASE(demo_pop_size)
{
    auto generator = Sentence_Generator_Test(std::make_unique<Monospace_Sizer<Word>>());
    auto g = Grammar_Test();
    g[Word("<START>")] = {{Word("T1"), Word("_2")}};
    g[Word("_2")] = {{Word("T2"), Word("_3")}};
    g[Word("_3")] = {{Word("T3")}};
    generator.set_grammar(g);

    const auto empty_pop = generator.pop_size(4);
    BOOST_CHECK_EQUAL(empty_pop, Word(""));
    const auto out1 = generator.pop_size(4);
    BOOST_CHECK_EQUAL(generator.size_remaining(), 5);
    BOOST_CHECK_EQUAL(out1, Word("T1"));
    const auto out2 = generator.pop_size(7);
    BOOST_CHECK_EQUAL(out2, Word("T2 T3"));
}

BOOST_AUTO_TEST_CASE(test_sizer)
{
    const auto sizer = Monospace_Sizer_Test();
    BOOST_CHECK_EQUAL(true, sizer.word_fits("12", 5));
    BOOST_CHECK_EQUAL(true, sizer.word_fits("1234", 5));
    BOOST_CHECK_EQUAL(true, sizer.word_fits("12345", 5));
    BOOST_CHECK_EQUAL(false, sizer.word_fits("123456", 5));
}

template <typename Word>
class Test_Sizer : public Sizer<Word>
{
    public:

    Test_Sizer() : Sizer<Word>() {};


    unsigned long size_word(const Word word) const
    {
        auto size = 0u;
        for (auto i = 0u; i < length(word); ++i)
        {
            if (word[i] == '.')
            {
                size += 1;
            }
            else
            {
                size += 2;
            }
        }
        return size;
    };
};

BOOST_AUTO_TEST_CASE(test_sizer)
{


    auto generator = Sentence_Generator_Test(std::make_unique<Test_Sizer<Word>>());

    auto g = Grammar_Test();
    g[Word("<START>")] = {{"1234", "456"}};
    generator.set_grammar(g);
    generator.get_screen(6, 1); // empty
    const auto out1 = generator.get_screen(6, 1);

    const auto expected1 = {Word("123...")};

    BOOST_CHECK_EQUAL_COLLECTIONS(out1.begin(),out1.end(),
                                expected1.begin(), expected1.end());
}

#endif
