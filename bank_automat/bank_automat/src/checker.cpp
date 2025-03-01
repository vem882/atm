#include "checker.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

Checker::Checker()
{
}

void Checker::checkResourceFile(const QString &path)
{
    QFile file(path);
    if (!file.exists()) {
        qDebug() << "File not found at path:" << path;
    } else {
        qDebug() << "File found at path:" << path;
    }
}

QString Checker::getBearerToken(const QString &cardNumber, const QString &pin)
{
    QString serialNumber = "SN12345"; // This should ideally be read from settings.json
    QString url = QString("https://api.dev.zroot.it/atm/%1/login").arg(serialNumber);

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["cardNumber"] = cardNumber;
    json["pin"] = pin;

    QNetworkReply *reply = manager.post(request, QJsonDocument(json).toJson());
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            QString token = doc.object().value("token").toString(); // Assuming the token is returned in the response
            qDebug() << "Bearer token received:" << token;
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });

    return QString(); // Return type should be adjusted based on how you want to handle the async nature of the request
}