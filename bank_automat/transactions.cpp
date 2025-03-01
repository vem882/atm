#include "transactions.h"
#include "env.h"
#include "qheaderview.h"
#include <QDateTime>
#include <mainwindow.h>


transactions::transactions(QWidget *parent): QDialog(parent) {}

transactions::~transactions() {}

void transactions::setTableView(QTableView *view)
{
    tableView = view;
}

void transactions::attachWindow(QWidget *window)
{
    // Ensure the table view is set
    if (!tableView) {
        qDebug() << "Error: Taulukkonäkymää ei löytynyt";
        return;
    }
}

void transactions::setCurrencySymbol(const QString &symbol)
{
    currency_symbol = symbol;
}

int transactions::addEvents(int pageNum)
{
    if (!tableView) {
        qDebug() << "Taulukkonäkymää ei ole alustettu!";
        return 0;
    }
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    // Tarkistetaan JSONin oikeellisuus
    if(json_doc.isNull()) {
        qDebug() << "Virheellinen JSON-data";
        qDebug() << "Raw JSON response: " << QString(response_data);
        return 0;
    }

    // Haetaan data-taulukko juuriobjektista
    QJsonObject root_obj = json_doc.object();
    QJsonArray json_array = root_obj["data"].toArray();

    int eventsOnPage = 10;
    int totalEvents = json_array.size();
    int maxNum = (totalEvents + eventsOnPage - 1) / eventsOnPage; // Kokonaissivumäärä

    QStandardItemModel *table_model = new QStandardItemModel(eventsOnPage, 3);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Amount"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));

    for (int row = 0; row < eventsOnPage; ++row) {
        int dataIndex = (pageNum - 1) * eventsOnPage + row; // Lasketaan oikea indeksi JSON-datasta
        if (dataIndex >= totalEvents) {
            break; // Lopeta, jos tapahtumat loppuvat kesken
        }

        QJsonObject event = json_array[dataIndex].toObject();

        // Määrä-kenttä
        QString amount = QString("%1 %2").arg(event["trans_amount"].toString()).arg(currency_symbol);
        QStandardItem *amountItem = new QStandardItem(amount);

        // Tapahtuman tyyppi
        QStandardItem *typeItem = new QStandardItem(event["trans_method"].toString());

        // Päivämäärän muotoilu
        QString rawDate = event["trans_date"].toString();
        QDateTime dateTime = QDateTime::fromString(rawDate, Qt::ISODate);
        QString formattedDate = dateTime.toString("dd.MM.yyyy HH:mm");
        QStandardItem *dateItem = new QStandardItem(formattedDate);

        // Aseta rivin tiedot
        table_model->setItem(row, 0, amountItem);
        table_model->setItem(row, 1, typeItem);
        table_model->setItem(row, 2, dateItem);
    }

    // Tyylittely
    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    tableView->setModel(table_model);
    tableView->resizeColumnsToContents();
    tableView->setColumnWidth(0, 200);
    tableView->setColumnWidth(1, 200);
    tableView->setColumnWidth(2, 200);

    return maxNum;
}

void transactions::getEventSlot(QByteArray data) {
    response_data = QByteArray(data.constData(), data.length()); // Syväkopio
}
