#ifndef RENTALREQUEST_H
#define RENTALREQUEST_H

#include "QtCore/qstring.h"
#include <vector>
class RentalRequest
{
public:
    RentalRequest();
    static void saveRentalRequests(std::vector<RentalRequest> rentalRequests);
    static void saveRentalRequest(RentalRequest rentalRequest);
    static std::vector<RentalRequest> getRentalRequests();
    QString getClientId() const;
    void setClientId(const QString &newClientId);
    QString getItemName() const;
    void setItemName(const QString &newItemName);
    QString getStatus() const;
    void setStatus(const QString &newStatus);
    QString getCreateDate() const;
    void setCreateDate(const QString &newCreateDate);
    QString getFromDate() const;
    void setFromDate(const QString &newFromDate);
    QString getToDate() const;
    void setToDate(const QString &newToDate);
    QString getFinalPrice() const;
    void setFinalPrice(const QString &newFinalPrice);

private:
    QString clientId;
    QString itemName;
    QString status;
    QString createDate;
    QString fromDate;
    QString toDate;
    QString finalPrice;
};

#endif // RENTALREQUEST_H
