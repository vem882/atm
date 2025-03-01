#include "pinscreen.h"
#include "ui_pinscreen.h"
#include <QTimer>
#include "mainwindow.h"
#include "checker.h"

PinScreen::PinScreen(MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::PinScreen)
    , mainWindow(parent)
{
    ui->setupUi(this);

    // Connect signals from MainWindow to PinScreen slots
    connect(mainWindow, &MainWindow::loginSuccessful,
            this, &PinScreen::closeOnSuccess);
    connect(mainWindow, &MainWindow::loginFailed,
            this, &PinScreen::showErrorMessage);

    pinMessageTimer = new QTimer(this);
    pinMessageTimer->setSingleShot(true);
    connect(pinMessageTimer, &QTimer::timeout, this, [this]() {
        ui->textPinInfo->clear();
    });
    ui->textPin->setReadOnly(true);

    Checker checker;
    checker.checkResourceFile(":/Icons/Icons/checkmark.png");
    checker.checkResourceFile(":/Icons/Icons/undo.png");
    checker.checkResourceFile(":/Icons/Icons/X.png");

    QPixmap checkmarkIcon(":/Icons/Icons/checkmark.png");
    QPixmap undoIcon(":/Icons/Icons/undo.png");
    QPixmap xIcon(":/Icons/Icons/X.png");

    ui->btnConfirmPin->setIcon(checkmarkIcon);
    ui->btnClearPin->setIcon(xIcon);
    ui->btnUndoPin->setIcon(undoIcon);

    ui->btnConfirmPin->setStyleSheet("QPushButton { icon-size: 30px 30px; }");
    ui->btnClearPin->setStyleSheet("QPushButton { icon-size: 30px 30px; }");
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
    QString enteredPin = ui->textPin->text();
    QString cardNumber = mainWindow->getCardNumber();

    pinMessageTimer->stop();

    mainWindow->initiateLogin(cardNumber, enteredPin);

}

// Handle success
void PinScreen::closeOnSuccess()
{
    // Close the PIN screen (ends the exec() loop)
    accept();
    if (mainWindow)
    {
        mainWindow -> updateUIForDebitCredit();
    }
}

// Handle failure
void PinScreen::showErrorMessage()
{
    ui->textPinInfo->setText("Login failed");
    pinMessageTimer->start(3000);
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
    this -> close();
}


void PinScreen::resetPinMessageTimer(int timeout)
{
    pinMessageTimer -> start(timeout);
}
