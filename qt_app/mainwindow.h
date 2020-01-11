#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/qnetworkaccessmanager.h>
#include "sentence_generator_widget.hpp"
#include <QGridLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void pressed(const QString text);

private:
    unsigned int get_width() const;
    Ui::MainWindow *ui;
    Sentence_Generator_Widget* text;

    QNetworkAccessManager* manager;
    QGridLayout* btnLayout;

    const QString source;
    const int rows;
    const int cols;
};
#endif // MAINWINDOW_H
