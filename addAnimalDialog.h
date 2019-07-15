#ifndef AddAnimalDialogVIEW_H
#define AddAnimalDialogVIEW_H

#include <QDialog>
#include <QtDebug>
#include <QSlider>
#include <QMessageBox>
#include "staffDatabaseControl.h"
#include "subject.h"

namespace Ui {
class AddAnimalDialog;
}

/*
  Class: AddAnimalDialog
  Purpose: displays a dialog for feature AddAnimals, also takes in charge the control flow of the feature

  Member function: constructor
  Purpose: checks the connection status with database

  Member function: on_saveButton_clicked
  Purpose: save the info into database when user chooses to save

  Member function: on_resetButton_clicked
  Purpose: clear the fields when user chooses to reset

  Member function: on_cancelButton_clicked
  Purpose: close the dialog when user chooses to cancel

  Member function: newAnimalAdded
  Purpose: signal sent to staffMainWindow object, so that the latter can update when new animal added

  Member function: addDog/Cat/...
  Purpose: add a sigle type of animal to the database based on the user's selection
*/

class AddAnimalDialog : public Subject
{
    Q_OBJECT

private:
    Ui::AddAnimalDialog *ui;
    StaffDatabaseControl *dbControl;
    int typecounter;
    bool update = false;
    int rowNum;

public:
    explicit AddAnimalDialog(QWidget *parent = 0);
    explicit AddAnimalDialog(int row, int num, QString* attr, QWidget *parent=0, int animal_type=0, int user_type=0, bool readOnly = true);
    ~AddAnimalDialog();

public slots:
    void setBreed();

private slots:
    void clearFields();
    void addDog(QHash<QString, QString> &input);
    void addCat(QHash<QString, QString> &input);
    void addBird(QHash<QString, QString> &input);
    void addRabbit(QHash<QString, QString> &input);
    void addHamster(QHash<QString, QString> &input);
    void addGuineaPig(QHash<QString, QString> &input);
    void setDogView(QString* attr);
    void setCatView(QString* attr);
    void setBirdView(QString* attr);
    void setRabbitView(QString* attr);
    void setHamsterView(QString* attr);
    void setGuineaPigView(QString* attr);
    void on_saveButton_clicked();
    void on_resetButton_clicked();
    void on_cancelButton_clicked();
    void on_update_Button_clicked();

    void on_edit_Button_clicked();

signals:
    void animalEdited();
};

#endif // AddAnimalDialog_H
