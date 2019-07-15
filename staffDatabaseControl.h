#ifndef STAFFDATABASECONTROL_H
#define STAFFDATABASECONTROL_H

#include <QObject>
#include <QHash>
#include "databaseControl.h"
#include "dataModel.h"

#define ADD_ANIMAL 1
#define ADD_CLIENT 2
#define VIEW_ANIMAL 3
#define VIEW_CLIENT 4
#define ADD_USER 5
#define UPDATE_ANIMAL 6
#define ALGORITHM_READ_ANIMAL 7
#define ALGORITHM_READ_CLIENT 8
#define WRITE_RESULT 9
#define ALGORITHM_CLEAN_TABLE 10
#define VIEW_MATCHES 11

class DatabaseControl;

class StaffDatabaseControl : public QObject
{
    Q_OBJECT

private:
    DatabaseControl *dbControl;

public:
    explicit StaffDatabaseControl(QObject *parent = nullptr);
    bool dbRequest(void *input, void *output, int id, QString *errMsg = NULL);
    bool addClientRequest(QHash<QString, QString> *input, QString *errMsg);
    bool addAnimalRequest(QHash<QString, QString> *input, QString *errMsg);
    bool updateAnimalRequest(QHash<QString, QString> *input, QString *errMsg);
    bool addUserRequest(QHash<QString, QString> *input, QString *errMsg);
    bool viewClientRequest(DataModel *output, QString *errMsg);
    bool viewAnimalRequest(DataModel *output, QString *errMsg);
    bool viewMatchRequest(DataModel *output, QString *errMsg);
    bool algorithmReadAnimalRequest(QHash<QString, QString> *input, QList<QHash<QString, QString>> *output, QString *errMsg);
    bool algorithmReadClientRequest(QHash<QString, QString> *input, QList<QHash<QString, QString>> *output, QString *errMsg);
    bool writeResultRequest(QHash<QString, QString> *input, QString *errMsg);
    bool algorithmCleanTable(QString *errMsg);
};

#endif // STAFFDATABASECONTROL_H
