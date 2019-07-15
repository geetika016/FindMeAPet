#include "queryControl.h"

QueryControl::QueryControl()
{

}

bool QueryControl::dbWrite(QHash<QString, QString> *input, DBSettings *settings, QString *errMsg)
{
    QSqlQuery query;
    QString table;
    QString keys = "";
    QString values = "";

    if(settings->table == NULL)
    {
        *errMsg = QString("Table unspecified");
        return false;
    }

    table = settings->table;
    if(table == "animals" && input->value("name") == "")
    {
        *errMsg = QString("Add Failed! Please Specify Name!");
        return false;
    }
    QHashIterator<QString, QString> i(*input);

    while (i.hasNext())
    {
        i.next();
        keys += i.key() + ",";
        values += "'" + i.value() + "',";
    }
    keys.chop(1);
    values.chop(1);
    //qDebug()<<"insert into " + table + "(" + keys + ") values (" + values + ")";
    query.prepare("insert into " + table + "(" + keys + ") values (" + values + ")");

    if (!query.exec())
    {
        *errMsg = query.lastError().text();
        if(*errMsg == "UNIQUE constraint failed: clients.name Unable to fetch row")
            *errMsg = "The username you've entered has already been taken, please try again.";
        return false;
    }
    return true;
}

bool QueryControl::dbUpdate(QHash<QString, QString> *input, DBSettings *settings, QString *errMsg)
{
    QSqlQuery query;
    QString id = input->value("id") ;
    QString table = settings->table;
    QString set = "";
    QHashIterator<QString, QString> i(*input);
    if(table == "animals" && input->value("name") == "")
    {
        *errMsg = QString("Update Failed! Please Specify Name!");
        return false;
    }
    /*
     * add code here to check animal_type values before and after updating;
        if they are different , first set all previous columns to null
        deleteclientInfo
    if(settings->prepreferenceChanged)
        do stuff to previous data first
        and then update with the new data

    */
    while (i.hasNext())
    {
        i.next();
        set += i.key() + "='" + i.value() + "',";
    }
    set.chop(1);
    query.prepare("update " + table + " set " + set + " where id = " + id);
    if (!query.exec())
    {
        *errMsg = query.lastError().text();
        return false;
    }
    return true;
}

bool QueryControl::dbCheck(QHash<QString, QString> *input, Authentication *output, DBSettings *settings, QString *errMsg)
{
    QSqlQuery query;
    QString table = settings->table;
    QString username = input->begin().key();
    QString password = input->begin().value();

    query.prepare("select * FROM " + table + " where lower(username) = lower(?)");
    query.bindValue(0, username);
    if (!query.exec())
    {
        *errMsg = QString("Failure on checking");
        return false;
    }

    if (!query.first())
    {
        output->msg = "Authentication failed, username not found";
        output->accept = false;
    }
    else
    {
        QString dbpassword = query.value(2).toString(); // Get the Password
        if (password == dbpassword)
        {
            output->accept = true;
            output->username = query.value(1).toString();
            output->role = query.value(3).toString();
        }
        else
        {
            output->msg = "Authentication failed, invalid password";
            output->accept = false;
        }
    }
    return true;
}

bool QueryControl::dbRead(QHash<QString, QString> *input, QList<QHash<QString, QString>> *output, DBSettings *settings, QString *errMsg)
{
    QSqlQuery query;
    QString table = settings->table;
    QString inputKey = input->begin().key();
    QString inputValue = input->begin().value();
    int rowCount = 0;
    query.prepare("select * from " + table + " where " + inputKey + " = '" + inputValue +"' ");
    if (!query.exec())
    {
        *errMsg = "Failure on reading: " + query.lastError().text();
        return false;
    }

    while (query.next())
    {
        QHash<QString, QString> hash;
        for (int i=0; i<query.record().count(); i++){
            hash.insert(query.record().fieldName(i), query.value(i).toString());
            //qDebug()<<query.record().fieldName(i)<<query.value(i).toString();
        }
        //qDebug()<<"    ";
        output->append(hash);
        ++rowCount;
    }

    //qDebug()<<"query at:"<<query.at();
    //qDebug()<<"rows:"<<rowCount;
    if (/*rowCount != query.at() ||  */rowCount == 0)
    {
        //qDebug()<<"select * from " + table + " where " + inputKey + " = '" + inputValue +"' ";
        //qDebug()<<"query get 0 rows";
    }

    return true;
}

bool QueryControl::createTable(QHash<QString, QString> *input, bool *output, DBSettings *settings)
{
    QString table = input->begin().key();
    QSqlQuery query;

    if(query.exec("SELECT 1 FROM " + table + " LIMIT 1"))
    {
        if(output != NULL)
            *output = true;
        return true;
    }

    if (!query.exec("create table " + table + input->begin().value()))
    {
        QMessageBox::critical(NULL,
                              QObject::tr("Database error"),
                              QObject::tr("Unable to create table"));
        return false;
    }

    if(output != NULL)
        *output = false;
    return true;
}

bool QueryControl::dbCleanTable(QString *input, QString *errMsg)
{
    QSqlQuery query;
    if(!query.exec("delete from " + *input))
    {
        *errMsg = query.lastError().text();
        return false;
    }
    return true;
}
