#include "dataModel.h"

DataModel::DataModel(QObject *parent)
    : QSqlTableModel(parent)
{
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    QString text = QSqlTableModel::data(index).toString();

    switch (role) {
    case Qt::FontRole:
        if (text == "More" || text == "Edit") //change background only for cell that have text 'More'
        {
            QFont font;
            font.setUnderline(true);
            return font;
        }
        break;
    case Qt::ForegroundRole:
        if (text == "More" || text == "Edit")
            return QBrush(Qt::blue);
        break;

    default:
        return QSqlTableModel::data(index, role);
    }
    return QVariant();
}
