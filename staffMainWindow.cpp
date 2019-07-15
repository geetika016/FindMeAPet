#include "staffMainWindow.h"
#include "ui_staffMainWindow.h"
#include "addAnimalDialog.h"

StaffMainWindow::StaffMainWindow(QWidget *parent) :
    ProxySubject(parent),
    ui(new Ui::StaffMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Staff");
    //animalTableIsShowing = NULL;
    //clientTableIsShowing = NULL;
    subjectAddClient = NULL;
    observerViewClient = NULL;
    subjectAddAnimal = NULL;
    observerViewAnimal = NULL;
    matchingControl = NULL;
    QRect rect = this->geometry();
    rect.moveCenter(QApplication::desktop()->availableGeometry().center());
    this->setGeometry(rect);

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(tabClosed(int)));
}

StaffMainWindow::~StaffMainWindow()
{
    delete ui;
    if (!viewAnimalWidget)
        delete viewAnimalWidget;
    if (!matchingControl)
        delete matchingControl;
}

void StaffMainWindow::displayRequest()
{
   this->show();
}

void StaffMainWindow::on_actionView_Animals_triggered()
{
    viewAnimalWidget = new ViewAnimalWidget();
    observerViewAnimal = viewAnimalWidget;
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

void StaffMainWindow::on_actionAdd_Animals_triggered()
{
    addAnimalDialog = new AddAnimalDialog;
    subjectAddAnimal = addAnimalDialog;
    setSubscription(subjectAddAnimal, observerViewAnimal);
    //connect the signal and slot, is legal when addAnimalDialog is not null
    //connect(addAnimalDialog, &AddAnimalDialog::newAnimalAdded,
    //        this, &StaffMainWindow::updateAnimalViewTable);
    addAnimalDialog->setModal(true);//dialog will pop up as modal
    addAnimalDialog->exec();

    subjectAddAnimal = NULL;
}

void StaffMainWindow::on_actionView_Clients_triggered()
{
    viewClientWidget = new ViewClientWidget(this, 0);
    observerViewClient = viewClientWidget;
    int tabIndex = -1;

    for(int i=0; i<ui->tabWidget->count(); i++)
    {
        if (ui->tabWidget->tabText(i) == "Clients Table")
        {
            tabIndex = i;
            break;
        }
    }

    //prevent table from showing up mutiple times
    if (tabIndex >= 0)
    {
        ui->tabWidget->removeTab(tabIndex);
        ui->tabWidget->insertTab(tabIndex, viewClientWidget, QString("Clients Table"));
        ui->tabWidget->setCurrentIndex(tabIndex);
    }
    else
    {
        int index = ui->tabWidget->addTab(viewClientWidget, QString("Clients Table"));
        ui->tabWidget->setCurrentIndex(index);
    }

    //set up a flag for signal handler, which means table view has already been triggered by user
    clientTableIsShowing = viewClientWidget;
    viewClientWidget->show();
}

void StaffMainWindow::on_actionAdd_Clients_triggered()
{
    addClientDialog = new AddClientDialog;
    subjectAddClient = addClientDialog;
    setSubscription(subjectAddClient, observerViewClient);

    //connect the signal and slot, is legal when addAnimalDialog is not null
    //connect(addClientDialog, &AddClientDialog::newClientAdded,
      //      this, &StaffMainWindow::updateClientViewTable);
    addClientDialog->setModal(true);//dialog will pop up as modal
    addClientDialog->exec();
    subjectAddClient = NULL;
}

void StaffMainWindow::tabClosed(int index)
{
    if (ui->tabWidget->tabText(index) == "Clients Table")
    {
        if (subjectAddClient != NULL)
            subjectAddClient->unsubscribe(observerViewClient);
        observerViewClient = NULL;
    }
    if (ui->tabWidget->tabText(index) == "Animals Table")
    {
        if (subjectAddAnimal != NULL)
        subjectAddAnimal->unsubscribe(observerViewAnimal);
        observerViewAnimal = NULL;
    }

    ui->tabWidget->removeTab(index);
}

//void StaffMainWindow::updateAnimalViewTable()
//{
//    //make sure the table is on display before re-trigger the viewAnimal slot
//    if (animalTableIsShowing)
//        on_actionView_Animals_triggered();
//}

//void StaffMainWindow::updateClientViewTable()
//{
    //make sure the table is on display before re-trigger the viewClient slot
  //  if (clientTableIsShowing)
    //    on_actionView_Clients_triggered();
//}

void StaffMainWindow::setSubscription(Subject *subjectAddObj, Observer *observerViewObj)
{
    if (observerViewObj == NULL)
    {
        //qDebug() << "No need to update viewing object since it's not there yet.";
        return;
    }
    subjectAddObj->subscribe(observerViewObj);
}


void StaffMainWindow::on_actionLaunch_triggered()
{
//    matchingControl = new MatchingControl;
//    bool gotMatching = matchingControl->start();
//    viewLauchACM = new ViewLaunchACM;
//    bool matchesDone = viewLauchACM->getGotMatchingValue();
//    viewLauchACM->show();//dialog will pop up as modal
//    if(matchesDone)
//    {
//        lauchACMtriggered = 1;

//    }
    matchingControl = new MatchingControl;
    bool gotMatching = matchingControl->start();
    if(gotMatching)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, "Success", "ACM Computed Matches successfully!");
        gotMatches = gotMatching;
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, "Error!!", "ACM Failed!!");
    }

}

void StaffMainWindow::on_actionMatch_Results_triggered()
{
    if(!(gotMatches))
    {
        QMessageBox::StandardButton reply;
          reply = QMessageBox::information(this, "Error!!", "Please Launch ACM Atleast Once!");
    }

    else
    {
    viewMatchWidget = new ViewMatchWidget;
    int tabIndex = -1;

    for(int i=0; i<ui->tabWidget->count(); i++)
    {
        if (ui->tabWidget->tabText(i) == "Results Table")
        {
            tabIndex = i;
            break;
        }
    }

    //prevent table from showing up mutiple times
    if (tabIndex >= 0)
    {
        ui->tabWidget->removeTab(tabIndex);
        ui->tabWidget->insertTab(tabIndex, viewMatchWidget, QString("Results Table"));
        ui->tabWidget->setCurrentIndex(tabIndex);
    }
    else
    {
        int index = ui->tabWidget->addTab(viewMatchWidget, QString("Results Table"));
        ui->tabWidget->setCurrentIndex(index);
    }

    //set up a flag for signal handler, which means table view has already been triggered by user
    matchTableIsShowing = viewMatchWidget;
    viewMatchWidget->show();
    }
}
