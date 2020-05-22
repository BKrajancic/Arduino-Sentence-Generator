#pragma once
#include "sizer.hpp"
template <typename Word>
class Monospace_Sizer : public Sizer<Word>
{
    public:

    Monospace_Sizer() : Sizer<Word>() {};

    unsigned long size_word(const Word word) const
    {
        return length(word);
    };
};