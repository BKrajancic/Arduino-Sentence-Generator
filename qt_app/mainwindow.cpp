#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include "personal_info.hpp"
#include "math.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , text(new Sentence_Generator_Widget(QFont("Arial", 24, QFont::Bold)))
    , source(PERSONAL::REMOTE_URL)
    , rows (static_cast<int>(sqrt(PERSONAL::URLS.length())))
    , cols ((rows) + (rows * rows != PERSONAL::URLS.length()))
{
    auto text_font = text->font();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->setupUi(this);
    manager = new QNetworkAccessManager();

    QWidget *widget = new QWidget();
    setCentralWidget(widget);
    widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    btnLayout = new QGridLayout(widget);
    for (auto i = 0; i < rows * cols; ++i)
    {
        QPushButton* const button = new QPushButton(PERSONAL::URLS[i], this);

        button->setFont(text_font);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnLayout->addWidget(button, cols + (i / rows), i % cols);

        QObject::connect(
            button,
            &QPushButton::released,
            [=]() {this->pressed(PERSONAL::URLS[i]);}
        );
    }

    QT_GRAMMAR::Qt_Grammar g = QT_GRAMMAR::Qt_Grammar();
    btnLayout->addWidget(text, 0, 0, 1 ,cols);

#include "../arduino/personal_grammar.hpp"
    text->set_grammar(g);
    text->setMargin(8);

    text->shuffle();
    text->next_screen(INT_MAX);
    text->next_screen(INT_MAX);
}

void MainWindow::pressed(const QString button_text)
{
    QNetworkRequest request;
    const QUrl url = source + button_text;
    request.setUrl(url);
    manager->get(request);
    text->next_screen(get_width());
}

MainWindow::~MainWindow()
{
    delete ui;
}

unsigned int MainWindow::get_width() const
{
    auto out = 0u;
    for (auto i = 0; i < cols; ++i)
    {
        out += static_cast<unsigned int>(btnLayout->cellRect(0,i).width());
    }
    return out;
}
