#include <QApplication>
#include "overallControl.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OverAllControl control;

    control.launch();

    return a.exec();
}
