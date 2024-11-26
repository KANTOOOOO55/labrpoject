#include "categoryadminwindow.h"
#include "admindashboard.h"
#include "category.h"
#include "ui_categoryadminwindow.h"

#include <QMessageBox>

CategoryAdminWindow::CategoryAdminWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CategoryAdminWindow)
{
    ui->setupUi(this);
    std::vector<Category> categories = Category::getCategories();
    ui->tableWidget->setRowCount(categories.size());
    int row = 0;
    for (const auto& category : categories) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(category.getName()));
        row++;
    }
}

CategoryAdminWindow::~CategoryAdminWindow()
{
    delete ui;
}

void CategoryAdminWindow::on_pushButtonAddNewCategory_clicked()
{
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow);
    for (int column = 0; column < 1; ++column) {
        ui->tableWidget->setItem(newRow, column, new QTableWidgetItem(""));
    }
}


void CategoryAdminWindow::on_pushButtonDelete_clicked()
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


void CategoryAdminWindow::on_pushButtonSave_clicked()
{
    std::vector<Category> updatedCategories;
    for (int row = 0; row < ui->tableWidget->rowCount();row++) {
        Category category(ui->tableWidget->item(row, 0)->text());
        updatedCategories.push_back(category);
    }
    Category::saveCategories(updatedCategories);
}


void CategoryAdminWindow::on_pushButtonReturn_clicked()
{
    hide();
    AdminDashBoard *dash = new AdminDashBoard();
    dash->show();
}

