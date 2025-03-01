#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateUIForDebitCredit();
    void changeLanguage(const QString &language);
    void initiateLogin(const QString &cardNumber, const QString &pin);

private slots:
    void on_btnStart_clicked();
    void on_btnExit_clicked();
    void on_btnCreditAcc_clicked();
    void on_btnDebitAcc_clicked();
    void on_btnReturn_clicked();
    void on_btnSv_clicked();
    void on_btnEn_clicked();
    void on_btnFi_clicked();
    void onLoginResponse(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QStack<int> pageHistory;
    QNetworkAccessManager *networkManager;
    QString bearerToken;
    void returnBtnVisibility();
    void resetCardNumMessageTimer(int timeout);
    int DebitWithdrawNum;
    int CreditWithdrawNum;
    void appendToDebitWithdrawValue(QString digit);
    void appendToCreditWithdrawValue(QString digit);
};

#endif // MAINWINDOW_H