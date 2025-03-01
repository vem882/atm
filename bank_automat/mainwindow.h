#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtNetwork>
#include <QTimer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTableView>
#include "transactions.h"
#include <QList>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSoundEffect *efx;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateUIForDebitCredit();
    void changeLanguage(const QString &language);
    void initiateLogin(const QString &cardNumber, const QString &pin);
    QString getCardNumber() const;
    QTableView* getTransactionTableView();

signals:
    void loginSuccessful();
    void loginFailed(const QString &errorMsg);

private slots:
    void on_btnStart_clicked();
    void checkATMSerialNumber();

    void on_btnExit_clicked();

    void on_btnCreditAcc_clicked();

    void on_btnDebitAcc_clicked();

    void on_btnReturn_clicked();

    void on_btnSv_clicked();

    void on_btnEn_clicked();

    void on_btnFi_clicked();

    void on_btnDepositDebit_clicked();

    void on_btnWithdrawDebit_clicked();

    void on_btnTransactionsDebit_clicked();

    void on_btnWithdraw10Debit_clicked();

    void on_btnWithdraw20Debit_clicked();

    void on_btnWithdraw50Debit_clicked();

    void on_btnAddCustomWithdrawDebit_clicked();

    void on_btnWithdraw100Debit_clicked();

    void on_btnWithdraw150Debit_clicked();

    void on_btnWithdraw200Debit_clicked();

    void on_btnClearDebitWithdrawValue_clicked();

    void on_btnDebitCustom1_clicked();

    void on_btnDebitCustom2_clicked();

    void on_btnDebitCustom3_clicked();

    void on_btnDebitCustom4_clicked();

    void on_btnDebitCustom5_clicked();

    void on_btnDebitCustom6_clicked();

    void on_btnDebitCustom7_clicked();

    void on_btnDebitCustom8_clicked();

    void on_btnDebitCustom9_clicked();

    void on_btnDebitCustom0_clicked();

    void on_btnHideNumpadDebitWithdraw_clicked();

    void on_btnConfirmWithdrawDebit_clicked();

    void on_btnDebitCustomUndo_clicked();

    void on_btnDebitDepositStart_clicked();

    void onLoginResponse(QNetworkReply *reply);

    void transactionEventsData(QNetworkReply *reply);

    void checkPage();

    //void readData();

    void on_btnTransferPage_clicked();

    void on_btnTransferConfirm_clicked();

    void on_nextButton_clicked();

    void on_previousButton_clicked();

private:
    Ui::MainWindow *ui;
    QStack<int> pageHistory;
    QNetworkAccessManager *networkManager;
    QNetworkAccessManager *transferManager;
    QNetworkAccessManager *transferManagerEvents;
    QNetworkReply *reply;
    QNetworkReply *replyEvents;
    QByteArray data;

    int currentPage = 0;
    int maxPage;
    QTimer *atmCheckTimer;
    QString bearerToken;
    QString atmSerialNumber;
    QString atmLocation;
    QString cardNumber;
    QString cardType;
    int atmId;
    int cardStatus;
    int cardID;
    QString accountNumber;
    int accountID;
    QString accountBalance;
    QString currency_symbol;
    QString customerFirstName;
    QString customerLastName;
    void returnBtnVisibility();
    void updateButtonVisibility();
    QTimer *cardNumMessageTimer;
    void resetCardNumMessageTimer(int timeout);
    int DebitWithdrawNum;
    void appendToDebitWithdrawValue(QString digit);
    QJsonArray transactions;
    QTableView *transactionTableView;
    void displayTransactions();
    void handleLastPage();
    class transactions * eventData;
    QTimer *inactivityTimer;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void resetInactivityTimer();
};

#endif // MAINWINDOW_H
