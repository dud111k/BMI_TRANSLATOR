#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;

struct WindowState
{
    QString weight;
    QString height;

    QRect geometry;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& language,
                        QWidget *parent = nullptr);

    ~MainWindow();

    WindowState saveWindowState();

    void restoreWindowState(
        const WindowState& state
        );

signals:
    void restartRequested(const QString& lang);

private slots:
    void OnAddClicked();

    void onLanguageChanged();

private:
    void buildUi();

private:
    QString currentLanguage;

    QWidget* central;

    QLineEdit* heightInput;
    QLineEdit* weightInput;

    QLabel* bmiLabel;
    QLabel* answerLabel;

    QLabel* weightLabel;
    QLabel* heightLabel;

    QPushButton* bmiButton;

    QComboBox* langCombo;
};

#endif // MAINWINDOW_H
