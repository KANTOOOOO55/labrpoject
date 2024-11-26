#include "client.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QDir>
#include <map>

Client::Client() {}

std::map<QString, Client> Client::getAllClients()
{
    QString filePath = QDir::homePath() + "/Documents/clients.txt";
    QFile file(filePath);
    std::map<QString, Client> clients;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return clients;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList attributes = line.split("$");

        if (attributes.size() < 4) {
            continue; // Skip incomplete lines
        }

        Client client;
        client.setName(attributes[0]);
        client.setPassword(attributes[1]);
        client.setPhone(attributes[2]);
        client.setEmail(attributes[3]);
        clients[client.getName()] = client;
    }

    file.close();
    return clients;
}

QString Client::getName() const {
    return name;
}

void Client::setName(const QString &value) {
    name = value;
}

QString Client::getPhone() const {
    return phone;
}

void Client::setPhone(const QString &value) {
    phone = value;
}

void Client::saveClient(Client client)
{
    QString filePath = QDir::homePath() + "/Documents/clients.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    out << client.getName() << "$"
        << client.getPassword() << "$"
        << client.getPhone() << "$"
        << client.getEmail() << "\n";
    file.close();
}

void Client::saveAllClients(std::map<QString, Client> clients)
{
    QString filePath = QDir::homePath() + "/Documents/clients.txt";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    file.close();

    for (const auto& [id, client] : clients) {
        saveClient(client);
    }
}

QString Client::login(QString email, QString password)
{
    std::map<QString, Client> clients = getAllClients();

    for (const auto& [id, client] : clients) {
        if (client.getEmail() == email && client.getPassword() == password) {
            return id;
        }
    }

    return "-1";
}
