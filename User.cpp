#include "User.h"

User::User() : _id(-1){}

User::~User() {}

QString User::getUserName() {
    return _userName;
}

void User::setUserName(QString value) {
    _userName = value;
}

QString User::getUserType() {
    return _type;
}

void User::setUserType(QString value) {
    _type = value;
}

int User::getId() {
    return _id;
}

void User::setId(int value) {
    _id = value;
}
