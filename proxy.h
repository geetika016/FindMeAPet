#ifndef PROXY_H
#define PROXY_H

#include <QHash>
#include "proxySubject.h"
#include "staffMainWindow.h"
#include "clientMainWindow.h"
#include "loginDialog.h"
#include "databaseControl.h"

class StaffMainWindow;

class Proxy : public ProxySubject
{
    Q_OBJECT

private:
    StaffMainWindow *staffRealSubject;
    ClientMainWindow *clientRealSubject;
    LoginDialog *loginDialog;
    QString username;
    QString password;
    DatabaseControl *dbControl;
    Authentication authentication;
    void displayRequestHelper();

public:
    explicit Proxy(QWidget *parent = nullptr);
    ~Proxy();
    virtual void displayRequest();

private slots:
    void getLoginInfo();
};

#endif // PROXY_H
