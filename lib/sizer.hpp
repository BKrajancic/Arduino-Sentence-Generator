/*
A sizer will check if characters will fit on a line.
*/

template <typename Word>
class Sizer
{
    public:

    Sizer() {};
    virtual bool overflow_with_elipsis(const Word word) const = 0;
    virtual bool overflow(const Word word) const = 0;
    void set_elipsis(const Word elipsis)
    {
        this->elipsis = elipsis;
    }

};