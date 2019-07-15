#ifndef CLIENTLISTVIEW_H
#define CLIENTLISTVIEW_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include "ui_viewClientWidget.h"
#include "dataModel.h"
#include "staffDatabaseControl.h"
#include "observer.h"
#include "viewEditClientDialog.h"

#define CLIENT_SUMMARY_ATTRIBUTES_NUM 4
#define MAX_ATTRIBUTES_NUM 50
#define MAX_ATTRIBUTES_NUM_DOUBLE 100

/*
  Class: ViewClientWidget
  Purpose: displays a table for feature ViewAnimals, also takes in charge the control flow of the feature

  Member function: constructor
  Purpose: creates a data model for in program storage, also provides format info for QTableView object

  Member function: buildDataModel
  Purpose: intializes and polulates the model

  Member function: configure()
  Purpose: set up the QTableView object

*/

class ViewClientWidget : public Observer
{
    Q_OBJECT

private:
    Ui::ViewClientWidget ui;
    DataModel *model;
    StaffDatabaseControl *dbControl;
    ViewEditClientDialog* viewEditClientDialog;
    QSqlError buildDataModel(DataModel *model);
    static QString summaryAttributes[CLIENT_SUMMARY_ATTRIBUTES_NUM];
    void showClientDetail(int row);
    int user_type = 1;

public:
    explicit ViewClientWidget(QWidget *parent = nullptr, int user_type = 1);
    ~ViewClientWidget();
    void configure(QTableView *tableView, QString *attributes, int attributesShown);    
    virtual void update(Subject * subject);

private slots:
    void clicked(const QModelIndex &modelIndex);
};

#endif // CLIENTLISTVIEW_H
