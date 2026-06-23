#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

bool needRestart = true;

QString currentLanguage = "ru";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    while (needRestart)
    {
        needRestart = false;

        QTranslator translator;

        if (currentLanguage == "en")
        {
            translator.load("app_en.qm");

            app.installTranslator(&translator);
        }

        MainWindow window(currentLanguage);

        QObject::connect(
            &window,
            &MainWindow::restartRequested,
            [&](const QString& lang)
            {
                currentLanguage = lang;

                needRestart = true;

                app.quit();
            }
            );

        window.show();

        app.exec();

    }

    return 0;
}
