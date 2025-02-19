#include "pinscreen.h"
#include "ui_pinscreen.h"
#include <QTimer>
#include "mainwindow.h"

PinScreen::PinScreen(MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::PinScreen)
    , mainWindow(parent)
{
    ui->setupUi(this);
    ui -> textPin -> setReadOnly(true);
    ui -> textPinInfo -> clear();
}

PinScreen::~PinScreen()
{
    delete ui;
}

void PinScreen::on_btnPinNum1_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "1");
}


void PinScreen::on_btnPinNum2_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "2");
}


void PinScreen::on_btnPinNum3_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "3");
}


void PinScreen::on_btnPinNum4_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "4");
}


void PinScreen::on_btnPinNum5_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "5");
}


void PinScreen::on_btnPinNum6_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "6");
}


void PinScreen::on_btnPinNum7_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "7");
}


void PinScreen::on_btnPinNum8_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "8");
}


void PinScreen::on_btnPinNum9_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "9");
}


void PinScreen::on_btnPinNum0_clicked()
{
    ui -> textPin -> setText(ui -> textPin -> text() + "0");
}


void PinScreen::on_btnConfirmPin_clicked()
{
    QString enteredPin = ui -> textPin -> text();
    QString correctPin = "1234"; //hardcoded test pin

    if (enteredPin == correctPin)
    {
        ui -> textPinInfo -> setText("PIN correct");
        ui -> textPinInfo -> setStyleSheet("color: green;");
        pinAttempts = 3;

        QTimer::singleShot(3000, this, [this]()
        {
            ui -> textPinInfo -> clear();
        });

        if (mainWindow)
        {
            mainWindow -> updateUIForDebitCredit();
        }

        this -> close();
    }
    else
    {
        pinAttempts--;
        if (pinAttempts > 0)
        {
            ui -> textPinInfo -> setText(QString("Invalid PIN. %1 attempts remaining.").arg(pinAttempts));
            ui -> textPinInfo -> setStyleSheet("color: red;");
            ui -> textPin -> clear();
            QTimer::singleShot(3000, this, [this]()
            {
                ui -> textPinInfo -> clear();
            });
        }
        else
        {
            ui -> textPinInfo -> setText("Invalid PIN. No attempts remaining. Account locked");
            ui -> textPinInfo -> setStyleSheet("color: red;");
            ui -> textPin -> clear();
            QTimer::singleShot(5000, this, [this]()
            {
                ui -> textPinInfo -> clear();
            });
        }
    }
}


void PinScreen::on_btnClearPin_clicked()
{
    ui -> textPin -> clear();
}


void PinScreen::on_btnUndoPin_clicked()
{
    QString currentText = ui -> textPin -> text();
    if (!currentText.isEmpty())
    {
        currentText.chop(1);
        ui -> textPin -> setText(currentText);
    }
}


void PinScreen::on_btnExit_clicked()
{
    QCoreApplication::quit();
}
