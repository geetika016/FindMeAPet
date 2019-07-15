#include "clientDatabaseControl.h"

ClientDatabaseControl::ClientDatabaseControl(QString name, QObject *parent) :
    QObject(parent),
    username(name)
{
    dbControl = new DatabaseControl;
}

bool ClientDatabaseControl::dbRequest(void *input, void *output, int id, QString *errMsg, bool prefChanged)
{
    DBSettings settings;
    switch (id) {
    case READ_CLIENT:
        editClientRequest(output, errMsg);
        break;
    case UPDATE_CLIENT:
        updateClientRequest((QHash<QString, QString> *)input, errMsg, prefChanged);
        break;
    default:
        break;
    }
    return true;
}

bool ClientDatabaseControl::updateClientRequest(QHash<QString, QString> *input, QString *errMsg, bool prefChanged)
{
    struct DBSettings settings;
    settings.table = QString("clients");
    settings.preferenceChanged = prefChanged;
    return dbControl->dbRequest(input, NULL, &settings, UPDATE, errMsg);
}


bool ClientDatabaseControl::editClientRequest(void *output, QString *errMsg)
{
    //read from the db
    struct DBSettings settings;
    settings.table = QString("clients");
    QHash<QString, QString> input;
    input["name"] = username;
    dbControl->dbRequest((void *)&input, (void *)output, &settings, READ, errMsg);
    //the passing process of username: Proxy->ClientMainWindow->ViewEditClientDialog->ClientDBControl
    return true;
}

bool ClientDatabaseControl::viewAnimalRequest(DataModel *output, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("animals");
    settings.editStrategy = QSqlTableModel::OnManualSubmit;
    ColHeaderOperation colHeaderOperation;
    colHeaderOperation.name = QString("replace");
    colHeaderOperation.arg1 = QString("_");
    colHeaderOperation.arg2 = QString(" ");
    settings.colHeaderOperation = &colHeaderOperation;
    CellsOperation cellsOperation;
    cellsOperation.name = QString("overwrite");
    cellsOperation.dataType = QMetaType::QString;
    cellsOperation.arg1 = QString("");
    cellsOperation.arg2 = QString("N/A");
    settings.colHeaderOperation = &colHeaderOperation;
    settings.cellsOperation = &cellsOperation;
    return dbControl->dbRequest(NULL, output, &settings, MODEL, errMsg);
}
