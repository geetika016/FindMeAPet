#ifndef ANIMALLISTVIEW_H
#define ANIMALLISTVIEW_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QFont>
#include "ui_viewAnimalWidget.h"
#include "detailedAnimalDialog.h"
#include "dataModel.h"
#include "staffDatabaseControl.h"
#include "observer.h"
#include "addAnimalDialog.h"

#define SUMMARY_ATTRIBUTES_NUM 13
//#define MAX_ANIMAL_NUM 100
#define MAX_ATTRIBUTES_NUM 50
#define MAX_ATTRIBUTES_NUM_DOUBLE 100

namespace Ui {
class ViewAnimalWidget;
}

/*
  Class: ViewAnimalWidget
  Purpose: displays a table for feature ViewAnimals, also takes in charge the control flow of the feature

  Member function: constructor
  Purpose: creates a data model for in program storage, also provides format info for QTableView object

  Member function: buildDataModel
  Purpose: intializes and polulates the model

  Member function: configure()
  Purpose: set up the QTableView object

  Member function: showAnimalDetail
  Purpose: extract the information of attributes and pass them to the dialog box showing detailed animal information

  Member function: clicked
  Purpose: signal handler triggered when client click on more
*/

class ViewAnimalWidget : public Observer
{
    Q_OBJECT

private:
    Ui::ViewAnimalWidget ui;
    DataModel *model;
    StaffDatabaseControl *dbControl;
    DetailedAnimalDialog* detailedAnimalDialog;
    AddAnimalDialog* addAnimalDialog;
    QSqlError buildDataModel(DataModel *model);
    static QString summaryAttributes[SUMMARY_ATTRIBUTES_NUM];
    void showAnimalDetail(int row);
    int user_type = 0;

public:
    explicit ViewAnimalWidget(QWidget *parent = nullptr, int user_type=0);
    ~ViewAnimalWidget();
    void configure(QTableView *tableView, QString *attributes, int attributesShown);
    virtual void update(Subject * subject);

private slots:
    void clicked(const QModelIndex &modelIndex);
    void animalEdited();
};

#endif // ANIMALLISTVIEW_H
