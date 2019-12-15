#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    /*
    w.setStyleSheet(
                    "QPushButton {" \
                    "background-color: #D50000;"\
                    "color: white;" \
                    "padding: 0;"
                    "border-width: 0;" \
                    "border-radius: 6px;"\
                    "}"
                    );
                   */
    w.show();
    return a.exec();
}
