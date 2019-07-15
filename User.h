#ifndef USER_H
#define USER_H
#include <QString>
#include <QObject>
#include <QtSql>

class User: public QObject
{
public:
    User();
    ~User();
    QString getUserName();
    void setUserName(QString value);
    QString getUserType();
    void setUserType(QString value);
    int getId();
    void setId(int value);
protected:
    int _id;
    QString _userName;
    QString _type;
};

#endif // USER_H
