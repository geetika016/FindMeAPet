#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QStackedLayout>
#include <QDesktopWidget>
#include "viewAnimalWidget.h"
#include "viewEditClientDialog.h"
#include "proxySubject.h"
#include "loginDialog.h"
//#include "proxy.h"

class ViewEditClientDialog;

namespace Ui {
class ClientMainWindow;
}

class ClientMainWindow : public ProxySubject
{
    Q_OBJECT

public:
    explicit ClientMainWindow(QString name, QWidget *parent = 0);
    ~ClientMainWindow();
    virtual void displayRequest();

private slots:
    void on_actionView_Animals_triggered();
    void on_actionEdit_Profile_triggered();
    void tabClosed(int index);

//signals:
//    void viewAnimalsOnly();

    void on_logout_Button_clicked();

private:
    Ui::ClientMainWindow *ui;
    QString username;
    ViewAnimalWidget *viewAnimalWidget;
    ViewEditClientDialog *viewEditClientDialog;
    LoginDialog *loginDialogWidget;
    //Proxy *proxy;
};

#endif // CLIENTMAINWINDOW_H
