#include "loginwindow.h"
#include "admindashboard.h"
#include "client.h"
#include "clientdashboard.h"
#include "registerwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    if(username == "admin" && password == "admin") {
        QMessageBox::information(this, "Login", "Welcome admin!");
        hide();
        AdminDashBoard *admin = new AdminDashBoard();
        admin->show();
    }else if(Client::login(username, password) != "-1") {
        QMessageBox::warning(this, "Login", "Login Successfull!");
        QString id = Client::login(username, password);
        this->hide();
        ClientDashboard *clientDashBoard = new ClientDashboard(nullptr, id);
        clientDashBoard->show();
    }
        else {
        QMessageBox::warning(this, "Login", "Username or password is wrong!");
    }
}


void LoginWindow::on_pushButton_2_clicked()
{
    this->hide();
    RegisterWindow *registerWindow = new RegisterWindow();
    registerWindow->show();
}

