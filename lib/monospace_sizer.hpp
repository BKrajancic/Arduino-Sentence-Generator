#include "sizer.hpp"
#include "utility_cpp.hpp"
template <typename Word>
class Monospace_Sizer : Sizer<Word>
{
    public:

    Monospace_Sizer(unsigned int width, Word elipsis)
    : Sizer<Word>()
    , width(width)
    , elipsis(elipsis)
    {};

    bool overflow_with_elipsis(const Word word) const
    {
        return length(word + elipsis) > width;
    };

    bool overflow(const Word word) const
    {
        return length(word) > width;
    };

    private:
    unsigned int width;
    Word elipsis;

};