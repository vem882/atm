#ifndef CHECKER_H
#define CHECKER_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class Checker
{
public:
    Checker();
    void checkResourceFile(const QString &path);
    void login(const QString &cardNumber, const QString &pin, const QString &serialNumber);

private:
    QNetworkAccessManager *networkManager;
};

#endif // CHECKER_H