#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * w = new MainWindow();
    auto rightArea = w->GetRight();
    w->Layout()->addWidget(rightArea);
    auto leftArea = w->GetLeft();
    w->Layout()->addWidget(leftArea);
    w->show();
    return a.exec();
}
