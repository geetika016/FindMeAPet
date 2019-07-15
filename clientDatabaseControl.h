#ifndef CLIENTDATABASECONTROL_H
#define CLIENTDATABASECONTROL_H

#include <QObject>
#include <QHash>
#include "databaseControl.h"
#include "dataModel.h"
#include "clientMainWindow.h"

#define READ_CLIENT 1
#define CLIENT_VIEW_ANIMAL 2
#define UPDATE_CLIENT 3

class DatabaseControl;

class ClientDatabaseControl : public QObject
{
    Q_OBJECT

private:
    DatabaseControl *dbControl;
    QString username;

public:
    explicit ClientDatabaseControl(QString name, QObject *parent = nullptr);
    bool dbRequest(void *input, void *output, int id, QString *errMsg = NULL,bool prefChanged = false);
    bool editClientRequest(void *output, QString *errMsg);
    bool viewAnimalRequest(DataModel *output, QString *errMsg);
    bool updateClientRequest(QHash<QString, QString> *input, QString *errMsg, bool prefChanged = false);
};

#endif // CLIENTDATABASECONTROL_H
