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

    virtual bool overflow(const Word word,  unsigned int size) const = 0;
    virtual bool word_fits(const Word word, unsigned int size) const = 0;

    void set_elipsis(const Word elipsis)
    {
        this->elipsis = elipsis;
    }

};