#include "subject.h"

Subject::Subject(QWidget *parent) : QDialog(parent)
{
}

Subject::~Subject()
{
}

void Subject::subscribe(Observer *observer)
{
    observerList.append(observer);
}

void Subject::unsubscribe(Observer *observer)
{
        observerList.removeOne(observer);
}

void Subject::notify()
{
    if (!observerList.isEmpty())
    {
        foreach (Observer *observer, observerList)
            observer->update(this);
    }
}
