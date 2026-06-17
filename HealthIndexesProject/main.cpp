#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

MainWindow* createWindow(
    QTranslator& translator,
    QString& currentLanguage,
    WindowState state = {}
    )
{
    MainWindow* window =
        new MainWindow(currentLanguage);

    window->restoreWindowState(state);

    QObject::connect(
        window,
        &MainWindow::languageChanged,
        [&translator,
         &currentLanguage,
         window](const QString& lang)
        {
            currentLanguage = lang;

            WindowState state =
                window->saveWindowState();

            qApp->removeTranslator(
                &translator
                );

            if (lang == "en")
            {
                translator.load("app_en.qm");

                qApp->installTranslator(
                    &translator
                    );
            }

            else
            {
                qApp->removeTranslator(
                    &translator
                    );
            }

            MainWindow* newWindow =
                createWindow(
                    translator,
                    currentLanguage,
                    state
                    );

            newWindow->show();

            window->close();

            window->deleteLater();
        }
        );

    return window;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;

    QString currentLanguage = "ru";

    MainWindow* window =
        createWindow(
            translator,
            currentLanguage
            );

    window->show();

    return a.exec();
}
