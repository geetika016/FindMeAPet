#ifndef OVERALLCONTROL_H
#define OVERALLCONTROL_H

#include <QtSql>
//#include <QMessageBox>
#include <QApplication>
#include "proxy.h"
#include "databaseControl.h"
//#include <QDesktopWidget>
//#include "staffMainWindow.h"
//#include "loginDialog.h"

#define ATTRIBUTES_NUM_DOG 34 //32
#define ATTRIBUTES_NUM_CAT 35 //35
#define ATTRIBUTES_NUM_BIRD 18 //18
#define ATTRIBUTES_NUM_RABBIT 14 //14
#define ATTRIBUTES_NUM_HAMSTER 15 //16
#define ATTRIBUTES_NUM_GUINEA_PIGS 14 //15
#define ATTRIBUTES_NUM_CLIENT 33

/*
  Class: OverAllControl
  Purpose: takes in charge the control flow for the program

  Member function: initializeDB
  Purpose: do the checkings for database and initialize it if required

  Member function: addInitAnimal
  Purpose: a helper funtion for initializeDB

  Member function: launch
  Purpose: launchs the program. intializes the database and shows the main window in a staff member's perspective
*/

class OverAllControl : public QObject
{
    Q_OBJECT

private:
    //StaffMainWindow sWindow;
    //LoginDialog loginDialog;
    Proxy *proxy;
    bool initializeDB();
    DatabaseControl *dbControl;
    void addToDB(QSqlQuery &query, QString *attributes, int size);
    void initializeHelper(QHash<QString, QString> &hash, QString *fields, QString *data, int size, QString table);

//private slots:
//    void acceptLogin();
//    void rejectLogin();

public:
    OverAllControl();
    ~OverAllControl();
    void launch();
    QSqlDatabase db;
};

#endif // OVERALLCONTROL_H
