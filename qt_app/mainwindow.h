#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/qnetworkaccessmanager.h>
#include "sentence_generator_widget.hpp"
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
    Sentence_Generator_Widget* text;
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;
    const QString source;
};
#endif // MAINWINDOW_H
