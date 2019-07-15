#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H

#include <QObject>
#include <QSql>
#include <QMessageBox>
#include "queryControl.h"
#include "dataModelControl.h"

#define CHECK 0
#define WRITE 1
#define MODEL 2
#define READ 3
#define CREATE_TABLE 4
#define UPDATE 5
#define CLEAN_TABLE 6

struct ColHeaderOperation{
    QString name;
    QString arg1;
    QString arg2;
};

struct CellsOperation{
    QString name;
    QMetaType::Type dataType;
    QVariant arg1;
    QVariant arg2;
};

struct DBSettings{
    QString table;
    bool preferenceChanged = false;
    QSqlTableModel::EditStrategy editStrategy;
    ColHeaderOperation *colHeaderOperation;
    CellsOperation *cellsOperation = NULL;
    bool update = false;
};

struct Authentication
{
    bool accept = false;
    QString username = "";
    QString role = "";
    QString msg = "";
};

class QueryControl;
class DataModelControl;

class DatabaseControl : public QObject
{
    Q_OBJECT
private:
    QueryControl *queryControl;
    DataModelControl *dataModelControl;

public:
    explicit DatabaseControl(QObject *parent = nullptr);
    ~DatabaseControl();
    bool openDB(QString dbName);
    bool dbRequest(void *input, void *output, DBSettings *settings, int type, QString *errMsg);

signals:

public slots:
};

#endif // DATABASECONTROL_H
