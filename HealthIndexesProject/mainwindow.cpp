#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QComboBox>
#include <QApplication>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget;
    setCentralWidget(centralWidget);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    centralWidget->setLayout(mainLayout);

    langCombo = new QComboBox(this);
    langCombo->addItem("Русский", "ru");
    langCombo->addItem("English", "en");
    mainLayout->addWidget(langCombo);
    connect(langCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onLanguageChanged);

    weightLabel = new QLabel(tr("Введите вес:"), this);
    mainLayout->addWidget(weightLabel);

    weightInput = new QLineEdit;
    weightInput->setPlaceholderText(tr("кг"));
    mainLayout->addWidget(weightInput);

    QFrame* horizontalLine = new QFrame();
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setLineWidth(2);
    mainLayout->addWidget(horizontalLine);

    heightLabel = new QLabel(tr("Введите рост:"), this);
    mainLayout->addWidget(heightLabel);

    heightInput = new QLineEdit();
    heightInput->setPlaceholderText(tr("см"));
    mainLayout->addWidget(heightInput);

    QFrame* horizontalLine1 = new QFrame();
    horizontalLine1->setFrameShape(QFrame::HLine);
    horizontalLine1->setLineWidth(2);
    mainLayout->addWidget(horizontalLine1);

    QFrame* horizontalLine2 = new QFrame();
    horizontalLine2->setFrameShape(QFrame::HLine);
    horizontalLine2->setLineWidth(2);
    mainLayout->addWidget(horizontalLine2);

    bmiButton = new QPushButton(tr("Рассчитать ИМТ"), this);
    mainLayout->addWidget(bmiButton);
    connect(bmiButton, &QPushButton::clicked, this, &MainWindow::OnAddClicked);

    bmiLabel = new QLabel(tr("ИМТ:"), this);
    answerLabel = new QLabel(this);
    mainLayout->addWidget(bmiLabel);
    mainLayout->addWidget(answerLabel);
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnAddClicked()
{
    bool heightOk, weightOk;
    double height = heightInput->text().toDouble(&heightOk) / 100;
    double weight = weightInput->text().toDouble(&weightOk);

    if (!heightOk || !weightOk || height <= 0 || weight <= 0) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Введите корректные значения роста и веса"));
        return;
    }

    QString lang = langCombo->currentData().toString();
    double bmi;
    if (lang == "ru") {
        bmi = weight / (height * height);
    } else {

        bmi = (weight * 703) / (height * height * 10000);
    }

    bmiLabel->setText(tr("ИМТ: %1").arg(bmi, 0, 'f', 1));

    QString answer;
    if (bmi < 16.0) answer = tr("Выраженный дефицит веса");
    else if (bmi < 18.5) answer = tr("Недостаточный вес");
    else if (bmi < 25) answer = tr("Нормальный вес");
    else if (bmi < 30) answer = tr("Избыточный вес");
    else if (bmi < 35) answer = tr("Ожирение 1-й степени");
    else if (bmi < 40) answer = tr("Ожирение 2-й степени");
    else answer = tr("Ожирение 3-й степени");

    answerLabel->setText(answer);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        weightInput->setPlaceholderText(tr("кг"));
        heightInput->setPlaceholderText(tr("см"));
        weightLabel->setText(tr("Введите вес:"));
        heightLabel->setText(tr("Введите рост:"));
        bmiButton->setText(tr("Рассчитать ИМТ"));
        QString lang = langCombo->currentData().toString();
        qApp->removeTranslator(&translator);
        if (lang == "en") {
            translator.load("app_en.qm");
            qApp->installTranslator(&translator);
        }
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::onLanguageChanged()
{
    QString lang = langCombo->currentData().toString();
    qDebug() << "Changing language to:" << lang;

    qApp->removeTranslator(&translator);

    if (lang == "en") {
        if (translator.load("app_en.qm")) {
            qApp->installTranslator(&translator);
            qDebug() << "English loaded";
        }
    }


    weightInput->setPlaceholderText(tr("кг"));
    heightInput->setPlaceholderText(tr("см"));
    weightLabel->setText(tr("Введите вес:"));
    heightLabel->setText(tr("Введите рост:"));
    bmiButton->setText(tr("Рассчитать ИМТ"));

    QString currentBmiText = bmiLabel->text();
    if (currentBmiText.contains(':')) {
        QString number = currentBmiText.section(':', 1).trimmed();
        bmiLabel->setText(tr("ИМТ: %1").arg(number));
    } else {
        bmiLabel->setText(tr("ИМТ:"));
    }


    QString currentAnswer = answerLabel->text();
    if (!currentAnswer.isEmpty()) {
        OnAddClicked();
    }
}
