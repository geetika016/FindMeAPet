#include "detailedAnimalDialog.h"
#include <QDebug>

DetailedAnimalDialog::DetailedAnimalDialog(int num, QString* attr, QWidget *parent, int edit) :
    QDialog(parent),
    attributesNum(num),
    attributes(attr),
    canEdit(edit)
{
    QWidget *details = new QWidget;
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(details);
    QGridLayout *mainLayout = new QGridLayout;
    details->setLayout(mainLayout);


    for(int i=0; i<attributesNum-1; i++)
    {
        QFrame *labelPair = new QFrame;
        labelPair->setLineWidth(1);
        labelPair->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        QLabel *attName = new QLabel;
        if(attributes[i*2].contains("afc"))
        {
            attributes[i*2] = attributes[i*2].remove("afc");
            attributes[i*2] = attributes[i*2]+" score by animal for client";
        }
        if(attributes[i*2].contains("cfa"))
        {
            attributes[i*2] = attributes[i*2].remove("cfa");
            attributes[i*2] = attributes[i*2]+" score by client for animal";
        }
        attName->setText(attributes[i*2]+":");
        QLineEdit *attVal = new  QLineEdit;
        attVal->setText(attributes[i*2+1]);
        if(canEdit == 1)
            attVal->setReadOnly(true);
        QHBoxLayout *labelPairLayout = new QHBoxLayout;//set up a pair of attribute name and value
        labelPairLayout->addWidget(attName);
        labelPairLayout->addWidget(attVal);
        labelPair->setLayout(labelPairLayout);
        mainLayout->addWidget(labelPair, i/3, i%3);//display 6 attributes per line
    }
    setLayout(mainLayout);
}
