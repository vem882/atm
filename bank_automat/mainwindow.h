#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

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

private slots:
    void on_btnStart_clicked();

    void on_btnExit_clicked();

    void on_btnCreditAcc_clicked();

    void on_btnDebitAcc_clicked();

    void on_btnReturn_clicked();

private:
    Ui::MainWindow *ui;
    QStack<int> pageHistory;
    void returnBtnVisibility();
};
#endif // MAINWINDOW_H
