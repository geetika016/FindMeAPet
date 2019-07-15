#include "animalDetailDialog.h"
#include <QDebug>

AnimalDetailDialog::AnimalDetailDialog(int num, QString* attr, QWidget *parent) :
    QDialog(parent),
    attributesNum(num),
    attributes(attr)
{
    QGridLayout *mainLayout = new QGridLayout;
    for(int i=0; i<attributesNum-1; i++)
    {
        QFrame *labelPair = new QFrame;
        labelPair->setLineWidth(1);
        labelPair->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        QLabel *attName = new QLabel;
        attName->setText(attributes[i*2]+":");
        QLabel *attVal = new QLabel;
        attVal->setText(attributes[i*2+1]);
        QHBoxLayout *labelPairLayout = new QHBoxLayout;//set up a pair of attribute name and value
        labelPairLayout->addWidget(attName);
        labelPairLayout->addWidget(attVal);
        labelPair->setLayout(labelPairLayout);
        mainLayout->addWidget(labelPair, i/4, i%4);//display 4 attributes per line
    }
    setLayout(mainLayout);
}
