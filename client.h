#ifndef CLIENT_H
#define CLIENT_H

#include "user.h"
#include <map>

class Client: public User
{
public:
    Client();
    static std::map<QString, Client> getAllClients();
    static void saveAllClients(std::map<QString, Client> clients);
    static void saveClient(Client client);
    static QString login(QString email, QString password);
    QString getName() const;
    void setName(const QString &value);
    QString getPhone() const;
    void setPhone(const QString &value);

private:
    QString name;
    QString phone;
};

#endif // CLIENT_H
