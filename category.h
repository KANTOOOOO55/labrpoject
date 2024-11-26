#ifndef CATEGORY_H
#define CATEGORY_H

#include "QtCore/qstring.h"
class Category
{
public:
    Category(QString name);
    static void saveCategories(std::vector<Category> categories);
    static std::vector<Category> getCategories();
    void setName(QString name);
    QString getName() const;
private:
    QString name;
};

#endif // CATEGORY_H
