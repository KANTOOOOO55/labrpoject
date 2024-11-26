#include "itemadminwindow.h"
#include "category.h"
#include "item.h"
#include "ui_itemadminwindow.h"
#include <AdminDashBoard.h>
#include <QComboBox>
#include <QMessageBox>

ItemAdminWindow::ItemAdminWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemAdminWindow)
{
    ui->setupUi(this);
    std::map<QString, Item> items = Item::getAllItems();
    ui->tableWidget->setRowCount(items.size());

    QStringList availabilityOptions = {"Available", "Reserved"};
    std::vector<Category> categoryOptions = Category::getCategories();

    int row = 0;
    for (const auto& [id, item] : items) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(item.getName()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(item.getDescription()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(item.getPrice()));
        // Availability
        QComboBox* availabilityComboBox = new QComboBox();
        availabilityComboBox->addItems(availabilityOptions);
        int index = availabilityOptions.indexOf(item.getAvailability());
        if (index != -1) {
            availabilityComboBox->setCurrentIndex(index);
        }
        ui->tableWidget->setCellWidget(row, 3, availabilityComboBox);
        // Category
        QComboBox* categoryComboBox = new QComboBox();
        for (const auto& category : categoryOptions) {
            categoryComboBox->addItem(category.getName());
        }
        auto it = std::find_if(categoryOptions.begin(), categoryOptions.end(), [&](const Category& category) {
            return category.getName() == item.getCategory();
        });
        if (it != categoryOptions.end()) {
            int index = std::distance(categoryOptions.begin(), it);
            categoryComboBox->setCurrentIndex(index);
        }
        ui->tableWidget->setCellWidget(row, 4, categoryComboBox);
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(item.getNumberOfTimesRented()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(item.getRate()));
        row++;
    }
}

ItemAdminWindow::~ItemAdminWindow()
{
    delete ui;
}

void ItemAdminWindow::on_pushButtonAddNewItem_clicked()
{
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow);
    QStringList availabilityOptions = {"Available", "Reserved"};
    std::vector<Category> categoryOptions = Category::getCategories();
    QStringList categoryNames;
    for (const auto& category : categoryOptions) {
        categoryNames.append(category.getName());
    }

    for (int column = 0; column < 7; ++column) {
        if (column == 3) {
            QComboBox* availabilityComboBox = new QComboBox();
            availabilityComboBox->addItems(availabilityOptions);
            ui->tableWidget->setCellWidget(newRow, column, availabilityComboBox);
        } else if (column == 4) {
            QComboBox* categoryComboBox = new QComboBox();
            categoryComboBox->addItems(categoryNames);
            ui->tableWidget->setCellWidget(newRow, column, categoryComboBox);
        } else
        ui->tableWidget->setItem(newRow, column, new QTableWidgetItem(""));
    }
}


void ItemAdminWindow::on_pushButtonDelete_clicked()
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


void ItemAdminWindow::on_pushButtonSave_clicked()
{
    std::map<QString, Item> updatedItems;
    for (int row = 0; row < ui->tableWidget->rowCount();row++) {
        Item item;
        QString name = ui->tableWidget->item(row, 0)->text();
        QString description = ui->tableWidget->item(row, 1)->text();
        QString price = ui->tableWidget->item(row, 2)->text();
        QComboBox* comboBoxAvailability = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 3));
        QString availability = comboBoxAvailability->currentText();
        QComboBox* comboBoxCategory = qobject_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 4));
        QString category = comboBoxCategory->currentText();
        QString numberOfTimesRented = ui->tableWidget->item(row, 5)->text();
        QString rate = ui->tableWidget->item(row, 6)->text();
        item.setName(name);
        item.setDescription(description);
        item.setPrice(price);
        item.setAvailability(availability);
        item.setCategory(category);
        item.setNumberOfTimesRented(numberOfTimesRented);
        item.setRate(rate);
        updatedItems[name] = item;
    }
    Item::saveItems(updatedItems);
}


void ItemAdminWindow::on_pushButtonReturn_clicked()
{
    hide();
    AdminDashBoard *dash = new AdminDashBoard();
    dash->show();
}

