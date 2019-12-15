#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include "personal_info.hpp"
#include "math.h"
#include <QGraphicsDropShadowEffect>
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
    btnLayout->setVerticalSpacing(32);
    btnLayout->setHorizontalSpacing(8);
    for (auto i = 0; i < rows * cols; ++i)
    {
        QPushButton* button = new QPushButton(PERSONAL::URLS[i], this);
        button->setFont(text_font);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnLayout->addWidget(button, cols + (i / rows), i % cols);

        QObject::connect(
            button,
            &QPushButton::released,
            [=]() {this->pressed(PERSONAL::URLS[i]);}
        );

        QPalette button_pal = palette();
        button_pal.setColor(QPalette::Button, QColor(139,0,0));
        button_pal.setColor(QPalette::ButtonText, Qt::white);
        button->setAutoFillBackground(true);
        button->setPalette(button_pal);
        button->setFlat(true);

        QGraphicsDropShadowEffect* button_effect = new QGraphicsDropShadowEffect();
        button_effect->setBlurRadius(3);
        button_effect->setOffset(1, 1);
        button->setGraphicsEffect(button_effect);
    }

    QT_GRAMMAR::Qt_Grammar g = QT_GRAMMAR::Qt_Grammar();
    btnLayout->addWidget(text, 0, 0, 1 ,cols);

#include "../arduino/personal_grammar.hpp"
    text->set_grammar(g);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    text->setAutoFillBackground(true);
    text->setPalette(pal);
    text->setMargin(5);
    text->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    text->setLineWidth(1);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(12);
    effect->setOffset(3,3);
    //text->setGraphicsEffect(effect);


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
    const auto last_cell = btnLayout->cellRect(1,cols - 1);
    const auto end_x = last_cell.x() + last_cell.width();
    const auto right_margin = btnLayout->horizontalSpacing();
    return static_cast<unsigned int>( end_x - (2 * text->margin()) - (right_margin * 2));
}
