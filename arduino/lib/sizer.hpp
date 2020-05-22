/*
A sizer will check if characters will fit on a line.
*/
#pragma once

template <typename Word>
class Sizer
{
    public:

    Sizer() {};
    virtual ~Sizer() {};

    virtual unsigned long size_word(const Word word) const = 0;

    bool word_fits(const Word word, unsigned long max_size) const
    {
        return size_word(word) <= max_size;
    }
};
