#include "clientMainWindow.h"
#include "ui_clientMainWindow.h"

ClientMainWindow::ClientMainWindow(QString name, QWidget *parent) :
    ProxySubject(parent),
    username(name),
    ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Client");
    //animalTableIsShowing = NULL;
    QRect rect = this->geometry();
    rect.moveCenter(QApplication::desktop()->availableGeometry().center());
    this->setGeometry(rect);

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(tabClosed(int)));
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
    if (!viewAnimalWidget)
        delete viewAnimalWidget;
}

void ClientMainWindow::displayRequest()
{
   this->show();
}

void ClientMainWindow::on_actionView_Animals_triggered()
{
    viewAnimalWidget = new ViewAnimalWidget(this,1);
    //emit viewAnimalsOnly();
    int tabIndex = -1;

    for(int i=0; i<ui->tabWidget->count(); i++)
    {
        if (ui->tabWidget->tabText(i) == "Animals Table")
        {
            tabIndex = i;
            break;
        }
    }

    //prevent table from showing up mutiple times
    if (tabIndex >= 0)
    {
        ui->tabWidget->removeTab(tabIndex);
        ui->tabWidget->insertTab(tabIndex, viewAnimalWidget, QString("Animals Table"));
        ui->tabWidget->setCurrentIndex(tabIndex);
    }
    else
    {
        int index = ui->tabWidget->addTab(viewAnimalWidget, QString("Animals Table"));
        ui->tabWidget->setCurrentIndex(index);
    }

    //set up a flag for signal handler, which means table view has already been triggered by user
    //animalTableIsShowing = viewAnimalWidget;
    viewAnimalWidget->show();
}


void ClientMainWindow::on_actionEdit_Profile_triggered()
{
    viewEditClientDialog = new ViewEditClientDialog(username);

    viewEditClientDialog->setModal(true);//dialog will pop up as modal
    viewEditClientDialog->exec();
}

void ClientMainWindow::tabClosed(int index)
{
    ui->tabWidget->removeTab(index);
}




void ClientMainWindow::on_logout_Button_clicked()
{
    this->destroy();
    //add code to load login dialog
}
