#include "loginDialog.h"
#include "ui_loginDialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    username = "";
    password = "";
    QPixmap pixmap(":Images/mainBackground");
    ui->image_label->setPixmap(pixmap);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::getLoginInfo(QString &usrnm, QString &psswd)
{
    usrnm = username;
    psswd = password;
}

void LoginDialog::showMsg(QString msg)
{
    QMessageBox::critical(this, tr("Login failed"), msg);
}

void LoginDialog::on_loginButton_clicked()
{
   username = ui->username->text();
   password = ui->password->text();
   if(username.isEmpty() || password.isEmpty())
   {
       ui->username->clear();
       ui->password->clear();
       QMessageBox::critical(this, tr("Login failed"), tr("Please fill in your username and password"));
   }
   else
   {
       emit loginInfo();
       this->close();
   }
}
