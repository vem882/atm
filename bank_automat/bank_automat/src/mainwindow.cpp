#include "mainwindow.h"
#include "pinscreen.h"
#include "ui_mainwindow.h"
#include "checker.h"

#include <QTranslator>
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Load ATM serial number from settings.json
    QFile settingsFile("settings.json");
    if (settingsFile.open(QIODevice::ReadOnly)) {
        QByteArray settingsData = settingsFile.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(settingsData);
        QJsonObject jsonObj = jsonDoc.object();
        atmSerialNumber = jsonObj["serialNumber"].toString();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    PinScreen *pinScreen = new PinScreen(this);
    pinScreen->setModal(true);
    connect(pinScreen, &PinScreen::loginSuccessful, this, &MainWindow::handleLoginSuccess);
    pinScreen->exec();
}

void MainWindow::handleLoginSuccess(const QString &token)
{
    // Store the token for the session
    bearerToken = token;
    // Proceed with the application logic after successful login
}

void MainWindow::on_btnExit_clicked()
{
    QApplication::quit();
}

void MainWindow::updateUIForDebitCredit()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui->stackedWidget->currentIndex())
    {
        // Update UI logic here
    }
}

void MainWindow::on_btnDebitAcc_clicked()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui->stackedWidget->currentIndex())
    {
        // Navigate to debit account logic here
    }
}

void MainWindow::on_btnCreditAcc_clicked()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui->stackedWidget->currentIndex())
    {
        // Navigate to credit account logic here
    }
}

void MainWindow::on_btnReturn_clicked()
{
    if (!pageHistory.isEmpty())
    {
        // Logic for returning to the previous page
    }
}

void MainWindow::returnBtnVisibility()
{
    if (ui->stackedWidget->currentIndex() > 1)
    {
        // Show return button logic
    }
    else
    {
        // Hide return button logic
    }
}

void MainWindow::changeLanguage(const QString &language)
{
    // Language change logic here
}

void MainWindow::on_btnSv_clicked()
{
    changeLanguage("sv");
}

void MainWindow::on_btnEn_clicked()
{
    changeLanguage("en");
}

void MainWindow::on_btnFi_clicked()
{
    changeLanguage("fi");
}