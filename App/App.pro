QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cardform.cpp \
    cardview.cpp \
    cardwindow.cpp \
    human.cpp \
    main.cpp \
    neuro.cpp \
    org.cpp \
    recognize.cpp \
    startwindow.cpp \
    visitki.cpp

HEADERS += \
    cardform.h \
    cardview.h \
    cardwindow.h \
    human.h \
    neuro.h \
    org.h \
    recognize.h \
    startwindow.h \
    visitki.h

FORMS += \
    cardform.ui \
    cardview.ui \
    cardwindow.ui \
    human.ui \
    org.ui \
    recognize.ui \
    startwindow.ui \
    visitki.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Design
