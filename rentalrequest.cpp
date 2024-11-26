#include "rentalrequest.h"
#include "QtCore/qfile.h"

#include <QDir>

RentalRequest::RentalRequest() {}

void RentalRequest::saveRentalRequest(RentalRequest rentalRequest)
{
    QString filePath = QDir::homePath() + "/Documents/rental_requests.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << rentalRequest.getClientId() << "$"
        << rentalRequest.getItemName() << "$"
        << rentalRequest.getStatus() << "$"
        << rentalRequest.getCreateDate() << "$"
        << rentalRequest.getFromDate() << "$"
        << rentalRequest.getToDate() << "$"
        << rentalRequest.getFinalPrice() << "\n";

    file.close();
}

void RentalRequest::saveRentalRequests(std::vector<RentalRequest> rentalRequests)
{
    QString filePath = QDir::homePath() + "/Documents/rental_requests.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for (const auto& request : rentalRequests) {
        out << request.getClientId() << "$"
            << request.getItemName() << "$"
            << request.getStatus() << "$"
            << request.getCreateDate() << "$"
            << request.getFromDate() << "$"
            << request.getToDate() << "$"
            << request.getFinalPrice() << "\n";
    }

    file.close();
}

std::vector<RentalRequest> RentalRequest::getRentalRequests()
{
    QString filePath = QDir::homePath() + "/Documents/rental_requests.txt";
    QFile file(filePath);
    std::vector<RentalRequest> rentalRequests;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return rentalRequests;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList attributes = line.split("$");

        if (attributes.size() == 7) { // Ensure there are exactly 6 attributes
            RentalRequest rentalRequest;
            rentalRequest.setClientId(attributes[0]);
            rentalRequest.setItemName(attributes[1]);
            rentalRequest.setStatus(attributes[2]);
            rentalRequest.setCreateDate(attributes[3]);
            rentalRequest.setFromDate(attributes[4]);
            rentalRequest.setToDate(attributes[5]);
            rentalRequest.setFinalPrice(attributes[6]);

            rentalRequests.push_back(rentalRequest);
        }
    }

    file.close();
    return rentalRequests;
}

QString RentalRequest::getClientId() const
{
    return clientId;
}

void RentalRequest::setClientId(const QString &newClientId)
{
    clientId = newClientId;
}

QString RentalRequest::getItemName() const
{
    return itemName;
}

void RentalRequest::setItemName(const QString &newItemName)
{
    itemName = newItemName;
}

QString RentalRequest::getStatus() const
{
    return status;
}

void RentalRequest::setStatus(const QString &newStatus)
{
    status = newStatus;
}

QString RentalRequest::getCreateDate() const
{
    return createDate;
}

void RentalRequest::setCreateDate(const QString &newCreateDate)
{
    createDate = newCreateDate;
}

QString RentalRequest::getFromDate() const
{
    return fromDate;
}

void RentalRequest::setFromDate(const QString &newFromDate)
{
    fromDate = newFromDate;
}

QString RentalRequest::getToDate() const
{
    return toDate;
}

void RentalRequest::setToDate(const QString &newToDate)
{
    toDate = newToDate;
}

QString RentalRequest::getFinalPrice() const
{
    return finalPrice;
}

void RentalRequest::setFinalPrice(const QString &newFinalPrice)
{
    finalPrice = newFinalPrice;
}


