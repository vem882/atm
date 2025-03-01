#include "pinscreen.h"
#include "ui_pinscreen.h"
#include <QTimer>
#include "mainwindow.h"
#include "checker.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

PinScreen::PinScreen(MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::PinScreen)
    , mainWindow(parent)
{
    ui->setupUi(this);

    pinMessageTimer = new QTimer(this);
    pinMessageTimer->setSingleShot(true);
    connect(pinMessageTimer, &QTimer::timeout, this, [this]()
    {
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

    ui->btnConfirmPin->setStyleSheet("QPushButton {""   icon-size: 30px 30px;""}");
    ui->btnClearPin->setStyleSheet("QPushButton {""   icon-size: 30px 30px;""}");
}

PinScreen::~PinScreen()
{
    delete ui;
}

void PinScreen::on_btnConfirmPin_clicked()
{
    QString enteredPin = ui->textPin->text();
    QString cardNumber = "123123123123"; // hardcoded for demonstration
    QString correctPin = "1234"; // hardcoded test pin

    pinMessageTimer->stop();

    if (enteredPin == correctPin)
    {
        // Call API to retrieve bearer token
        QString serialNumber = "SN12345";
        QString url = QString("https://api.dev.zroot.it/atm/%1/login").arg(serialNumber);
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkRequest request(QUrl(url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject json;
        json["cardNumber"] = cardNumber;
        json["pin"] = enteredPin;

        QNetworkReply *reply = manager->post(request, QJsonDocument(json).toJson());

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray response = reply->readAll();
                QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
                QString token = jsonResponse["token"].toString(); // Assuming the token is in the response

                // Store the token for the session
                // You can use a member variable or a settings file to store it

                ui->textPinInfo->setText(tr("Login successful. Token: %1").arg(token));
                ui->textPinInfo->setStyleSheet("color: green;");
                pinAttempts = 3;

                if (mainWindow)
                {
                    mainWindow->updateUIForDebitCredit();
                }

                this->close();
            } else {
                ui->textPinInfo->setText(tr("Login failed: %1").arg(reply->errorString()));
                ui->textPinInfo->setStyleSheet("color: red;");
            }
            reply->deleteLater();
        });
    }
    else
    {
        pinAttempts--;
        if (pinAttempts > 0)
        {
            resetPinMessageTimer(3000);
            ui->textPinInfo->setText(tr("Invalid PIN. %1 attempts remaining.").arg(pinAttempts));
            ui->textPinInfo->setStyleSheet("color: red;");
            ui->textPin->clear();
        }
        else
        {
            ui->textPinInfo->setText(tr("Invalid PIN. No attempts remaining. Account locked."));
            ui->textPinInfo->setStyleSheet("color: red;");
            ui->textPin->clear();
        }
    }
}

// Other button click handlers remain unchanged...