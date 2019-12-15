#pragma once
#ifndef Sentence_Generator_Widget_HPP
#define Sentence_Generator_Widget_HPP

#include "qlabel_sizer.hpp"
#include "sentence_generator.hpp"
#include "grammar.hpp"

#include <QLabel>
#include <QMutex>
#include <QFont>

QT_BEGIN_NAMESPACE
namespace Ui { class Sentence_Generator_Widget; }

namespace QT_GRAMMAR {
    typedef QString Word;
    typedef QStringList Sentence;
    typedef QStringList::iterator Sentence_Iterator;
    typedef Grammar<Word, Sentence, Sentence_Iterator> Qt_Grammar;
    typedef Sentence_Generator<Qt_Grammar, Word, Sentence, Sentence_Iterator> Sentence_Generator;
    typedef QLabel_Sizer<Word> Qt_Sizer;
}

QT_END_NAMESPACE



class Sentence_Generator_Widget : public QLabel
{
    Q_OBJECT

public:
    Sentence_Generator_Widget(QFont font, QWidget *parent = nullptr);
    void next_screen(const unsigned int max_width);
    void set_screen_size(const unsigned int cols, const unsigned int rows);
    void shuffle();
    void set_grammar(QT_GRAMMAR::Qt_Grammar grammar);
private:
    QT_GRAMMAR::Sentence_Generator sentence_generator;
    QT_GRAMMAR::Qt_Grammar grammar;
    QMutex mutex;
};
#endif // Sentence_Generator_Widget_HPP
