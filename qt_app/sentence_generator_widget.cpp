#include <QString>
#include "sentence_generator_widget.hpp"

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

Sentence_Generator_Widget::Sentence_Generator_Widget(const QFont text_font, QWidget *parent)
    : QLabel(parent)
    , sentence_generator(std::make_unique<QT_GRAMMAR::Qt_Sizer>(text_font))
    , grammar()
    , mutex()
{
    this->setFont(text_font);
}

void Sentence_Generator_Widget::next_screen(const unsigned int max_width)
{
    mutex.lock();
    const auto screen_sentences = sentence_generator.get_screen(max_width, 2);
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
