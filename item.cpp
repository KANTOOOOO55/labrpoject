#include "item.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

Item::Item() {}

std::map<QString, Item> Item::getAllItems()
{
    std::map<QString, Item> items;
    QString filePath = QDir::homePath() + "/Documents/items.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return items;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList attributes = line.split("$");
        if (attributes.size() != 7) continue;
        Item item;
        item.setName(attributes[0]);
        item.setDescription(attributes[1]);
        item.setPrice(attributes[2]);
        item.setAvailability(attributes[3]);
        item.setCategory(attributes[4]);
        item.setNumberOfTimesRented(attributes[5]);
        item.setRate(attributes[6]);
        items[item.getName()] = item;
    }

    file.close();
    return items;
}

void Item::saveItems(std::map<QString, Item> items)
{
    QString filePath = QDir::homePath() + "/Documents/items.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for (const auto& [key, item] : items) {
        out << item.getName() << "$"
            << item.getDescription() << "$"
            << item.getPrice() << "$"
            << item.getAvailability() << "$"
            << item.getCategory() << "$"
            << item.getNumberOfTimesRented() << "$"
            << item.getRate() << "\n";
    }

    file.close();
}

void Item::saveItem(Item item) {
    std::map<QString, Item> items = getAllItems();
    items[item.getName()] = item;
    saveItems(items);
}

void Item::setName(const QString& value) {
    name = value;
}

void Item::setDescription(const QString& value) {
    description = value;
}

void Item::setPrice(const QString& value) {
    price = value;
}

void Item::setAvailability(const QString& value) {
    avalability = value;
}

void Item::setCategory(const QString& value) {
    category = value;
}

void Item::setNumberOfTimesRented(const QString& value) {
    numberOfTimesRented = value;
}

void Item::setRate(const QString& value) {
    rate = value;
}

QString Item::getName() const {
    return name;
}
QString Item::getDescription() const {
    return description;
}
QString Item::getPrice() const {
    return price;
}
QString Item::getAvailability() const {
    return avalability;
}
QString Item::getCategory() const {
    return category;
}
QString Item::getNumberOfTimesRented() const {
    return numberOfTimesRented;
}
QString Item::getRate() const {
    return rate;
}
