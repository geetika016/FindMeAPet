#include "viewAnimalWidget.h"

QString ViewAnimalWidget::summaryAttributes[SUMMARY_ATTRIBUTES_NUM] = {
    "name", "type", "size", "breed", "gender", "age", "colour", "good_with_being_alone",
    "trainability", "energetic", "budget", "details"
};

ViewAnimalWidget::ViewAnimalWidget(QWidget *parent, int user_type) : Observer(parent)
{
    ui.setupUi(this);
    model = new DataModel;
    dbControl = new StaffDatabaseControl;
    if (!dbControl->dbRequest(NULL, model, VIEW_ANIMAL))
    {
        QMessageBox::critical(NULL, QObject::tr("Error!"),  QObject::tr("Unable to build dataModel"));
        return;
    }

    //set up the view object
    configure(ui.tableView_summary, summaryAttributes, SUMMARY_ATTRIBUTES_NUM);
    connect(ui.tableView_summary, SIGNAL(clicked(QModelIndex)),
            this, SLOT(clicked(QModelIndex)));
    this->user_type = user_type;
}

ViewAnimalWidget::~ViewAnimalWidget()
{
    delete(model);
    delete(dbControl);
}

void ViewAnimalWidget::configure(QTableView *tableView, QString *attributes, int attributesShown)
{
    //set up the View object
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setWindowTitle(QObject::tr("Animals Table"));
    tableView->setModel(model);
    tableView->setCurrentIndex(model->index(0, 0));
    for(int i=0; i<model->columnCount(); i++)
        tableView->hideColumn(i);
    for(int i=0; i<attributesShown; i++)
        tableView->setColumnHidden(model->fieldIndex(attributes[i]), false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->resizeColumnsToContents();
}

void ViewAnimalWidget::animalEdited()
{
    dbControl = new StaffDatabaseControl;
    if (!dbControl->dbRequest(NULL, model, VIEW_ANIMAL))
    {
        QMessageBox::critical(NULL, QObject::tr("Error!"),  QObject::tr("Unable to build dataModel"));
        return;
    }

    //set up the view object
    configure(ui.tableView_summary, summaryAttributes, SUMMARY_ATTRIBUTES_NUM);
    connect(ui.tableView_summary, SIGNAL(clicked(QModelIndex)),
            this, SLOT(clicked(QModelIndex)));
}

void ViewAnimalWidget::clicked(const QModelIndex &modelIndex)
{
    //show animal details if user click on more
    if(model->data(modelIndex).toString() == "More")
        showAnimalDetail(modelIndex.row());
}

void ViewAnimalWidget::showAnimalDetail(int row)
{

    int attributeNumOfType = 0;
    int animal_type = 0;
    QString attributes[MAX_ATTRIBUTES_NUM_DOUBLE];
    QModelIndex modelIndexes[MAX_ATTRIBUTES_NUM];
    //get the model indexes for attributes
    for(int i=0; i<model->columnCount(); i++)
        modelIndexes[i] = model->index(row, i, QModelIndex());

    for(int i=0; i<model->columnCount(); i++)
    {
        /*add attributes names and values into an array of strings and pass it to
          the constructor of the dialog box showing the detailed information*/
        if((model->data(modelIndexes[i]).toString()) != "N/A")
        {
            attributes[attributeNumOfType*2] = model->headerData(i, Qt::Horizontal).toString();
            //qDebug()<< attributes[attributeNumOfType*2];
            attributes[attributeNumOfType*2+1] = model->data(modelIndexes[i]).toString();
            //qDebug()<< attributes[attributeNumOfType*2+1];
            ++attributeNumOfType;
        }
    }

    if(attributes[5] == "Dog")
        animal_type = 1;
    else if(attributes[5] == "Cat")
        animal_type = 2;
    else if(attributes[5] == "Bird")
        animal_type = 3;
    else if(attributes[5] == "Rabbit")
        animal_type = 4;
    else if(attributes[5] == "Hamster")
        animal_type = 5;
    else if(attributes[5] == "Guinea Pig")
        animal_type = 6;


    //detailedAnimalDialog = new DetailedAnimalDialog(attributeNumOfType, attributes, this, 0);
    addAnimalDialog = new AddAnimalDialog(row, attributeNumOfType, attributes, this, animal_type, user_type, true);
    connect(addAnimalDialog, SIGNAL(animalEdited()), this, SLOT(animalEdited()));
    addAnimalDialog->setModal(true);//dialog will pop up as modal
    addAnimalDialog->exec();
}

void ViewAnimalWidget::update(Subject * subject)
{
    if (!dbControl->dbRequest(NULL, model, VIEW_ANIMAL))
    {
        QMessageBox::critical(NULL, QObject::tr("Error!"),  QObject::tr("Unable to build dataModel"));
        return;
    }
    configure(ui.tableView_summary, summaryAttributes, SUMMARY_ATTRIBUTES_NUM);
}

