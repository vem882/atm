#include "mainwindow.h"
#include "pinscreen.h"
#include "ui_mainwindow.h"
#include "checker.h"
#include "env.h"

#include <QTranslator>
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
    , inactivityTimer(new QTimer(this))
{
    ui->setupUi(this);

    this -> setStyleSheet(
        "#stackedWidget { "
        " border-image: url(:Icons/Icons/Bgroungotto.png) 0 0 0 0 stretch stretch;"
        "}");

    inactivityTimer -> setInterval(30000);
    inactivityTimer -> setSingleShot(true);
    connect(inactivityTimer, &QTimer::timeout, this, &MainWindow::on_btnExit_clicked);
    qApp -> installEventFilter(this);
    inactivityTimer -> start();

    // transactionTableView = ui->transactionTableView; // Initialize transactionTableView
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onLoginResponse);

    //initialize withdraw values
    DebitWithdrawNum = 0;
    ui -> textDebitWithdrawValue -> setReadOnly(true);
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));

    //CreditWithdrawNum = 0;
    //initialize message timer for cardNum
    cardNumMessageTimer = new QTimer(this);
    cardNumMessageTimer -> setSingleShot(true);
    connect(cardNumMessageTimer, &QTimer::timeout, this, [this]()
    {
        ui -> textCardNumInfo -> clear();
    });

    //initialize return btn and stackedWidgetIndex
    ui -> stackedWidget -> setCurrentIndex(0);
    ui -> btnReturn -> setVisible(false);

    //check icons
    Checker checker;

    checker.checkResourceFile(":/Icons/Icons/en.png");
    checker.checkResourceFile(":/Icons/Icons/fi.png");
    checker.checkResourceFile(":/Icons/Icons/sv.png");

    checker.checkResourceFile(":/translations/translations/translations_fi.qm");
    checker.checkResourceFile(":/translations/translations/translations_en.qm");
    checker.checkResourceFile(":/translations/translations/translations_sv.qm");
    efx = new QSoundEffect(this);
    efx->setSource(QUrl::fromLocalFile(":/welcomeEN.wav"));
    efx->setVolume(0.90);
    efx->setLoopCount(1);
    efx->play();
   // emit loginSuccessful();  // <--- Signal success

    //set icons
    QPixmap enIcon(":/Icons/Icons/en.png");
    QPixmap fiIcon(":/Icons/Icons/fi.png");
    QPixmap svIcon(":/Icons/Icons/sv.png");
    QPixmap undoIcon(":/Icons/Icons/undo.png");

    ui -> btnEn -> setIcon(enIcon);
    ui -> btnFi -> setIcon(fiIcon);
    ui -> btnSv -> setIcon(svIcon);
    ui -> btnDebitCustomUndo -> setIcon(undoIcon);

    //resize icons
    ui -> btnEn -> setStyleSheet("QPushButton {""   icon-size: 50px 50px;""}");
    ui -> btnFi -> setStyleSheet("QPushButton {""   icon-size: 50px 50px;""}");
    ui -> btnSv -> setStyleSheet("QPushButton {""   icon-size: 50px 50px;""}");
    ui -> btnDebitCustomUndo -> setStyleSheet("QPushButton {""   icon-size: 20px 20px;""}");

    //hiding numpad buttons initially
    ui -> btnDebitCustom0 -> setVisible(false);
    ui -> btnDebitCustom1 -> setVisible(false);
    ui -> btnDebitCustom2 -> setVisible(false);
    ui -> btnDebitCustom3 -> setVisible(false);
    ui -> btnDebitCustom4 -> setVisible(false);
    ui -> btnDebitCustom5 -> setVisible(false);
    ui -> btnDebitCustom6 -> setVisible(false);
    ui -> btnDebitCustom7 -> setVisible(false);
    ui -> btnDebitCustom8 -> setVisible(false);
    ui -> btnDebitCustom9 -> setVisible(false);
    ui -> btnHideNumpadDebitWithdraw -> setVisible(false);
    ui -> btnDebitCustomUndo -> setVisible(false);
    ui -> btnExit -> setVisible(false);

    eventData = new class transactions(this);
    eventData->setTableView(ui->transactionTableView); // Set the table view
    eventData->setCurrencySymbol(currency_symbol); // Set the currency symbol
    ui -> transactionTableView -> verticalHeader() -> setVisible(false);
  // connect(ui->btnNextPage, &QPushButton::clicked, this, &MainWindow::nextPage);
  // connect(ui->btnPreviousPage, &QPushButton::clicked, this, &MainWindow::previousPage);


    atmCheckTimer = new QTimer(this);
    connect(atmCheckTimer, &QTimer::timeout, this, &MainWindow::checkATMSerialNumber);
    //atmCheckTimer->start(100000); // 10 sekunnin välein
}

void MainWindow::checkATMSerialNumber() {
    QFile settingsFile(":/settings.json");
    if (!settingsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open settings file.";
        return;
    }

    QJsonDocument settingsDoc = QJsonDocument::fromJson(settingsFile.readAll());
    QString atmSerialNumber = settingsDoc.object().value("atmserialnro").toString();
    settingsFile.close();

    QUrl url(env::getUrl() + "/ping");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("serialNumber", atmSerialNumber.toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObject = responseDoc.object(); // Muunna JSON-dokumentti JSON-objektiksi

            // Tarkista, onko "sn" avain olemassa
            if (jsonObject.contains("sn")) {
                QJsonValue snValue = jsonObject["sn"]; // Hae "sn" arvo

                bool sn = false; // Oletusarvo false

                // Tarkista, onko arvo boolean tai merkkijono
                if (snValue.isBool()) {
                    sn = snValue.toBool(); // Jos arvo on boolean, käytä sitä suoraan
                } else if (snValue.isString()) {
                    QString snString = snValue.toString().toLower(); // Muunna merkkijono pieniksi kirjaimiksi
                    sn = (snString == "true"); // Muunna merkkijono booleaniksi
                }

                if (!sn) { // Tarkista, onko sn false
                    // Siirry näkymään 8, jos sarjanumero ei ole kelvollinen
                    ui->stackedWidget->setCurrentIndex(8);
                    qDebug() << "ATM serial number is not valid. Switching to error view.";
                } else {
                    // sn on true, joten jatka normaalia toimintaa
                    qDebug() << "ATM serial number is valid.";
                }
            }
        }
        reply->deleteLater(); // Poista reply olio
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    //atmCheckTimer->stop();
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove ||
        event->type() == QEvent::KeyPress ||
        event->type() == QEvent::TouchBegin)
    {
        resetInactivityTimer();
    }
    return QMainWindow::eventFilter(obj, event);
}


void MainWindow::resetInactivityTimer()
{
    inactivityTimer->start();
    //qDebug() << "timer reset";
}


void MainWindow::on_btnStart_clicked()
{
    cardNumber = ui->cardNumberInput->text(); // Retrieve the card number from the input field
    if (!cardNumber.isEmpty())
    {
        // Proceed to PIN screen
        PinScreen pinScreen(this);
        pinScreen.exec();
    }
    else
    {
        // Handle empty card number input
        //qDebug() << "Card number is empty.";
    }
}


void MainWindow::on_btnExit_clicked()
{
    // Reset session data
    bearerToken.clear();
    atmSerialNumber.clear();
    atmLocation.clear();
    cardNumber.clear();
    cardID = 0;
    cardType.clear();
    cardStatus = 0;
    accountNumber.clear();
    accountID = 0;
    currency_symbol.clear();
    accountBalance.clear();
    customerFirstName.clear();
    customerLastName.clear();
    ui->cardNumberInput->clear();
    currentPage = 1;
    maxPage = 1;

    // Reset UI elements
    ui->stackedWidget->setCurrentIndex(0);
    returnBtnVisibility();

    // Optionally, reset button visibility
    ui->btnCreditAcc->setVisible(true);
    ui->btnDebitAcc->setVisible(true);
    ui->btnDepositDebit->setVisible(true);
    ui->btnWithdrawDebit->setVisible(true);
    ui -> btnFi -> setVisible(true);
    ui -> btnEn -> setVisible(true);
    ui -> btnSv -> setVisible(true);
}

void MainWindow::onLoginResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
        //qDebug() << "" << responseDoc;

        // Store the token
        bearerToken = responseDoc.object().value("token").toString();
        //qDebug() << "Login successful, token:" << bearerToken;

        // Store ATM details
        QJsonObject atmObj = responseDoc.object().value("atm").toObject();
        atmSerialNumber = atmObj.value("serial_number").toString();
        atmLocation = atmObj.value("location").toString();
        atmId = atmObj.value("idatm").toInt();

        // Store card details
        QJsonObject cardObj = responseDoc.object().value("card").toObject();
        cardNumber = cardObj.value("cardNumber").toString();
        cardStatus = cardObj.value("status").toInt();
        cardType = cardObj.value("cardType").toString();
        cardID = cardObj.value("cardID").toInt();

        // Store account details
        QJsonObject accountObj = cardObj.value("account").toObject();
        accountNumber = accountObj.value("accountNumber").toString();
        accountID = accountObj.value("accountID").toInt();
        currency_symbol = accountObj.value("currency_symbol").toString();
        accountBalance = accountObj.value("balance").toString();

        // Store customer details
        QJsonObject customerObj = cardObj.value("customer").toObject();
        customerFirstName = customerObj.value("firstName").toString();
        customerLastName = customerObj.value("lastName").toString();

        // Update button visibility based on card type
        updateButtonVisibility();



    emit loginSuccessful();  // <--- Signal success
    } else {
        //qDebug() << "Login failed:" << reply->errorString();
        efx = new QSoundEffect(this);
        efx->setSource(QUrl::fromLocalFile(":/LoginFail_EN.wav"));
        efx->setVolume(0.90);
        efx->setLoopCount(1);
        efx->play();
        emit loginFailed(reply->errorString()); // <--- Signal error msg
    }
    reply->deleteLater();
}

void MainWindow::updateUIForDebitCredit()
{
    //setting balance
    ui-> accountBalanceDebit -> setText(QString("%1").arg(accountBalance));

    ui->textWelcomeDebit->setText(QString(tr("Welcome %1!")).arg(customerFirstName));

    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        //qDebug() << "Added page to history:" << ui -> stackedWidget -> currentIndex();
    }
    if(cardType == "debit")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(cardType == "credit")
    {
       ui->stackedWidget->setCurrentIndex(2);
    }
    else if(cardType == "combination")
    {
        ui -> stackedWidget -> setCurrentIndex(1);
        returnBtnVisibility();
    }
    ui -> btnExit -> setVisible(true);
}


void MainWindow::on_btnDebitAcc_clicked()
{
    ui->btnDepositDebit->setVisible(true);

    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        //qDebug() << "Added page to history:" << ui -> stackedWidget -> currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(2);
    returnBtnVisibility();
}


void MainWindow::on_btnCreditAcc_clicked()
{
    ui->btnDepositDebit->setVisible(false);

    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        //qDebug() << "Added page to history:" << ui -> stackedWidget -> currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(2);
    returnBtnVisibility();
}


void MainWindow::on_btnReturn_clicked()
{
    if (!pageHistory.isEmpty())
    {
        int lastPage = pageHistory.pop();
        //qDebug() << "navigating back to page:" << lastPage;
        //qDebug() << "remaining page history:" << pageHistory;

        if ((ui -> stackedWidget -> currentIndex() == 2 || ui -> stackedWidget -> currentIndex() == 3) && lastPage == 1)
        {
            ui -> stackedWidget -> setCurrentIndex(1);
            pageHistory.push(1);
        }
        else
        {
            ui -> stackedWidget -> setCurrentIndex(lastPage);
        }

        returnBtnVisibility();
    }
}


void MainWindow::returnBtnVisibility()
{
    if (ui -> stackedWidget -> currentIndex() > 2)
    {
        ui -> btnReturn -> setVisible(true);
    }
    else
    {
        ui -> btnReturn -> setVisible(false);
    }

    if(ui -> stackedWidget -> currentIndex() == 0)
    {
        ui -> btnExit -> setVisible(false);
    }
    else
    {
        ui -> btnExit -> setVisible(true);
    }
}


void MainWindow::changeLanguage(const QString &language)
{
    QTranslator *translator = new QTranslator(this);

    if (language == "fi")
    {
        translator -> load(":/translations/translations/translations_fi");
    }
    else if (language == "sv")
    {
        translator -> load(":/translations/translations/translations_sv");
    }
    else if (language == "en")
    {
        translator -> load(":/translations/translations/translations_en");
    }

    qApp -> installTranslator(translator);
    ui -> retranslateUi(this);
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


void MainWindow::resetCardNumMessageTimer(int timeout)
{
    cardNumMessageTimer -> start(timeout);
}


//Debit sivun napit
void MainWindow::on_btnDepositDebit_clicked()
{
    ui -> textDebitDepositAmount -> setVisible(false);
    ui -> btnDebitDepositStart -> setVisible(true);
    ui -> textDebitDepositMessage -> setVisible(false);
    ui -> textDebitDepositGuideMessage -> setVisible(true);

    ui -> textDebitDepositGuideMessage -> setText(tr("Insert bills into the machine"));

    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        //qDebug() << "Added page to history:" << ui -> stackedWidget -> currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(3);
    returnBtnVisibility();
}


void MainWindow::on_btnWithdrawDebit_clicked()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        //qDebug() << "Added page to history:" << ui -> stackedWidget -> currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(5);
    returnBtnVisibility();
}


void MainWindow::on_btnTransactionsDebit_clicked()
{
    maxPage = 1;
    currentPage = 1;
    if (pageHistory.isEmpty() || pageHistory.top() != ui->stackedWidget->currentIndex())
    {
        pageHistory.push(ui->stackedWidget->currentIndex());
        //qDebug() << "Added page to history:" << ui->stackedWidget->currentIndex();
    }

    // Fetch transactions from the API
    QFile settingsFile(":/settings.json");
    if (!settingsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qDebug() << "Failed to open settings file.";
        return;
    }

    QJsonDocument settingsDoc = QJsonDocument::fromJson(settingsFile.readAll());
    QString atmSerialNumber = settingsDoc.object().value("atmserialnro").toString();
    settingsFile.close();
    QJsonObject sentData;
    // Get the account ID from the login
    QString accountID = QString::number(this->accountID);

    // Construct the URL with the account ID
    QString  url = env::getUrl() + "/transactions/history/" + accountID;
    QNetworkRequest request(url);
    // Create the request
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray myToken="Bearer "+bearerToken.toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setRawHeader("serialnumber", atmSerialNumber.toUtf8());

    transferManagerEvents = new QNetworkAccessManager(this);
    connect(transferManagerEvents, SIGNAL(finished(QNetworkReply*)), this, SLOT(transactionEventsData(QNetworkReply*)));

    replyEvents = transferManagerEvents->get(request, QJsonDocument(sentData).toJson());


    // Change the current page to the transactions page
}
void MainWindow::transactionEventsData(QNetworkReply *reply) {
    QByteArray data = reply->readAll();

    if (data.length() == 0 || data == "-4078") {
        //qDebug() << "Network error";
        reply->deleteLater();
        transferManagerEvents->deleteLater();
        return;
    }

    if (data == "false") {
        //qDebug() << "Can't get data from source";
        reply->deleteLater();
        transferManagerEvents->deleteLater();
        return;
    }

    // Aseta transaktiosivu näkyväksi
    ui->stackedWidget->setCurrentIndex(4); // page_6 (indeksi 5)

    // Liitä taulukkonäkymä
    eventData->attachWindow(ui->stackedWidget->widget(5)); // Välitä oikea widgetti

    // Käsittele data
    eventData->getEventSlot(data);
    maxPage = eventData->addEvents(currentPage);
    checkPage();

    replyEvents->deleteLater();
    transferManagerEvents->deleteLater();
    returnBtnVisibility();
}


void MainWindow::checkPage()
{
    ui -> previousButton -> setVisible(currentPage > 1);
    ui -> nextButton -> setVisible(currentPage < maxPage);

    ui -> transactionsPageInfo -> setText(tr("Page  %1 / %2").arg(currentPage).arg(maxPage));
}


//Debit deposit page
void MainWindow::on_btnWithdraw10Debit_clicked()
{
    DebitWithdrawNum = 10;
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));
}


void MainWindow::on_btnWithdraw20Debit_clicked()
{
    DebitWithdrawNum = 20;
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));
}


void MainWindow::on_btnWithdraw50Debit_clicked()
{
    DebitWithdrawNum = 50;
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));
}


void MainWindow::on_btnWithdraw100Debit_clicked()
{
    DebitWithdrawNum = 100;
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));
}


void MainWindow::on_btnWithdraw150Debit_clicked()
{
    DebitWithdrawNum = 150;
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));
}


void MainWindow::on_btnWithdraw200Debit_clicked()
{
    DebitWithdrawNum = 200;
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));
}


void MainWindow::on_btnClearDebitWithdrawValue_clicked()
{
    DebitWithdrawNum = 0;
    ui -> textDebitWithdrawValue -> setText(QString::number(DebitWithdrawNum));
    ui -> textDebitWithdrawMsg -> clear();
}


void MainWindow::on_btnAddCustomWithdrawDebit_clicked()
{
    //numpad buttons
    ui -> btnDebitCustom0 -> setVisible(true);
    ui -> btnDebitCustom1 -> setVisible(true);
    ui -> btnDebitCustom2 -> setVisible(true);
    ui -> btnDebitCustom3 -> setVisible(true);
    ui -> btnDebitCustom4 -> setVisible(true);
    ui -> btnDebitCustom5 -> setVisible(true);
    ui -> btnDebitCustom6 -> setVisible(true);
    ui -> btnDebitCustom7 -> setVisible(true);
    ui -> btnDebitCustom8 -> setVisible(true);
    ui -> btnDebitCustom9 -> setVisible(true);
    ui -> btnHideNumpadDebitWithdraw -> setVisible(true);
    ui -> btnDebitCustomUndo -> setVisible(true);

    //set value buttons visible
    ui -> btnWithdraw10Debit -> setVisible(false);
    ui -> btnWithdraw20Debit -> setVisible(false);
    ui -> btnWithdraw50Debit -> setVisible(false);
    ui -> btnWithdraw100Debit -> setVisible(false);
    ui -> btnWithdraw150Debit -> setVisible(false);
    ui -> btnWithdraw200Debit -> setVisible(false);
}


void MainWindow::appendToDebitWithdrawValue(QString digit)
{
    QString currentText = ui -> textDebitWithdrawValue -> text();

    if (currentText == "0")
    {
        currentText.clear();
    }

    currentText.append(digit);

    int value = currentText.toInt();

    if (value > 2000)
    {
        value = 2000;
    }

    ui -> textDebitWithdrawValue -> setText(QString::number(value));
    DebitWithdrawNum = value;
}


void MainWindow::on_btnDebitCustom1_clicked()
{
    appendToDebitWithdrawValue("1");
}


void MainWindow::on_btnDebitCustom2_clicked()
{
    appendToDebitWithdrawValue("2");
}


void MainWindow::on_btnDebitCustom3_clicked()
{
    appendToDebitWithdrawValue("3");
}


void MainWindow::on_btnDebitCustom4_clicked()
{
    appendToDebitWithdrawValue("4");
}


void MainWindow::on_btnDebitCustom5_clicked()
{
    appendToDebitWithdrawValue("5");
}


void MainWindow::on_btnDebitCustom6_clicked()
{
    appendToDebitWithdrawValue("6");
}


void MainWindow::on_btnDebitCustom7_clicked()
{
    appendToDebitWithdrawValue("7");
}


void MainWindow::on_btnDebitCustom8_clicked()
{
    appendToDebitWithdrawValue("8");
}


void MainWindow::on_btnDebitCustom9_clicked()
{
    appendToDebitWithdrawValue("9");
}


void MainWindow::on_btnDebitCustom0_clicked()
{
    appendToDebitWithdrawValue("0");
}


void MainWindow::on_btnHideNumpadDebitWithdraw_clicked()
{
    //numpad buttons
    ui -> btnDebitCustom0 -> setVisible(false);
    ui -> btnDebitCustom1 -> setVisible(false);
    ui -> btnDebitCustom2 -> setVisible(false);
    ui -> btnDebitCustom3 -> setVisible(false);
    ui -> btnDebitCustom4 -> setVisible(false);
    ui -> btnDebitCustom5 -> setVisible(false);
    ui -> btnDebitCustom6 -> setVisible(false);
    ui -> btnDebitCustom7 -> setVisible(false);
    ui -> btnDebitCustom8 -> setVisible(false);
    ui -> btnDebitCustom9 -> setVisible(false);
    ui -> btnHideNumpadDebitWithdraw -> setVisible(false);
    ui -> btnDebitCustomUndo -> setVisible(false);

    //set value buttons visible
    ui -> btnWithdraw10Debit -> setVisible(true);
    ui -> btnWithdraw20Debit -> setVisible(true);
    ui -> btnWithdraw50Debit -> setVisible(true);
    ui -> btnWithdraw100Debit -> setVisible(true);
    ui -> btnWithdraw150Debit -> setVisible(true);
    ui -> btnWithdraw200Debit -> setVisible(true);

    ui -> btnConfirmWithdrawDebit -> setVisible(true);
    ui -> btnAddCustomWithdrawDebit -> setVisible(true);
    ui -> btnClearDebitWithdrawValue -> setVisible(true);
}


void MainWindow::on_btnConfirmWithdrawDebit_clicked()
{
    int withdrawAmount = ui -> textDebitWithdrawValue -> text().toInt();
    //qDebug() << "account balance: " << accountBalance;
    //qDebug() << "transfer amount: " << withdrawAmount;

    if (accountBalance.toDouble() >= withdrawAmount)
    {
        if (withdrawAmount > 0 && withdrawAmount % 10 == 0)
        {
            QJsonObject json;
            json["account_id"] = QString::number(accountID);
            json["amount"] = withdrawAmount;
            json["idatm"] = atmId;
            json["idcard"] = cardID;

            QUrl url(env::getUrl() + "/transactions/withdraw");
            QNetworkRequest request(url);
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            QByteArray myToken = "Bearer " + bearerToken.toUtf8();
            request.setRawHeader(QByteArray("Authorization"), myToken);
            request.setRawHeader("serialnumber", atmSerialNumber.toUtf8());

            QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());
            connect(reply, &QNetworkReply::finished, this, [this, reply, withdrawAmount]()
            {
                if (reply->error() == QNetworkReply::NoError)
                {
                    ui -> textDebitWithdrawProcess -> setText(tr("Processing..."));

                    ui -> btnReturn -> setVisible(false);
                    ui -> btnDebitCustom0 -> setVisible(false);
                    ui -> btnDebitCustom1 -> setVisible(false);
                    ui -> btnDebitCustom2 -> setVisible(false);
                    ui -> btnDebitCustom3 -> setVisible(false);
                    ui -> btnDebitCustom4 -> setVisible(false);
                    ui -> btnDebitCustom5 -> setVisible(false);
                    ui -> btnDebitCustom6 -> setVisible(false);
                    ui -> btnDebitCustom7 -> setVisible(false);
                    ui -> btnDebitCustom8 -> setVisible(false);
                    ui -> btnDebitCustom9 -> setVisible(false);
                    ui -> btnHideNumpadDebitWithdraw -> setVisible(false);
                    ui -> btnDebitCustomUndo -> setVisible(false);
                    ui -> btnWithdraw10Debit -> setVisible(false);
                    ui -> btnWithdraw20Debit -> setVisible(false);
                    ui -> btnWithdraw50Debit -> setVisible(false);
                    ui -> btnWithdraw100Debit -> setVisible(false);
                    ui -> btnWithdraw150Debit -> setVisible(false);
                    ui -> btnWithdraw200Debit -> setVisible(false);
                    ui -> btnConfirmWithdrawDebit -> setVisible(false);
                    ui -> btnAddCustomWithdrawDebit -> setVisible(false);
                    ui -> btnClearDebitWithdrawValue -> setVisible(false);

                    QTimer::singleShot(3000, this, [this, withdrawAmount]()
                    {
                        ui -> textDebitWithdrawProcess -> clear();
                        ui->textDebitWithdrawMsg->setText(tr("%1 Withdrawn").arg(withdrawAmount));
                        ui->textDebitWithdrawMsg->setStyleSheet("color: green;");
                        DebitWithdrawNum = 0;
                        ui->textDebitWithdrawValue->setText("0");

                        QTimer::singleShot(4000, this, [this]()
                        {
                            handleLastPage();
                        });
                    });
                }
                else
                {
                    ui->textDebitWithdrawMsg->setText(tr("Withdrawal failed: %1").arg(reply->errorString()));
                    ui->textDebitWithdrawMsg->setStyleSheet("color: red;");
                }
                reply->deleteLater();
            });
        }
        else
        {
            ui -> textDebitWithdrawMsg -> setText(tr("%1 Amount is invalid to withdraw").arg(withdrawAmount));
            ui -> textDebitWithdrawMsg -> setStyleSheet("color: red;");
        }
    }
    else
    {
        ui -> textDebitWithdrawMsg -> setText(tr("Invalid funds"));
        ui -> textDebitWithdrawMsg -> setStyleSheet("color: red;");

        QTimer::singleShot(3000, this, [this]()
        {
            ui -> textDebitWithdrawMsg -> clear();
        });
    }
}


void MainWindow::on_btnDebitCustomUndo_clicked()
{
    QString currentText = ui -> textDebitWithdrawValue -> text();
    if (!currentText.isEmpty())
    {
        currentText.chop(1);
        ui -> textDebitWithdrawValue -> setText(currentText);
    }
    else
    {
        ui -> textDebitWithdrawValue -> clear();
    }

    DebitWithdrawNum = currentText.toInt();
    ui -> textDebitWithdrawMsg -> clear();
}


void MainWindow::on_btnDebitDepositStart_clicked()
{
    ui -> textDebitDepositGuideMessage -> setVisible(false);
    ui -> btnDebitDepositStart -> setVisible(false);
    ui -> textDebitDepositMessage -> setVisible(true);
    ui -> btnReturn -> setVisible(false);
    ui -> textDebitDepositMessage -> setText(tr("Processing..."));
   // connect(this, &MainWindow::loginSuccessful, this, &MainWindow::updateUIForDebitCredit);
    efx = new QSoundEffect(this);
    efx->setSource(QUrl::fromLocalFile(":/deposit.wav"));
    efx->setVolume(0.90);
    efx->setLoopCount(1);
    efx->play();

    // Simulate processing delay
    QTimer::singleShot(3000, this, [this]()
    {
        int randomNumber = QRandomGenerator::global() -> bounded(1, 101);
        int result = randomNumber * 10;
        // Prepare the deposit request
        QJsonObject json;
        json["account_id"] = QString::number(accountID);
        json["amount"] = result;
        json["idatm"] = QString::number(atmId);
        json["idcard"] = QString::number(cardID);
        qDebug() << json;

        QUrl url(env::getUrl() + "/transactions/deposit");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray myToken = "Bearer " + bearerToken.toUtf8();
        request.setRawHeader(QByteArray("Authorization"), myToken);
        request.setRawHeader("serialnumber", atmSerialNumber.toUtf8());

        QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply, result]()
        {
            if (reply->error() == QNetworkReply::NoError)
            {

                ui->textDebitDepositMessage->setText(tr("Deposit successful!"));
                ui->textDebitDepositMessage->setStyleSheet("color: green;");

                ui -> textDebitDepositAmount -> setVisible(true);
                ui -> textDebitDepositAmount -> setText(tr("%1 Added to balance").arg(result));


                // Update account balance (example, replace with actual logic)
                accountBalance = QString::number(accountBalance.toDouble() + result); // Example amount
                ui->accountBalanceDebit->setText(accountBalance);

                QTimer::singleShot(4000, this, [this]()
                {
                    handleLastPage();
                });
            }
            else
            {
                ui->textDebitDepositMessage->setText(tr("Deposit failed: %1").arg(reply->errorString()));
                ui->textDebitDepositMessage->setStyleSheet("color: red;");
            }
            reply->deleteLater();
        });
    });
}


void MainWindow::initiateLogin(const QString &cardNumber, const QString &pin)
{
    QFile settingsFile(":/settings.json");
    if (!settingsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qDebug() << "Failed to open settings file.";
        return;
    }

    QJsonDocument settingsDoc = QJsonDocument::fromJson(settingsFile.readAll());
    QString atmSerialNumber = settingsDoc.object().value("atmserialnro").toString();
    settingsFile.close();

    QUrl url(env::getUrl() + "/atm/" + atmSerialNumber + "/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["cardNumber"] = cardNumber;
    json["pin"] = pin;

    networkManager->post(request, QJsonDocument(json).toJson());
    connect(this, &MainWindow::loginSuccessful, this, &MainWindow::updateUIForDebitCredit);

    ui -> btnFi -> setVisible(false);
    ui -> btnEn -> setVisible(false);
    ui -> btnSv -> setVisible(false);
}

QString MainWindow::getCardNumber() const
{
    return cardNumber;
}

void MainWindow::updateButtonVisibility()
{
    if (cardType == "debit") {
        ui->btnCreditAcc->setVisible(false);
        ui->btnDepositDebit->setVisible(true);
        ui->btnWithdrawDebit->setVisible(true);
        ui->btnTransactionsDebit->setVisible(true);
    } else if (cardType == "credit") {
        ui->btnDebitAcc->setVisible(false);
        ui->btnDepositDebit->setVisible(false);
        ui->btnWithdrawDebit->setVisible(true);
        ui->btnTransactionsDebit->setVisible(true);
    } else if (cardType == "combination") {
        ui->btnCreditAcc->setVisible(true);
        ui->btnDebitAcc->setVisible(true);
        ui->btnDepositDebit->setVisible(true);
        ui->btnWithdrawDebit->setVisible(true);
        ui->btnTransactionsDebit->setVisible(true);
    }
}


void MainWindow::handleLastPage()
{
    ui -> stackedWidget -> setCurrentIndex(6);

    QTimer::singleShot(4000, this, [this]()
    {
        // Reset session data
        bearerToken.clear();
        atmSerialNumber.clear();
        atmLocation.clear();
        atmId = 0;
        cardNumber.clear();
        cardType.clear();
        cardStatus = 0;
        cardID = 0;
        accountNumber.clear();
        accountID = 0;
        accountBalance.clear();
        customerFirstName.clear();
        customerLastName.clear();
        ui->cardNumberInput->clear();
        ui -> textDebitWithdrawMsg ->clear();
        ui -> lineEditTransferAmount -> clear();
        ui -> lineEditTransferTarget -> clear();

        // Reset UI elements
        ui->stackedWidget->setCurrentIndex(0);
        returnBtnVisibility();

        // Optionally, reset button visibility
        ui->btnCreditAcc->setVisible(true);
        ui->btnDebitAcc->setVisible(true);
        ui->btnDepositDebit->setVisible(true);
        ui->btnWithdrawDebit->setVisible(true);
        ui->btnTransactionsDebit->setVisible(true);
        ui -> btnFi -> setVisible(true);
        ui -> btnEn -> setVisible(true);
        ui -> btnSv -> setVisible(true);

        ui -> btnWithdraw10Debit -> setVisible(true);
        ui -> btnWithdraw20Debit -> setVisible(true);
        ui -> btnWithdraw50Debit -> setVisible(true);
        ui -> btnWithdraw100Debit -> setVisible(true);
        ui -> btnWithdraw150Debit -> setVisible(true);
        ui -> btnWithdraw200Debit -> setVisible(true);
        ui -> btnConfirmWithdrawDebit -> setVisible(true);
        ui -> btnAddCustomWithdrawDebit -> setVisible(true);
        ui -> btnClearDebitWithdrawValue -> setVisible(true);

    });
}


void MainWindow::on_btnTransferPage_clicked()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        //qDebug() << "Added page to history:" << ui -> stackedWidget -> currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(7);
    returnBtnVisibility();

    ui -> lineEditTransferAmount -> setVisible(true);
    ui -> lineEditTransferTarget -> setVisible(true);
    ui -> textTransferAmount -> setVisible(true);
    ui -> textTransferTarget -> setVisible(true);
    ui -> btnTransferConfirm -> setVisible(true);

    ui -> textTransferState -> setVisible(false);
    ui -> textTransferProcess -> setVisible(false);
    ui -> lineEditTransferAmount -> setValidator(new QDoubleValidator(0, 3000, 2, this));
}


void MainWindow::on_btnTransferConfirm_clicked()
{
    int transferAmount = ui -> lineEditTransferAmount -> text().toInt();
    int transferTarget = ui -> lineEditTransferTarget -> text().toInt();

    if (accountBalance.toDouble() >= transferAmount && transferAmount != 0)
    {
        ui -> textTransferProcess -> setText(tr("Processing..."));
        ui -> btnReturn -> setVisible(false);

        ui -> lineEditTransferAmount -> setVisible(false);
        ui -> lineEditTransferTarget -> setVisible(false);
        ui -> textTransferAmount -> setVisible(false);
        ui -> textTransferTarget -> setVisible(false);
        ui -> btnTransferConfirm -> setVisible(false);

        ui -> textTransferProcess -> setVisible(true);

        QJsonObject json;
        json["from_account"] = QString::number(accountID);
        json["to_account"] = transferTarget;
        json["amount"] = transferAmount;
        json["idatm"] = atmId;
        json["idcard"] = cardID;

        QUrl url(env::getUrl() + "/transactions/transfer");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QByteArray myToken = "Bearer " + bearerToken.toUtf8();
        request.setRawHeader(QByteArray("Authorization"), myToken);
        request.setRawHeader("serialnumber", atmSerialNumber.toUtf8());

        QNetworkReply *reply = networkManager->post(request, QJsonDocument(json).toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply, transferAmount]() {
            if (reply->error() == QNetworkReply::NoError) {
                ui->textTransferProcess->setVisible(false);
                ui->textTransferState->setVisible(true);
                ui->textTransferState->setText(tr("%1 Transferred").arg(QString::number(transferAmount)));
                ui->textTransferState->setStyleSheet("color: green;");

                QTimer::singleShot(4000, this, [this]() {
                    handleLastPage();
                });
            } else {
                ui->textTransferProcess->setVisible(false);
                ui->textTransferState->setVisible(true);
                ui->textTransferState->setText(tr("Transfer failed"));
                ui->textTransferState->setStyleSheet("color: red;");

                QTimer::singleShot(3000, this, [this]() {
                    ui->textTransferState->clear();
                });
            }
            reply->deleteLater();
        });
    }
    else if (transferAmount == 0)
    {
        ui->textTransferProcess->setVisible(false);
        ui->textTransferState->setVisible(true);
        ui->lineEditTransferAmount->setVisible(true);
        ui->lineEditTransferTarget->setVisible(true);
        ui->textTransferAmount->setVisible(true);
        ui->textTransferTarget->setVisible(true);
        ui->btnTransferConfirm->setVisible(true);
        ui->textTransferState->setText(tr("Invalid amount"));
        ui->textTransferState->setStyleSheet("color: red;");

        QTimer::singleShot(3000, this, [this]() {
            ui->textTransferState->clear();
        });
    }
    else
    {
        ui->textTransferProcess->setVisible(false);
        ui->textTransferState->setVisible(true);
        ui->lineEditTransferAmount->setVisible(true);
        ui->lineEditTransferTarget->setVisible(true);
        ui->textTransferAmount->setVisible(true);
        ui->textTransferTarget->setVisible(true);
        ui->btnTransferConfirm->setVisible(true);
        ui->textTransferState->setText(tr("Invalid funds"));
        ui->textTransferState->setStyleSheet("color: red;");

        QTimer::singleShot(3000, this, [this]() {
            ui->textTransferState->clear();
        });
    }
}


void MainWindow::on_nextButton_clicked()
{
    if (currentPage < maxPage) {
        currentPage++;
        maxPage = eventData->addEvents(currentPage);
    }

    checkPage();
    //qDebug() << "Next clicked! Current page: " << currentPage << ", max page: " << maxPage;
}


void MainWindow::on_previousButton_clicked()
{
    if (currentPage > 1) {
        currentPage--;
        maxPage = eventData->addEvents(currentPage); // Päivitä taulukko
        checkPage(); // Päivitä näppäinten tilanne
    }

    checkPage();
}

