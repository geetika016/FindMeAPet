#include "dataModelControl.h"

DataModelControl::DataModelControl(QObject *parent) : QObject(parent)
{

}

bool DataModelControl::buildModel(DataModel *output, DBSettings *settings)
{
    output->setEditStrategy(settings->editStrategy);
    output->setTable(settings->table);

    if ((settings->colHeaderOperation->name) == QString("replace"))
    {
        for(int i=0; i<output->columnCount(); i++)
            output->setHeaderData(i, Qt::Horizontal, output->headerData(i, Qt::Horizontal).
                                  toString().replace(settings->colHeaderOperation->arg1, settings->colHeaderOperation->arg2));
    }

    if (!output->select())
        return false;

    if ((settings->cellsOperation != NULL) && (settings->cellsOperation->name) == QString("overwrite"))
    {
        QMetaType::Type dataType = settings->cellsOperation->dataType;
        for(int i=0; i<output->rowCount(); i++)
            for(int j=0; j<output->columnCount(); j++)
            {
                 if (output->data(output->index(i, j)).userType() == dataType)
                 {
                     if (dataType == QMetaType::QString)
                        if(output->data(output->index(i, j)).toString() == settings->cellsOperation->arg1)
                            output->setData(output->index(i, j), settings->cellsOperation->arg2);
                 }
            }
    }

    if (output->lastError().type() != QSqlError::NoError)
        return false;

    return true;
}
