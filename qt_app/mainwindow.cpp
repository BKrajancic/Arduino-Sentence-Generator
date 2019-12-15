#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include "personal_info.hpp"
#include "math.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , text(new Sentence_Generator_Widget(32,2))
    , ui(new Ui::MainWindow)
    , source(PERSONAL::REMOTE_URL)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->setupUi(this);

    QT_GRAMMAR::Qt_Grammar g = QT_GRAMMAR::Qt_Grammar();
#include "../arduino/personal_grammar.hpp"
    text->set_grammar(g);
    text->setMargin(8);

    manager = new QNetworkAccessManager();
    const auto rows = static_cast<int>(sqrt(PERSONAL::URLS.length()));
    const auto cols = (rows) + (rows * rows != PERSONAL::URLS.length());

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
        if (i < cols)
        {
            button_widths += button->width();
        }
    }

    QFont text_font("Arial", 24, QFont::Bold);
    btnLayout->addWidget(text, 0, 0, 1 ,cols);
    text->setFont(text_font);
    text->setMaximumWidth(button_widths);

    for (auto i = 0u; i < unsigned(button_widths) * 2u; ++i)
    {
        QString demo = "";
        for (auto j = 0u; j < i; ++j)
        {
            demo.push_back('_');
        }

        text->setText(demo);
        const auto metrics = text->fontMetrics();
        const auto most_chars = button_widths / metrics.maxWidth();
        const auto text_width = text->fontMetrics().boundingRect(demo).width();
        if (text_width >= button_widths)
        {
            text->set_screen_size(i - 4, 2);
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
