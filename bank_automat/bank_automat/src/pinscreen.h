#ifndef PINSCREEN_H
#define PINSCREEN_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class MainWindow;

namespace Ui {
class PinScreen;
}

class PinScreen : public QDialog
{
    Q_OBJECT

public:
    explicit PinScreen(MainWindow *parent = nullptr);
    ~PinScreen();

private slots:
    void on_btnPinNum1_clicked();
    void on_btnPinNum2_clicked();
    void on_btnPinNum3_clicked();
    void on_btnPinNum4_clicked();
    void on_btnPinNum5_clicked();
    void on_btnPinNum6_clicked();
    void on_btnPinNum7_clicked();
    void on_btnPinNum8_clicked();
    void on_btnPinNum9_clicked();
    void on_btnPinNum0_clicked();
    void on_btnConfirmPin_clicked();
    void on_btnClearPin_clicked();
    void on_btnUndoPin_clicked();
    void on_btnExit_clicked();
    void handleLoginResponse(QNetworkReply *reply);

private:
    Ui::PinScreen *ui;
    int pinAttempts = 3;
    MainWindow *mainWindow;
    void resetPinMessageTimer(int timeout);
    QTimer *pinMessageTimer;
    QNetworkAccessManager *networkManager;
    QString serialNumber;
    QString cardNumber; // This should be set with the actual card number
};

#endif // PINSCREEN_H