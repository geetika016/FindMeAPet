#ifndef VIEWMATCHWIDGET_H
#define VIEWMATCHWIDGET_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QFont>
#include "ui_viewMatchWidget.h"
#include "detailedAnimalDialog.h"
#include "dataModel.h"
#include "staffDatabaseControl.h"

#define SUMMARY_ATTRIBUTES_NUM 3
//#define MAX_ANIMAL_NUM 100
#define MAX_ATTRIBUTES_NUM 100
#define MAX_ATTRIBUTES_NUM_DOUBLE 200

namespace Ui {
class ViewMatchWidget;
}

class ViewMatchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewMatchWidget(QWidget *parent = 0);
    void configure(QTableView *tableView, QString *attributes, int attributesShown);
    ~ViewMatchWidget();

private:
    Ui::ViewMatchWidget *ui;
    DataModel *model;
    StaffDatabaseControl *dbControl;
    DetailedAnimalDialog* detailedAnimalDialog;
    QSqlError buildDataModel(DataModel *model);
    static QString summaryAttributes[SUMMARY_ATTRIBUTES_NUM];
    void showAnimalDetail(int row, int edit);

private slots:
    void clicked(const QModelIndex &modelIndex);
};

#endif // VIEWMATCHWIDGET_H

