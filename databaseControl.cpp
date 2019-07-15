#include "databaseControl.h"

DatabaseControl::DatabaseControl(QObject *parent) : QObject(parent)
{
    queryControl = new QueryControl;
    dataModelControl = new DataModelControl;
}

DatabaseControl::~DatabaseControl()
{
    delete queryControl;
    delete dataModelControl;
}

bool DatabaseControl::openDB(QString dbName)
{
    //check for the SQLITE driver
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
            QMessageBox::critical(NULL,
                                  QObject::tr("Unable to load database"),
                                  QObject::tr("The initialization needs the SQLITE driver"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open())//if no database file exits, db.open() will create a empty one
    {
        QMessageBox::critical(NULL,
                              QObject::tr("Unable to open/create database"),
                              db.lastError().text());
        return false;
    }

    return true;
}

bool DatabaseControl::dbRequest(void *input, void *output, DBSettings *settings, int type, QString *errMsg)
{
    bool rtval;

    switch (type) {
    case WRITE:
        rtval = queryControl->dbWrite((QHash<QString, QString> *)input, settings, errMsg);
        break;
    case READ:
        rtval = queryControl->dbRead((QHash<QString, QString> *)input, (QList<QHash<QString, QString>> *)output, settings, errMsg);
        break;
    case CHECK:
        rtval = queryControl->dbCheck((QHash<QString, QString> *)input, (Authentication *)output, settings, errMsg);
        break;
    case MODEL:
        rtval = dataModelControl->buildModel((DataModel *)output, settings);
        break;
    case CREATE_TABLE:
        rtval = queryControl->createTable((QHash<QString, QString> *)input, (bool *)output, settings);
        break;
    case UPDATE:
        rtval = queryControl->dbUpdate((QHash<QString, QString> *)input, settings, errMsg);
        break;
    case CLEAN_TABLE:
        rtval = queryControl->dbCleanTable((QString *)input, errMsg);
        break;
    default:
        break;
    }

    return rtval;
}
