#ifndef CLIENTPROFILEVIEW_H
#define CLIENTPROFILEVIEW_H

#include <QDialog>
#include <QtDebug>
#include <QSlider>
#include <QMessageBox>
#include "clientDatabaseControl.h"

class ViewEditClientDialog;
class ClientDatabaseControl;

namespace Ui {
class ViewEditClientDialog;
}

class ViewEditClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewEditClientDialog(QString name, QWidget *parent = 0 ,int user_type =1);
    explicit ViewEditClientDialog(int row, int num, QString* attr, QWidget *parent=0, int animal_type=0, int user_type=1, bool readOnly = true);
    ~ViewEditClientDialog();
//signals:
    //void myProfile();

private slots:
    void on_saveButton_clicked();
    void setClientDogView(QHash<QString, QString> input);
    void setClientCatView(QHash<QString, QString> input);
    void setClientBirdView(QHash<QString, QString> input);
    void setClientRabbitView(QHash<QString, QString> input);
    void setClientHamsterView(QHash<QString, QString> input);
    void setClientGuineaPigView(QHash<QString, QString> input);
    void clientUpdateDog(QHash<QString, QString> &input);
    void clientUpdateCat(QHash<QString, QString> &input);
    void clientUpdateBird(QHash<QString, QString> &input);
    void clientUpdateRabbit(QHash<QString, QString> &input);
    void clientUpdateHamster(QHash<QString, QString> &input);
    void clientUpdateGuineaPig(QHash<QString, QString> &input);

private:
    Ui::ViewEditClientDialog *ui;
    QString username;
    QString animal_type;
    ClientDatabaseControl *dbControl;
    void fillInfo(QHash<QString, QString> input);
    void initialInfo(QHash<QString, QString> input);
    QString clientID;
    bool update = false;
    int rowNum;
    int user_type=1;

};

#endif // CLIENTPROFILEVIEW_H
