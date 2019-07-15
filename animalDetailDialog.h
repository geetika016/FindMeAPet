#ifndef ANIMALDETAILDIALOG_H
#define ANIMALDETAILDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <QFrame>

/*
  Class: AnimalDetailDialog
  Purpose: displays a dialog for detailed information of an animal

  Member function: constructor
  Purpose: configure the layout in the dialog

  Member function: buildDataModel
  Purpose: intializes and polulates the model

  Member function: configure()
  Purpose: set up the QTableView object

*/

class AnimalDetailDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AnimalDetailDialog(int num, QString* attr, QWidget *parent = nullptr);

private:
    int attributesNum;
    QString* attributes;

signals:

public slots:
};

#endif // ANIMALDETAILDIALOG_H
