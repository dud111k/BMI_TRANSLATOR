#include "mainwindow.h"

#include <QComboBox>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSignalBlocker>
#include <QVBoxLayout>

MainWindow::MainWindow(
    const QString& language,
    QWidget *parent)
    : QMainWindow(parent),
    currentLanguage(language)
{
    buildUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::buildUi()
{
    central = new QWidget(this);

    setCentralWidget(central);

    QVBoxLayout* mainLayout =
        new QVBoxLayout;

    central->setLayout(mainLayout);

    // Language combo

    langCombo = new QComboBox(this);

    langCombo->addItem("Русский", "ru");
    langCombo->addItem("English", "en");

    {
        QSignalBlocker blocker(langCombo);

        if (currentLanguage == "en")
        {
            langCombo->setCurrentIndex(1);
        }
        else
        {
            langCombo->setCurrentIndex(0);
        }
    }

    mainLayout->addWidget(langCombo);

    connect(
        langCombo,
        QOverload<int>::of(
            &QComboBox::currentIndexChanged
            ),
        this,
        &MainWindow::onLanguageChanged
        );

    // Weight

    weightLabel =
        new QLabel(tr("Введите вес:"), this);

    mainLayout->addWidget(weightLabel);

    weightInput = new QLineEdit(this);

    weightInput->setPlaceholderText(
        tr("кг")
        );

    mainLayout->addWidget(weightInput);

    // Line

    QFrame* line1 = new QFrame();

    line1->setFrameShape(QFrame::HLine);

    mainLayout->addWidget(line1);

    // Height

    heightLabel =
        new QLabel(tr("Введите рост:"), this);

    mainLayout->addWidget(heightLabel);

    heightInput = new QLineEdit(this);

    heightInput->setPlaceholderText(
        tr("см")
        );

    mainLayout->addWidget(heightInput);

    // Line

    QFrame* line2 = new QFrame();

    line2->setFrameShape(QFrame::HLine);

    mainLayout->addWidget(line2);

    // Button

    bmiButton =
        new QPushButton(
            tr("Рассчитать ИМТ"),
            this
            );

    mainLayout->addWidget(bmiButton);

    connect(
        bmiButton,
        &QPushButton::clicked,
        this,
        &MainWindow::OnAddClicked
        );

    // Result

    bmiLabel =
        new QLabel(tr("ИМТ:"), this);

    answerLabel = new QLabel(this);

    mainLayout->addWidget(bmiLabel);

    mainLayout->addWidget(answerLabel);

    resize(400, 300);
}

WindowState MainWindow::saveWindowState()
{
    WindowState state;

    state.weight =
        weightInput->text();

    state.height =
        heightInput->text();

    state.geometry =
        geometry();

    return state;
}

void MainWindow::restoreWindowState(
    const WindowState& state)
{
    weightInput->setText(state.weight);

    heightInput->setText(state.height);

    setGeometry(state.geometry);
}

void MainWindow::OnAddClicked()
{
    bool heightOk;
    bool weightOk;

    double height =
        heightInput->text()
            .toDouble(&heightOk) / 100.0;

    double weight =
        weightInput->text()
            .toDouble(&weightOk);

    if (!heightOk ||
        !weightOk ||
        height <= 0 ||
        weight <= 0)
    {
        QMessageBox::warning(
            this,
            tr("Ошибка"),
            tr("Введите корректные значения роста и веса")
            );

        return;
    }

    QString lang =
        langCombo->currentData().toString();

    double bmi;

    if (lang == "ru")
    {
        bmi =
            weight / (height * height);
    }
    else
    {
        bmi =
            (weight * 703) /
            (height * height * 10000);
    }

    bmiLabel->setText(
        tr("ИМТ: %1")
            .arg(bmi, 0, 'f', 1)
        );

    QString answer;

    if (bmi < 16.0)
    {
        answer =
            tr("Выраженный дефицит веса");
    }
    else if (bmi < 18.5)
    {
        answer =
            tr("Недостаточный вес");
    }
    else if (bmi < 25)
    {
        answer =
            tr("Нормальный вес");
    }
    else if (bmi < 30)
    {
        answer =
            tr("Избыточный вес");
    }
    else if (bmi < 35)
    {
        answer =
            tr("Ожирение 1-й степени");
    }
    else if (bmi < 40)
    {
        answer =
            tr("Ожирение 2-й степени");
    }
    else
    {
        answer =
            tr("Ожирение 3-й степени");
    }

    answerLabel->setText(answer);
}

void MainWindow::onLanguageChanged()
{
    QString lang =
        langCombo->currentData().toString();

    emit restartRequested(lang);
}
