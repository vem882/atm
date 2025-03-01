#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <QString>
#include <QDateTime>
#include <QList>
#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QStandardItem>
#include <QDialog>
#include <QLabel>
#include <QSize>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QTableView>
#include <QColor>
#include <QColorDialog>
#include <QPalette>


QT_BEGIN_NAMESPACE
namespace Ui {
class transactions;
}
QT_END_NAMESPACE

class transactions : public QDialog
{
    Q_OBJECT

public:
    explicit transactions(QWidget *parent = nullptr);
    ~transactions();

    void attachWindow(QWidget *window);
    int addEvents(int pageNum);
    void getEventSlot(QByteArray data);
    void setTableView(QTableView *view);
    void setCurrencySymbol(const QString &symbol); // Add this method

private:

    QNetworkAccessManager *getManager;
    QByteArray response_data;
    QList<transactions> eventList;
    QTableView *tableView;
    QString currency_symbol; // Add this member variable

};
#endif // TRANSACTIONS_H
