#include "proxy.h"

Proxy::Proxy(QWidget *parent) : ProxySubject(parent)
{
    loginDialog = new LoginDialog;
    dbControl = new DatabaseControl;
    staffRealSubject = NULL;
    username = "";
    password = "";
    connect(loginDialog, SIGNAL(loginInfo()),
            this, SLOT(getLoginInfo()));
}

Proxy::~Proxy()
{
    delete loginDialog;
    delete dbControl;
    if (staffRealSubject != NULL)
        delete staffRealSubject;
}

void Proxy::displayRequest()
{
    loginDialog->show();
}

void Proxy::getLoginInfo()
{
    loginDialog->getLoginInfo(username, password);
    displayRequestHelper();
}

void Proxy::displayRequestHelper()
{
    QHash<QString, QString> loginInfo;
    loginInfo[username] = password;
    QString errMsg;
    DBSettings settings;
    settings.table = "users";
    if (!dbControl->dbRequest(&loginInfo, (void *)&authentication, &settings, CHECK, &errMsg))
       loginDialog->showMsg(errMsg);
    else
    {
        if (authentication.accept)
        {
            if(authentication.role == "staff")
            {
                staffRealSubject = new StaffMainWindow;
                staffRealSubject->displayRequest();
            }
            if(authentication.role == "client")
            {
                clientRealSubject = new ClientMainWindow(authentication.username);
                clientRealSubject->displayRequest();
            }
        }
        else
            loginDialog->showMsg(authentication.msg);
    }
}
