#ifndef SUBJECT_H
#define SUBJECT_H

#include <QWidget>
#include <QList>
#include <QDialog>
#include "observer.h"

class Subject : public QDialog
{
    Q_OBJECT

public:
    explicit Subject(QWidget *parent = nullptr);
    virtual ~Subject();
    void subscribe(Observer *observer);
    void unsubscribe(Observer *observer);
    void notify();

private:
    QList<Observer *> observerList;
};

#endif // SUBJECT_H
