#ifndef USER_H
#define USER_H

#include "QtCore/qstring.h"
class User
{
public:
    User();
    QString getEmail() const;
    void setEmail(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);

private:
    QString email;
    QString password;
};

#endif // USER_H
