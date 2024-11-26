    #include "clientdashboard.h"
#include "QtCore/qdatetime.h"
#include "category.h"
#include "clientrentalhistory.h"
#include "item.h"
#include "rentalrequest.h"
#include "ui_clientdashboard.h"
#include <QMessageBox>

QString ClientName;

ClientDashboard::ClientDashboard(QWidget *parent, QString clientName)
    : QDialog(parent)
    , ui(new Ui::ClientDashboard)
{
    ui->setupUi(this);
    ClientName = clientName;
    std::map<QString, Item> items = Item::getAllItems();
    ui->tableWidget->setRowCount(items.size());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    std::vector<Category> categoryOptions = Category::getCategories();
    for( const auto& categoryOption : categoryOptions)
        ui->comboBoxCategory->addItem(categoryOption.getName());
    ui->comboBoxCategory->addItem("All");

    int row = 0;
    for (const auto& [id, item] : items) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(item.getName()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(item.getDescription()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(item.getPrice()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(item.getCategory()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(item.getNumberOfTimesRented()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(item.getRate()));
        row++;
    }
}

ClientDashboard::~ClientDashboard()
{
    delete ui;
}

void ClientDashboard::on_pushButtonSearch_clicked()
{
    QString keyword = ui->lineEditKeyword->text();
    QString minPrice = ui->lineEditMinPrice->text();
    QString maxPrice = ui->lineEditMaxPrice->text();
    QString category = ui->comboBoxCategory->currentText();
    QString fromDate = ui->lineEditRentFrom->text();
    QString toDate = ui->lineEditRentTo->text();
    bool isShowOnlyAvailable = ui->checkBoxShowOnlyAvailable->isChecked();

    std::vector<Item> *searchedItems = new std::vector<Item>();
    for (const auto& [id, item] : Item::getAllItems()) {
        if ((keyword.isEmpty() || item.getName().contains(keyword, Qt::CaseInsensitive)) &&
            (minPrice.isEmpty() || item.getPrice().toInt() >= minPrice.toInt()) &&
            (maxPrice.isEmpty() || item.getPrice().toInt() <= maxPrice.toInt()) &&
            (category == "All" || item.getCategory() == category) &&
            (!isShowOnlyAvailable || (isShowOnlyAvailable && checkIfDateIsAvailable(item.getName(), fromDate, toDate).isEmpty()))
            ) {
            searchedItems->push_back(item);
        }
    }
    ui->tableWidget->clearContents();
    int row = 0;
    for (const auto& item : *searchedItems) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(item.getName()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(item.getDescription()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(item.getPrice()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(item.getCategory()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(item.getNumberOfTimesRented()));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(item.getRate()));
        row++;
    }
}


void ClientDashboard::on_pushButtonSave_clicked()
{
    Item selectedItem;
    int currentRow = ui->tableWidget->currentRow();
    QTableWidgetItem* item = ui->tableWidget->item(currentRow, 0);
    if (item) {
        std::map<QString, Item> x = Item::getAllItems();
        selectedItem = x[item->text()];
    }

    QString availabilityMessage = checkIfDateIsAvailable(selectedItem.getName(), ui->lineEditRentFrom->text(), ui->lineEditRentTo->text());
    if(ui->lineEditRentFrom->text().isEmpty() || ui->lineEditRentTo->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select the rent dates");
    } else if(!availabilityMessage.isEmpty()) {
        QMessageBox::warning(this, "Error", availabilityMessage);
    }
        else {
        int totalPrice = 0;
        int increasedRate = 0.2 * selectedItem.getRate().toInt();
        int increasedDemand = 0.2 * selectedItem.getNumberOfTimesRented().toInt();
        int rentalDays = calculateDaysBetween(ui->lineEditRentFrom->text(), ui->lineEditRentTo->text()) * 0.2;

        totalPrice = selectedItem.getPrice().toInt() + increasedRate + increasedDemand - rentalDays;
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Reservation Confirmation", "Are you sure you want to reserve " +
                                                                            selectedItem.getName() +
                                                                            " from " +
                                                                            ui->lineEditRentFrom->text() +
                                                                            " to " +
                                                                            ui->lineEditRentTo->text() +
                                                                            " with a total price of " +
                                                                            QString::number(totalPrice) +
                                                                            " the price was adjusted based on the car's rating, demand and your reservation period. "
                                      , QMessageBox::Yes | QMessageBox::No );

        if (reply == QMessageBox::Yes) {
            QDate currentDate = QDate::currentDate();
            QString currentDateString = currentDate.toString("d/M/yyyy");
            RentalRequest *rentalRequest = new RentalRequest();
            rentalRequest->setClientId(ClientName);
            rentalRequest->setCreateDate(currentDateString);
            rentalRequest->setFromDate(ui->lineEditRentFrom->text());
            rentalRequest->setToDate(ui->lineEditRentTo->text());
            rentalRequest->setItemName(selectedItem.getName());
            rentalRequest->setStatus("Open");
            rentalRequest->setFinalPrice(QString::number(totalPrice));
            RentalRequest::saveRentalRequest(*rentalRequest);
        } else {
            qDebug() << "User clicked No";
        }
    }
}

int ClientDashboard::calculateDaysBetween(const QString &date1, const QString &date2)
{
    const QString dateFormat = "d/M/yyyy";
    QDate firstDate = QDate::fromString(date1, dateFormat);
    QDate secondDate = QDate::fromString(date2, dateFormat);
    if (!firstDate.isValid() || !secondDate.isValid()) {
        qDebug() << "Invalid date format!";
        return -1;
    }
    int daysDifference = firstDate.daysTo(secondDate);
    return daysDifference;
}


void ClientDashboard::on_pushButtonSave_2_clicked()
{
    hide();
    ClientRentalHistory *client = new ClientRentalHistory(this, ClientName);
    client->show();
}

QString ClientDashboard::checkIfDateIsAvailable(QString itemName, QString fromDate, QString toDate)
{
    std::vector<RentalRequest> allRequests = RentalRequest::getRentalRequests();

    QDate requestedFromDate = QDate::fromString(fromDate, "d/M/yyyy");
    QDate requestedToDate = QDate::fromString(toDate, "d/M/yyyy");

    if (!requestedFromDate.isValid() || !requestedToDate.isValid()) {
        return "Invalid date format. Please enter dates in the format: d/M/yyyy.";
    }

    if (requestedFromDate > requestedToDate) {
        return "The start date cannot be after the end date.";
    }

    QDate earliestAvailableDate = requestedFromDate;
    for (const auto& request : allRequests) {
        if (request.getItemName() == itemName) {
            QDate bookedFromDate = QDate::fromString(request.getFromDate(), "d/M/yyyy");
            QDate bookedToDate = QDate::fromString(request.getToDate(), "d/M/yyyy");

            if (bookedFromDate.isValid() && bookedToDate.isValid()) {
                // Check if the requested range overlaps with this booking
                if (!(requestedToDate < bookedFromDate || requestedFromDate > bookedToDate)) {
                    // Update the earliest available date to be after the current booking
                    earliestAvailableDate = bookedToDate.addDays(1);
                }
            }
        }
    }

    // Check if the earliest available date is later than the requested range
    if (earliestAvailableDate > requestedFromDate) {
        QDate suggestedToDate = earliestAvailableDate.addDays(requestedToDate.daysTo(requestedFromDate));
        return QString("The item '%1' is unavailable for the requested dates (%2 to %3). "
                       "You can book it from %4 to %5 instead.")
            .arg(itemName)
            .arg(fromDate)
            .arg(toDate)
            .arg(earliestAvailableDate.toString("d/M/yyyy"))
            .arg(suggestedToDate.toString("d/M/yyyy"));
    }

    return "";
}

