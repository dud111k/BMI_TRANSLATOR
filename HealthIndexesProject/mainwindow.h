#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

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
    explicit MainWindow(QTranslator* translator,
                        QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void OnAddClicked();
    void onLanguageChanged();

private:
    void buildUi();

    WindowState saveWindowState();
    void restoreWindowState(const WindowState& state);

private:
    // translator теперь хранится pointer-ом
    QTranslator* translator;

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
