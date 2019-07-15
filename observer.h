#ifndef OBSERVER_H
#define OBSERVER_H

#include <QWidget>

class Subject;
class Observer : public QWidget
{
    Q_OBJECT

public:
    explicit Observer(QWidget *parent = nullptr);
    virtual ~Observer();
    virtual void update(Subject *subject) = 0;
};

#endif // OBSERVER_H
