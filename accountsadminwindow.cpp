#include "accountsadminwindow.h"
#include "admindashboard.h"
#include "client.h"
#include "clientrentalhistory.h"
#include "ui_accountsadminwindow.h"

#include <QMessageBox>

AccountsAdminWindow::AccountsAdminWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountsAdminWindow)
{
    ui->setupUi(this);
    std::map<QString, Client> clients = Client::getAllClients();
    ui->tableWidget->setRowCount(clients.size());
    int row = 0;
    for (const auto& [id, client] : clients) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(client.getName()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(client.getEmail()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(client.getPassword()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(client.getPhone()));
        row++;
    }
}

AccountsAdminWindow::~AccountsAdminWindow()
{
    delete ui;
}

void AccountsAdminWindow::on_pushButton_2_clicked()  //betbayen dashboard el admin
{
    hide();
    AdminDashBoard *dash = new AdminDashBoard();
    dash->show();
}


void AccountsAdminWindow::on_pushButton_3_clicked() // function of the saving client
{
    std::map<QString, Client> updatedClients;
    for (int row = 0; row < ui->tableWidget->rowCount();row++) {
        Client client;
        QString name = ui->tableWidget->item(row, 0)->text();
        QString email = ui->tableWidget->item(row, 1)->text();
        QString password = ui->tableWidget->item(row, 2)->text();
        QString phone = ui->tableWidget->item(row, 3)->text();
        client.setName(name);
        client.setEmail(email);
        client.setPassword(password);
        client.setPhone(phone);
        updatedClients[name] = client;
    }
    Client::saveAllClients(updatedClients);
}


void AccountsAdminWindow::on_pushButton_clicked()   // function to add new row
{
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow);
    for (int column = 0; column < 5; ++column) {
        ui->tableWidget->setItem(newRow, column, new QTableWidgetItem(""));
    }
}


void AccountsAdminWindow::on_pushButton_4_clicked()   // function to remove current row
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow != -1) {
        if (currentRow >= 0 && currentRow < ui->tableWidget->rowCount()) {
            ui->tableWidget->removeRow(currentRow);
        }
    }
    else {
        QMessageBox::warning(this, "Account Manager", "There is no selected row!");

    }
}


void AccountsAdminWindow::on_pushButton_5_clicked() // function to show the client rental history
{
    QString name;
    int currentRow = ui->tableWidget->currentRow();
    QTableWidgetItem* item = ui->tableWidget->item(currentRow, 0);
    if (item) {
        name = item->text();
    }
    hide();
    ClientRentalHistory *clientRentalHistory = new ClientRentalHistory(this, name, true);
    clientRentalHistory->show();
}

