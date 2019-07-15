#include "addClientDialog.h"
#include "ui_addClientDialog.h"

AddClientDialog::AddClientDialog(QWidget *parent) :
    Subject(parent),
    ui(new Ui::AddClientDialog)
{
    ui->setupUi(this);
    dbControl = new StaffDatabaseControl;
}

AddClientDialog::~AddClientDialog()
{
    delete ui;
    delete dbControl;
}

void AddClientDialog::clearFields()
{
    this->ui->lineEdit_name->clear();
    this->ui->lineEdit_phoneNumber->clear();
    this->ui->lineEdit_email->clear();
    this->ui->lineEdit_password->clear();
}

void AddClientDialog::checkMandatoryFields()
{
    if(ui->lineEdit_name->text().isEmpty()) {
        //qDebug() << "Empty name";
        QMessageBox::critical(this,tr(""),tr("Please fill in your name"));
    }
    if(ui->lineEdit_phoneNumber->text().isEmpty()) {
        //qDebug() << "Empty phone number";
        QMessageBox::critical(this,tr(""),tr("Please fill in your phone number"));
    }
    if(ui->lineEdit_email->text().isEmpty()) {
        //qDebug() << "Empty email";
        QMessageBox::critical(this,tr(""),tr("Please fill in your email"));
    }
    if(ui->lineEdit_password->text().isEmpty()) {
        //qDebug() << "Empty password";
        QMessageBox::critical(this,tr(""),tr("Please fill in your password"));
    }
}

void AddClientDialog::on_saveButton_clicked()
{
    checkMandatoryFields();

    QHash<QString, QString> input;
    input[QString("name")] = ui->lineEdit_name->text();
    input[QString("phone_number")] = ui->lineEdit_phoneNumber->text();
    input[QString("email")] = ui->lineEdit_email->text();

    QHash<QString, QString> userInput;
    userInput[QString("username")] = ui->lineEdit_name->text();
    userInput[QString("password")] = ui->lineEdit_password->text();
    userInput[QString("role")] = "client";

    QString errMsg;

    if(dbControl->dbRequest(&input, NULL, ADD_CLIENT, &errMsg))
    {
        QMessageBox::information(this,tr("Save"),tr("Saved"));
        this->close();
        //emit newClientAdded();//send a signal to staffMainWindow object
        if (dbControl->dbRequest(&userInput, NULL, ADD_USER, &errMsg))
        {
            QMessageBox::information(this,tr("Save"),tr("Saved"));
            this->close();
            //emit newClientAdded();//send a signal to staffMainWindow object

             notify();
        }
        else
        {
            QMessageBox::critical(this, tr("Error! user err"), errMsg);
            this->clearFields();
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error! client err"), errMsg);
        this->clearFields();
    }
}

void AddClientDialog::on_resetButton_clicked()
{
    this->clearFields();
}

void AddClientDialog::on_cancelButton_clicked()
{
    this->close();
}
