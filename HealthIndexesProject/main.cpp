#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Translator живёт всё время работы приложения
    QTranslator translator;

    MainWindow* w = new MainWindow(&translator);

    w->show();

    return a.exec();
}
