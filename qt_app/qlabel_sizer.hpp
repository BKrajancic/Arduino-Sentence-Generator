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

    unsigned long size_word(const Word word) const
    {
        return fontMetrics.width(word);
    }

    private:
    const QFontMetrics fontMetrics;
};
