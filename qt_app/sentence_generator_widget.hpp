#ifndef Sentence_Generator_Widget_HPP
#define Sentence_Generator_Widget_HPP

#include "sentence_generator.hpp"
#include "grammar.hpp"
#include <QLabel>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class Sentence_Generator_Widget; }

namespace QT_GRAMMAR {
    typedef QString Word;
    typedef QStringList Sentence;
    typedef QStringList::iterator Sentence_Iterator;
    typedef Grammar<Word, Sentence, Sentence_Iterator> Qt_Grammar;
    typedef Sentence_Generator<Qt_Grammar, Word, Sentence, Sentence_Iterator> Sentence_Generator;
}

QT_END_NAMESPACE

class Sentence_Generator_Widget : public QLabel
{
    Q_OBJECT

public:
    Sentence_Generator_Widget(unsigned int cols, unsigned int rows, QWidget *parent = nullptr);
    ~Sentence_Generator_Widget();
    void next_screen();
    void resize(const unsigned int rows, const unsigned int cols);
    void shuffle();
    void set_grammar(QT_GRAMMAR::Qt_Grammar grammar);
private:
    QT_GRAMMAR::Sentence_Generator sentence_generator;
    QT_GRAMMAR::Qt_Grammar grammar;
    QMutex mutex;
};
#endif // Sentence_Generator_Widget_HPP
