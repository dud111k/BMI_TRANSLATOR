#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void changeEvent(QEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnAddClicked();
    void onLanguageChanged();

private:
    QLineEdit* heightInput;
    QLineEdit* weightInput;
    QLabel* bmiLabel;
    QLabel* answerLabel;
    QComboBox* langCombo;
    QTranslator translator;

    QLabel* weightLabel;
    QLabel* heightLabel;
    QPushButton* bmiButton;
};

#endif // MAINWINDOW_H
