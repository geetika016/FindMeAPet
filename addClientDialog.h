#ifndef ADDCLIENTVIEW_H
#define ADDCLIENTVIEW_H

#include <QDialog>
#include <QtDebug>
#include <QMessageBox>
#include "staffDatabaseControl.h"
#include "subject.h"

/*
  Class: AddClientDialog
  Purpose: displays a dialog for feature AddClients, also takes in charge the control flow of the feature

  Member function: constructor
  Purpose: checks the connection status with database

  Member function: checkMandatoryFields
  Purpose: checks if the mandatory fields are filled in

  Member function: on_saveButton_clicked
  Purpose: save the info into database when user chooses to save

  Member function: on_resetButton_clicked
  Purpose: clear the fields when user chooses to reset

  Member function: on_cancelButton_clicked
  Purpose: close the dialog when user chooses to cancel
*/

class StaffDatabaseControl;

namespace Ui {
class AddClientDialog;
}

class AddClientDialog : public Subject
{
    Q_OBJECT
public:
    explicit AddClientDialog(QWidget *parent = nullptr);
    ~AddClientDialog();

private:
    Ui::AddClientDialog *ui;
    StaffDatabaseControl *dbControl;
    void checkMandatoryFields();
    void clearFields();

//signals:
//    void newClientAdded();

private slots:
    void on_saveButton_clicked();
    void on_resetButton_clicked();
    void on_cancelButton_clicked();
};

#endif // ADDCLIENTVIEW_H
