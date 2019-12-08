#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include "personal_info.hpp"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , text(new Sentence_Generator_Widget(32,2))
    , ui(new Ui::MainWindow)
    , source(PERSONAL::REMOTE_URL)
{
    ui->setupUi(this);

    QT_GRAMMAR::Qt_Grammar g = QT_GRAMMAR::Qt_Grammar();
#include "../arduino/personal_grammar.hpp"
    text->set_grammar(g);
    text->setMargin(8);

    manager = new QNetworkAccessManager();


    const auto rows = 3;
    const auto cols = 3;

    QWidget *widget = new QWidget();
    setCentralWidget(widget);
    widget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QGridLayout* btnLayout = new QGridLayout(widget);
    QFont button_font("Arial", 24, QFont::Bold);

    auto button_widths = 0;
    for (auto i = 0; i < rows * cols; ++i)
    {
        QPushButton* const button = new QPushButton(PERSONAL::URLS[i], this);

        button->setFont(button_font);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnLayout->addWidget(button, cols + (i / rows), i % cols);

        QObject::connect(
            button,
            &QPushButton::released,
            [=]() {
                this->pressed(PERSONAL::URLS[i]);
            }
        );
        button_widths += button->width();
    }

    const auto full_width =  (button_widths);
    for (auto i = 0u; i < unsigned(full_width) * 2u; ++i)
    {
        QString demo = "";
        for (auto j = 0u; j < i; ++j)
        {
            demo.push_back('_');
        }

        const auto text_width = text->fontMetrics().boundingRect(demo).width();
        if (text_width >= full_width)
        {
            text->setMaximumWidth(full_width);
            text->resize(i, 2);
            btnLayout->addWidget(text, 0, 0, 1 ,cols);
            break;
        }
    }

    text->shuffle();
    text->next_screen();
    text->next_screen();
}

void MainWindow::pressed(const QString button_text)
{
    QNetworkRequest request;
    const QUrl url = source + button_text;
    request.setUrl(url);
    manager->get(request);
    text->next_screen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
