#include "viewClientWidget.h"

QString ViewClientWidget::summaryAttributes[CLIENT_SUMMARY_ATTRIBUTES_NUM] = {
    "name", "phone_number", "email", "details"
};

ViewClientWidget::ViewClientWidget(QWidget *parent, int user_type) : Observer(parent)
{
    ui.setupUi(this);
    model = new DataModel;
    dbControl = new StaffDatabaseControl;
    if (!dbControl->dbRequest(NULL, model, VIEW_CLIENT))
    {
        QMessageBox::critical(NULL, QObject::tr("Error!"),  QObject::tr("Unable to build dataModel"));
        return;
    }
    //set up the view object
    configure(ui.tableView_summary, summaryAttributes, CLIENT_SUMMARY_ATTRIBUTES_NUM);
    connect(ui.tableView_summary, SIGNAL(clicked(QModelIndex)),
             this, SLOT(clicked(QModelIndex)));
    this->user_type = user_type;
    //qDebug()<<user_type;
}


ViewClientWidget::~ViewClientWidget()
{
    delete(model);
    delete(dbControl);
}

void ViewClientWidget::configure(QTableView *tableView, QString *attributes, int attributesShown)
{
    //set up the View object
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setWindowTitle(QObject::tr("Clients Table"));
    tableView->setModel(model);
    tableView->setCurrentIndex(model->index(0, 0));
    for(int i=0; i<model->columnCount(); i++)
        tableView->hideColumn(i);
    for(int i=0; i<attributesShown; i++)
        tableView->setColumnHidden(model->fieldIndex(attributes[i]), false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->resizeColumnsToContents();
    //tableView->show();
}

void ViewClientWidget::clicked(const QModelIndex &modelIndex)
{
    //show animal details if user click on more
    if(model->data(modelIndex).toString() == "More")
        showClientDetail(modelIndex.row());
}


void ViewClientWidget::showClientDetail(int row)
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
    //qDebug()<<user_type;
    viewEditClientDialog = new ViewEditClientDialog(attributes[3], this, user_type);
    viewEditClientDialog->setModal(true);//dialog will pop up as modal
    viewEditClientDialog->exec();


}

void ViewClientWidget::update(Subject * subject)
{
    if (!dbControl->dbRequest(NULL, model, VIEW_CLIENT))
    {
        QMessageBox::critical(NULL, QObject::tr("Error!"),  QObject::tr("Unable to build dataModel"));
        return;
    }
    configure(ui.tableView_summary, summaryAttributes, CLIENT_SUMMARY_ATTRIBUTES_NUM);
}






