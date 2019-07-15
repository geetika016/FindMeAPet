#ifndef MYMODEL_H
#define MYMODEL_H
#include <QtSql>

/*
  Class: DataModel
  Purpose: Override the funtions of QSqlTableModel class so that we can customize the color and font within a sigle cell

  Member function: data
  Purpose: override the original funtion so that it knows what how to set the style of some specified cells
*/

class DataModel : public QSqlTableModel
{
    Q_OBJECT
public:
    DataModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // MYMODEL_H
