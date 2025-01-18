#include "mainwindow.h"
#include "pinscreen.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList <QPushButton *> exitButtons = this -> findChildren<QPushButton *>("btnExit");
    for (QPushButton *button : exitButtons)
    {
        connect(button, &QPushButton::clicked, this, &MainWindow::on_btnExit_clicked);
    }

    ui -> stackedWidget -> setCurrentIndex(0);

    ui -> btnReturn -> setVisible(false);
    connect(ui -> btnReturn, &QPushButton::clicked, this, &MainWindow::on_btnReturn_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    PinScreen *objPinScreen = new PinScreen(this);
    objPinScreen -> open();
}


void MainWindow::on_btnExit_clicked()
{
    QCoreApplication::quit();
}


void MainWindow::updateUIForDebitCredit()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        qDebug() << "Added page to history:" << ui->stackedWidget->currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(1);
    returnBtnVisibility();
}


void MainWindow::on_btnDebitAcc_clicked()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        qDebug() << "Added page to history:" << ui->stackedWidget->currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(2);
    returnBtnVisibility();
}


void MainWindow::on_btnCreditAcc_clicked()
{
    if (pageHistory.isEmpty() || pageHistory.top() != ui -> stackedWidget -> currentIndex())
    {
        pageHistory.push(ui -> stackedWidget -> currentIndex());
        qDebug() << "Added page to history:" << ui->stackedWidget->currentIndex();
    }
    ui -> stackedWidget -> setCurrentIndex(3);
    returnBtnVisibility();
}


void MainWindow::on_btnReturn_clicked()
{
    if (!pageHistory.isEmpty())
    {
        int lastPage = pageHistory.pop();
        qDebug() << "navigating back to page:" << lastPage;
        qDebug() << "remaining page history:" << pageHistory;

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
    if (ui -> stackedWidget -> currentIndex() > 1)
    {
        ui -> btnReturn -> setVisible(true);
    }
    else
    {
        ui -> btnReturn -> setVisible(false);
    }
}

