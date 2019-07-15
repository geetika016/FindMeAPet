#ifndef STAFFMAINWINDOW_H
#define STAFFMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QStackedLayout>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include "viewAnimalWidget.h"
#include "viewClientWidget.h"
#include "viewMatchWidget.h"
#include "addClientDialog.h"
#include "addAnimalDialog.h"
#include "subject.h"
#include "observer.h"
#include "proxySubject.h"
#include "matchingControl.h"

namespace Ui {
class StaffMainWindow;
}

/*
  Class: StaffMainWindow
  Purpose: display the main window as a staff member's perspective, also takes in charge the control flow of the window

  Member function: on_actionView_Animals_triggered
  Purpose: signal handler (under qt context), triggered when user clicks "view animals". shows the table

  Member function: on_actionAdd_Animals_triggered
  Purpose: signal handler, triggered when user clicks "add animal". shows the dialog box for adding a animal

  Member function: updateViewTable
  Purpose: signal handler, trigger the view animal handler to update the table when there is a animal added.
*/

class StaffMainWindow : public ProxySubject
{
    Q_OBJECT

public:
    explicit StaffMainWindow(QWidget *parent = 0);
    ~StaffMainWindow();
    virtual void displayRequest();

private slots:
    void on_actionView_Animals_triggered();
    void on_actionAdd_Animals_triggered();
    void on_actionView_Clients_triggered();
    void tabClosed(int index);
    void on_actionAdd_Clients_triggered();

    void on_actionLaunch_triggered();

    void on_actionMatch_Results_triggered();

private:
    Ui::StaffMainWindow *ui;
    ViewAnimalWidget *viewAnimalWidget;
    ViewAnimalWidget *animalTableIsShowing;
    ViewMatchWidget *viewMatchWidget;
    ViewMatchWidget *matchTableIsShowing;
    ViewClientWidget *clientTableIsShowing;
    AddAnimalDialog *addAnimalDialog;
    AddClientDialog *addClientDialog;
    ViewClientWidget *viewClientWidget;
    Subject *subjectAddClient;
    Observer *observerViewClient;
    Subject *subjectAddAnimal;
    Observer *observerViewAnimal;
    MatchingControl *matchingControl;
    void setSubscription(Subject *subjectAddObj, Observer *observerViewObj);
    bool gotMatches = false;
};

#endif // STAFFMAINWINDOW_H
