#ifndef QUERYCONTROL_H
#define QUERYCONTROL_H

#include "databaseControl.h"
#include <QtSql>

struct DBSettings;
struct Authentication;
struct ClientInfo;

class QueryControl
{
public:
    QueryControl();
    bool dbWrite(QHash<QString, QString> *input, DBSettings *settings, QString *errMsg);
    bool dbUpdate(QHash<QString, QString> *input, DBSettings *settings, QString *errMsg);
    bool dbCheck(QHash<QString, QString> *input, Authentication *output, DBSettings *settings, QString *errMsg);
    bool dbRead(QHash<QString, QString> *input, QList<QHash<QString, QString>> *output, DBSettings *settings, QString *errMsg);
    bool createTable(QHash<QString, QString> *input, bool *output, DBSettings *settings);
    bool dbCleanTable(QString *input, QString *errMsg);
};

#endif // QUERYCONTROL_H
