#include <QString>
int length(QString str)
{
    return str.length();
}

QString substring(QString str, int start,int end)
{
    QString out;
    for (auto i = start; i < end && i < str.size(); ++i)
    {
        out += str[i];
    }
    return out;
}

#include "sentence_generator_widget.hpp"

Sentence_Generator_Widget::Sentence_Generator_Widget(unsigned int cols, unsigned int rows, QWidget *parent)
    : QLabel(parent)
    , sentence_generator(cols, rows)
    , grammar()
    , mutex()
{}

Sentence_Generator_Widget::~Sentence_Generator_Widget()
{

}

void Sentence_Generator_Widget::set_screen_size(const unsigned int chars_per_row, const unsigned int rows_per_screen)
{
    sentence_generator.resize(chars_per_row, rows_per_screen);
}

void Sentence_Generator_Widget::next_screen()
{
    mutex.lock();
    const auto screen_sentences = sentence_generator.get_screen();
    const auto screen_text = screen_sentences.join("\n");
    setText(screen_text);
    mutex.unlock();
}

void Sentence_Generator_Widget::shuffle()
{
    sentence_generator.shuffle();
}

void Sentence_Generator_Widget::set_grammar(QT_GRAMMAR::Qt_Grammar grammar)
{
    mutex.lock();
    sentence_generator.set_grammar(grammar);
    mutex.unlock();
}
