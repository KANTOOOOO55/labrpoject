#include "registerwindow.h"
#include "client.h"
#include "loginwindow.h"
#include "ui_registerwindow.h"

#include <QMessageBox>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pushButton_2_clicked()
{
    this->hide();
    LoginWindow *loginWindow = new LoginWindow();
    loginWindow->show();
}


void RegisterWindow::on_pushButton_clicked()
{
    Client *client = new Client();
    client->setName(ui->lineEditName->text());
    client->setEmail(ui->lineEditEmail->text());
    client->setPassword(ui->lineEditPassword->text());
    client->setPhone(ui->lineEditPhone->text());
    Client::saveClient(*client);
    QMessageBox::warning(this, "Register", "Register successfull, please login!");
    on_pushButton_2_clicked();
}

