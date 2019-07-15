#ifndef PROXYSUBJECT_H
#define PROXYSUBJECT_H

#include <QMainWindow>

class ProxySubject : public QMainWindow
{
    Q_OBJECT
public:
    explicit ProxySubject(QWidget *parent = nullptr);
    ~ProxySubject();
    virtual void displayRequest() = 0;
};

#endif // PROXYSUBJECT_H
