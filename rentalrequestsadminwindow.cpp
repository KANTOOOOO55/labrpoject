#include "rentalrequestsadminwindow.h"
#include "AdminDashBoard.h"
#include "QtWidgets/qcombobox.h"
#include "rentalrequest.h"
#include "ui_rentalrequestsadminwindow.h"

RentalRequestsAdminWindow::RentalRequestsAdminWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RentalRequestsAdminWindow)
{
    ui->setupUi(this);

    std::vector<RentalRequest> rentalRequests = RentalRequest::getRentalRequests();
    ui->tableWidget->setRowCount(rentalRequests.size());

    QStringList statusOptions = {"Open", "Rented", "Returned", "Rejected"};

    int row = 0;
    for (const auto& rentalRequest : rentalRequests) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(rentalRequest.getClientId()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(rentalRequest.getItemName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(rentalRequest.getCreateDate()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(rentalRequest.getFromDate()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(rentalRequest.getToDate()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(rentalRequest.getFinalPrice()));
        // Status
        QComboBox* statusComboBox = new QComboBox();
        statusComboBox->addItems(statusOptions);
        int index = statusOptions.indexOf(rentalRequest.getStatus());
        if (index != -1) {
            statusComboBox->setCurrentIndex(index);
        }
        ui->tableWidget->setCellWidget(row, 6, statusComboBox);
        row++;
    }
}

RentalRequestsAdminWindow::~RentalRequestsAdminWindow()
{
    delete ui;
}

void RentalRequestsAdminWindow::on_pushButtonReturn_clicked()
{
    hide();
    AdminDashBoard *dash = new AdminDashBoard();
    dash->show();
}


void RentalRequestsAdminWindow::on_pushButtonSave_clicked()
{
    std::vector<RentalRequest> updatedRentalRequests;
    for (int row = 0; row < ui->tableWidget->rowCount();row++) {
        RentalRequest rentalRequest;
        rentalRequest.setClientId(ui->tableWidget->item(row, 0)->text());
        rentalRequest.setItemName(ui->tableWidget->item(row, 1)->text());
        rentalRequest.setCreateDate(ui->tableWidget->item(row, 2)->text());
        rentalRequest.setFromDate(ui->tableWidget->item(row, 3)->text());
        rentalRequest.setToDate(ui->tableWidget->item(row, 4)->text());
        rentalRequest.setFinalPrice(ui->tableWidget->item(row, 5)->text());
        QComboBox* comboBoxCategory = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 6));
        QString status = comboBoxCategory->currentText();
        rentalRequest.setStatus(status);
        updatedRentalRequests.push_back(rentalRequest);
    }
    RentalRequest::saveRentalRequests(updatedRentalRequests);
}

