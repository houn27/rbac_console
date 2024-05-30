QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    delrowwindow.cpp \
    editperwindow.cpp \
    editrolewindow.cpp \
    edituserwindow.cpp \
    main.cpp \
    newconnectwindow.cpp \
    selectrowwindow.cpp \
    widget.cpp

HEADERS += \
    delrowwindow.h \
    editperwindow.h \
    editrolewindow.h \
    edituserwindow.h \
    newconnectwindow.h \
    selectrowwindow.h \
    widget.h

FORMS += \
    delrowwindow.ui \
    editperwindow.ui \
    editrolewindow.ui \
    edituserwindow.ui \
    newconnectwindow.ui \
    selectrowwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
