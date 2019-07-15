#ifndef ANIMALDETAILDIALOG_H
#define ANIMALDETAILDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QScrollArea>

/*
  Class: DetailedAnimalDialog
  Purpose: displays a dialog for detailed information of an animal

  Member function: constructor
  Purpose: configure the layout in the dialog

  Member function: buildDataModel
  Purpose: intializes and polulates the model

  Member function: configure()
  Purpose: set up the QTableView object

*/

class DetailedAnimalDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DetailedAnimalDialog(int num, QString* attr, QWidget *parent = nullptr, int edit=0);

private:
    int attributesNum;
    QString* attributes;
    int canEdit;

signals:

public slots:
};

#endif // ANIMALDETAILDIALOG_H
