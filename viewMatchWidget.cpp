#include "viewMatchWidget.h"
QString ViewMatchWidget::summaryAttributes[SUMMARY_ATTRIBUTES_NUM] = {
    "client_name", "animal_name", "details"
};


ViewMatchWidget::ViewMatchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewMatchWidget)
{
    ui->setupUi(this);
    model = new DataModel;
    dbControl = new StaffDatabaseControl;
    if (!dbControl->dbRequest(NULL, model, VIEW_MATCHES))
    {
        QMessageBox::critical(NULL, QObject::tr("Error!"),  QObject::tr("Unable to build dataModel"));
        return;
    }

    //set up the view object
    configure(ui->tableView_summary, summaryAttributes, SUMMARY_ATTRIBUTES_NUM);
    connect(ui->tableView_summary, SIGNAL(clicked(QModelIndex)),
            this, SLOT(clicked(QModelIndex)));
}

ViewMatchWidget::~ViewMatchWidget()
{
    delete(model);
    delete(dbControl);
}

void ViewMatchWidget::configure(QTableView *tableView, QString *attributes, int attributesShown)
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


void ViewMatchWidget::clicked(const QModelIndex &modelIndex)
{
    //show animal details if user click on more
    if(model->data(modelIndex).toString() == "More")
        showAnimalDetail(modelIndex.row(),1);
}

void ViewMatchWidget::showAnimalDetail(int row, int edit)
{
    int attributeNumOfType = 0;
    QString attributes[MAX_ATTRIBUTES_NUM_DOUBLE];
    QModelIndex modelIndexes[MAX_ATTRIBUTES_NUM];
    //get the model indexes for attributes
    for(int i=0; i<model->columnCount(); i++)
        modelIndexes[i] = model->index(row, i, QModelIndex());

    for(int i=0; i<model->columnCount(); i++)
    {
        /*add attributes names and values into an array of strings and pass it to
          the constructor of the dialog box showing the detailed information*/


            if(model->data(modelIndexes[i]).toString() != "" && model->data(modelIndexes[i]).toString() != "More" && model->data(modelIndexes[i]).toString() != "matching id")
            {
            attributes[attributeNumOfType*2] = model->headerData(i, Qt::Horizontal).toString();
            //qDebug()<<attributes[attributeNumOfType*2];
            attributes[attributeNumOfType*2+1] = model->data(modelIndexes[i]).toString();
            //qDebug()<<attributes[attributeNumOfType*2+1];
            ++attributeNumOfType;
            }
    }
    detailedAnimalDialog = new DetailedAnimalDialog(attributeNumOfType, attributes, this, edit);

    detailedAnimalDialog->show();
}
