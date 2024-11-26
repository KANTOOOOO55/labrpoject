#ifndef ITEM_H
#define ITEM_H

#include "QtCore/qstring.h"
#include <map>
class Item
{
public:
    Item();
    static std::map<QString, Item>getAllItems();
    static void saveItems(std::map<QString, Item>);
    void saveItem(Item);
    void setName(const QString &value);
    void setDescription(const QString &value);
    void setPrice(const QString &value);
    void setAvailability(const QString &value);
    void setCategory(const QString &value);
    void setNumberOfTimesRented(const QString &value);
    void setRate(const QString &value);
    QString getName() const;
    QString getDescription() const;
    QString getPrice() const;
    QString getAvailability() const;
    QString getCategory() const;
    QString getNumberOfTimesRented() const;
    QString getRate() const;
private:
    QString name;
    QString description;
    QString price;
    QString avalability;
    QString category;
    QString numberOfTimesRented;
    QString rate;
};

#endif // ITEM_H
