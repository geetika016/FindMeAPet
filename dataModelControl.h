#ifndef DATAMODELCONTROL_H
#define DATAMODELCONTROL_H

#include <QObject>
#include "dataModel.h"
#include "databaseControl.h"

struct DBSettings;

class DataModelControl : public QObject
{
    Q_OBJECT

public:
    explicit DataModelControl(QObject *parent = nullptr);
    bool buildModel(DataModel *output, DBSettings *settings);

signals:

public slots:
};

#endif // DATAMODELCONTROL_H
