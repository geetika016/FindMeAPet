#-------------------------------------------------
#
# Project created by QtCreator 2019-02-03T11:51:29
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += warn_off

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuACS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    staffMainWindow.cpp \
    overallControl.cpp \
    User.cpp \
    addAnimalDialog.cpp \
    addClientDialog.cpp \
    viewClientWidget.cpp \
    viewAnimalWidget.cpp \
    detailedAnimalDialog.cpp \
    staffDatabaseControl.cpp \
    databaseControl.cpp \
    queryControl.cpp \
    dataModel.cpp \
    dataModelControl.cpp \
    subject.cpp \
    observer.cpp \
    proxySubject.cpp \
    proxy.cpp \
    loginDialog.cpp \
    clientMainWindow.cpp \
    viewEditClientDialog.cpp \
    clientDatabaseControl.cpp \
    matchingControl.cpp \
    animal.cpp \
    client.cpp \
    score.cpp \
    viewMatchWidget.cpp

HEADERS += \
    overallControl.h \
    staffMainWindow.h \
    User.h \
    addAnimalDialog.h \
    addClientDialog.h \
    viewClientWidget.h \
    viewAnimalWidget.h \
    detailedAnimalDialog.h \
    staffDatabaseControl.h \
    databaseControl.h \
    queryControl.h \
    dataModel.h \
    dataModelControl.h \
    subject.h \
    observer.h \
    proxySubject.h \
    proxy.h \
    loginDialog.h \
    clientMainWindow.h \
    viewEditClientDialog.h \
    clientDatabaseControl.h \
    matchingControl.h \
    animal.h \
    client.h \
    score.h \
    viewMatchWidget.h

FORMS += \
    staffMainWindow.ui \
    addAnimalDialog.ui \
    addClientDialog.ui \
    viewClientWidget.ui \
    viewAnimalWidget.ui \
    loginDialog.ui \
    clientMainWindow.ui \
    viewEditClientDialog.ui \
    viewMatchWidget.ui

RESOURCES += \
    resources.qrc
