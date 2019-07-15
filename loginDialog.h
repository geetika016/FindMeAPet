#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    void getLoginInfo(QString &usrnm, QString &psswd);
    void showMsg(QString msg);
    ~LoginDialog();

private slots:
    void on_loginButton_clicked();

signals:
    void loginInfo();

private:
    Ui::LoginDialog *ui;
    QString username;
    QString password;
};

#endif // LOGIN_H
