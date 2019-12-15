#pragma once
#include "sizer.hpp"
template <typename Word>
class Monospace_Sizer : public Sizer<Word>
{
    public:

    Monospace_Sizer() : Sizer<Word>() {};

    bool overflow(const Word word, unsigned int size) const override
    {
        return false == word_fits(word, size);
    };

    bool word_fits(const Word word, unsigned int max_size) const override
    {
        return length(word) <= max_size;
    }
};