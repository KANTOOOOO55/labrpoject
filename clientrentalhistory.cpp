#include "clientrentalhistory.h"
#include "QtCore/qdatetime.h"
#include "QtWidgets/qcombobox.h"
#include "accountsadminwindow.h"
#include "clientdashboard.h"
#include "item.h"
#include "rentalrequest.h"
#include "ui_clientrentalhistory.h"

#include <QMessageBox>

bool IsAdmin;
QString CurrentClientName;

ClientRentalHistory::ClientRentalHistory(QWidget *parent, QString clientName, bool isAdmin)
    : QDialog(parent)
    , ui(new Ui::ClientRentalHistory)
{
    ui->setupUi(this);
    IsAdmin = isAdmin;
    CurrentClientName = clientName;
    std::vector<RentalRequest> rentalRequests = RentalRequest::getRentalRequests();
    std::vector<RentalRequest> filteredItems;

    for (const auto& request : rentalRequests) {
        if (request.getClientId() == clientName) {
            filteredItems.push_back(request);
        }
    }

    ui->tableWidget->setRowCount(filteredItems.size());

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int row = 0;
    for (const auto& rentalRequest : filteredItems) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(rentalRequest.getItemName()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(rentalRequest.getCreateDate()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(rentalRequest.getFromDate()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(rentalRequest.getToDate()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(rentalRequest.getFinalPrice()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(rentalRequest.getStatus()));
        row++;
    }
}

ClientRentalHistory::~ClientRentalHistory()
{
    delete ui;
}

void ClientRentalHistory::on_pushButtonReturn_clicked()
{
    hide();
    if(IsAdmin) {
        AccountsAdminWindow *accountAdmin = new AccountsAdminWindow();
        accountAdmin->show();
    } else {
        ClientDashboard *clientDashboard = new ClientDashboard(this, CurrentClientName);
        clientDashboard->show();

    }
}


void ClientRentalHistory::on_pushButtonSave_clicked()
{


    RentalRequest selectedRentalRequest;
    int currentRow = ui->tableWidget->currentRow();
    QString status = ui->tableWidget->item(currentRow, 5)->text();
    if(status != "Rented") {
        QMessageBox::information(this, "Error", "You didn't recieve the car yet to return it");
        return;
    }


    QTableWidgetItem* itemNameItem = ui->tableWidget->item(currentRow, 0);
    QTableWidgetItem* createDateItem = ui->tableWidget->item(currentRow, 1);
    QTableWidgetItem* returnDateItem = ui->tableWidget->item(currentRow, 3);

    QString itemName = itemNameItem->text();
    QString userName = CurrentClientName;
    QString createDate = createDateItem->text();
    QString returnDate = returnDateItem->text();

    QDate returnDateParsed = QDate::fromString(returnDate, "dd/MM/yyyy");
    QDate currentDate = QDate::currentDate();

    // Check if current date is after the return date
    int lateDays = 0;
    if (currentDate > returnDateParsed) {
        lateDays = returnDateParsed.daysTo(currentDate);
    }

    // Calculate the total price
    QString basePrice = ui->tableWidget->item(currentRow, 4)->text();
    int lateFee = lateDays; // 1 unit per late day
    int totalDeduction = basePrice.toInt() + lateFee;

    QString message = "Item has been returned. ";
    if (lateDays > 0) {
        message += QString::number(lateDays) + " late days were charged. ";
    }
    message += QString::number(totalDeduction) + " units have been deducted from your account.";

    QMessageBox::information(this, "Success", message);

    std::vector<RentalRequest> allRequests = RentalRequest::getRentalRequests();

    bool found = false;
    for (auto& request : allRequests) {
        if (request.getItemName() == itemName &&
            request.getClientId() == userName &&
            request.getCreateDate() == createDate &&
            request.getToDate() == returnDate) {
            request.setStatus("Returned");
            found = true;
            break;
        }
    }
    RentalRequest::saveRentalRequests(allRequests);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Rating", "Did you like your rented car?", QMessageBox::Yes | QMessageBox::No );
    if (reply == QMessageBox::Yes) {
        std::map<QString, Item> allItems = Item::getAllItems();
        Item editedItem = allItems[itemName];
        editedItem.setRate(QString::number((editedItem.getRate().toInt() + 1)));
        allItems[itemName] = editedItem;
        Item::saveItems(allItems);
    } else {
        qDebug() << "User clicked No";
    }
    on_pushButtonReturn_clicked();
}

