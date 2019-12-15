#pragma once
#include "sizer.hpp"

#include <QFont>
#include <QFontMetrics>

template <typename Word>
class QLabel_Sizer : public Sizer<Word>
{
    public:

    QLabel_Sizer(QFont font)
    : Sizer<Word>()
    , fontMetrics(QFontMetrics(font)) {}

    bool overflow(const Word word, unsigned int size) const override
    {
        return false == word_fits(word, size);
    }

    bool word_fits(const Word word, unsigned int max_size) const override
    {
        return fontMetrics.width(word) <= static_cast<int>(max_size);
    }

    private:
    const QFontMetrics fontMetrics;
};
