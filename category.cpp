#include "category.h"

#include <QDir>

Category::Category(QString name)
{
    this->name = name;
}

void Category::saveCategories(std::vector<Category> categories)
{
    QString filePath = QDir::homePath() + "/Documents/categories.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::ios_base::failure("Failed to open the file for writing!");
    }

    QTextStream out(&file);
        for (const Category& category : categories) {
        out << category.getName() << "\n";
    }

    file.close();
}

std::vector<Category> Category::getCategories()
{
    QString filePath = QDir::homePath() + "/Documents/categories.txt";
    QFile file(filePath);

    std::vector<Category> categories;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::ios_base::failure("Failed to open the file for reading!");
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString name = in.readLine();
        Category category(name);
        categories.push_back(category);
    }

    file.close();
    return categories;
}

void Category::setName(QString name)
{
    this->name = name;
}

QString Category::getName() const
{
    return this->name;
}
