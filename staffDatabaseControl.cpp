#include "staffDatabaseControl.h"

StaffDatabaseControl::StaffDatabaseControl(QObject *parent) : QObject(parent)
{
    dbControl = new DatabaseControl;
}

bool StaffDatabaseControl::dbRequest(void *input, void *output, int id, QString *errMsg)
{
    bool rtval;

    switch (id) {
    case ADD_CLIENT:
        rtval = addClientRequest((QHash<QString, QString> *)input, errMsg);
        break;
    case ADD_ANIMAL:
        rtval = addAnimalRequest((QHash<QString, QString> *)input, errMsg);
        break;
    case VIEW_CLIENT:
        rtval = viewClientRequest((DataModel *)output, errMsg);
        break;
    case VIEW_ANIMAL:
        rtval = viewAnimalRequest((DataModel *)output, errMsg);
        break;
    case ADD_USER:
        rtval = addUserRequest((QHash<QString, QString> *)input, errMsg);
        break;
    case UPDATE_ANIMAL:
        rtval = updateAnimalRequest((QHash<QString, QString> *)input, errMsg);
        break;
    case ALGORITHM_READ_ANIMAL:
        rtval = algorithmReadAnimalRequest((QHash<QString, QString> *)input, (QList<QHash<QString, QString>> *)output, errMsg);
        break;
    case ALGORITHM_READ_CLIENT:
        rtval = algorithmReadClientRequest((QHash<QString, QString> *)input, (QList<QHash<QString, QString>> *)output, errMsg);
        break;
    case WRITE_RESULT:
        rtval = writeResultRequest((QHash<QString, QString> *)input, errMsg);
        break;
    case ALGORITHM_CLEAN_TABLE:
        rtval = algorithmCleanTable(errMsg);
        break;
    case VIEW_MATCHES:
        rtval = viewMatchRequest((DataModel *)output, errMsg);
    default:
        break;
    }

    return rtval;
}

bool StaffDatabaseControl::algorithmCleanTable(QString *errMsg)
{
    QString input = "results";
    return dbControl->dbRequest(&input, NULL, NULL, CLEAN_TABLE, errMsg);
}
bool StaffDatabaseControl::writeResultRequest(QHash<QString, QString> *input, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("results");
    return dbControl->dbRequest(input, NULL, &settings, WRITE, errMsg);
}

bool StaffDatabaseControl::addClientRequest(QHash<QString, QString> *input, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("clients");
    return dbControl->dbRequest(input, NULL, &settings, WRITE, errMsg);
}

bool StaffDatabaseControl::addAnimalRequest(QHash<QString, QString> *input, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("animals");
    return dbControl->dbRequest(input, NULL, &settings, WRITE, errMsg);
}

bool StaffDatabaseControl::updateAnimalRequest(QHash<QString, QString> *input, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("animals");
    return dbControl->dbRequest(input, NULL, &settings, UPDATE, errMsg);
}

bool StaffDatabaseControl::viewClientRequest(DataModel *output, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("clients");
    settings.editStrategy = QSqlTableModel::OnManualSubmit;
    ColHeaderOperation colHeaderOperation;
    colHeaderOperation.name = "replace";
    colHeaderOperation.arg1 = "_";
    colHeaderOperation.arg2 = " ";
    settings.colHeaderOperation = &colHeaderOperation;

    return dbControl->dbRequest(NULL, output, &settings, MODEL, errMsg);
}

bool StaffDatabaseControl::addUserRequest(QHash<QString, QString> *input, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("users");
    return dbControl->dbRequest(input, NULL, &settings, WRITE, errMsg);
}

bool StaffDatabaseControl::viewAnimalRequest(DataModel *output, QString *errMsg)
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

bool StaffDatabaseControl::algorithmReadAnimalRequest(QHash<QString, QString> *input, QList<QHash<QString, QString>> *output, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("animals");
    return dbControl->dbRequest(input, output, &settings, READ, errMsg);
}

bool StaffDatabaseControl::algorithmReadClientRequest(QHash<QString, QString> *input, QList<QHash<QString, QString>> *output, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("clients");
    return dbControl->dbRequest(input, output, &settings, READ, errMsg);
}

bool StaffDatabaseControl::viewMatchRequest(DataModel *output, QString *errMsg)
{
    struct DBSettings settings;
    settings.table = QString("results");
    settings.editStrategy = QSqlTableModel::OnManualSubmit;
    ColHeaderOperation colHeaderOperation;
    colHeaderOperation.name = "replace";
    colHeaderOperation.arg1 = "_";
    colHeaderOperation.arg2 = " ";
    settings.colHeaderOperation = &colHeaderOperation;

    return dbControl->dbRequest(NULL, output, &settings, MODEL, errMsg);
}
