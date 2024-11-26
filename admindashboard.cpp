#include "admindashboard.h"
#include "accountsadminwindow.h"
#include "categoryadminwindow.h"
#include "itemadminwindow.h"
#include "rentalrequestsadminwindow.h"
#include "ui_admindashboard.h"

AdminDashBoard::AdminDashBoard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminDashBoard)
{
    ui->setupUi(this);
}

AdminDashBoard::~AdminDashBoard()
{
    delete ui;
}

void AdminDashBoard::on_pushButton_clicked()
{
    hide();
    AccountsAdminWindow *accountsWindow = new AccountsAdminWindow();
    accountsWindow->show();
}


void AdminDashBoard::on_pushButton_2_clicked()
{
    hide();
    CategoryAdminWindow *categoryWindow = new CategoryAdminWindow();
    categoryWindow->show();
}


void AdminDashBoard::on_pushButton_3_clicked()
{
    hide();
    ItemAdminWindow *itemWindow = new ItemAdminWindow();
    itemWindow->show();
}


void AdminDashBoard::on_pushButton_4_clicked()
{
    hide();
    RentalRequestsAdminWindow *rentalRequestWindow = new RentalRequestsAdminWindow();
    rentalRequestWindow->show();
}

