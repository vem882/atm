#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load ATM serial number from settings.json
    QString serialNumber;
    QFile settingsFile("settings.json");
    if (settingsFile.open(QIODevice::ReadOnly)) {
        QByteArray settingsData = settingsFile.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(settingsData);
        QJsonObject jsonObj = jsonDoc.object();
        serialNumber = jsonObj["serialNumber"].toString();
    } else {
        qDebug() << "Could not open settings.json";
        return -1;
    }

    MainWindow w(serialNumber);
    w.show();
    return a.exec();
}