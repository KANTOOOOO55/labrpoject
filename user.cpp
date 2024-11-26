#include "user.h"

User::User() {}

QString User::getEmail() const {
    return email;
}

void User::setEmail(const QString &value) {
    email = value;
}

QString User::getPassword() const {
    return password;
}

void User::setPassword(const QString &value) {
    password = value;
}
