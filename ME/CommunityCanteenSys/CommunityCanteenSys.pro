QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Windows\Admin_Paper\adminwin.cpp \
    carouselchart.cpp \
    Windows\Login_Paper\loginwin.cpp \
    Windows\Control_Pager\controlwin.cpp \
    main.cpp \
    Windows\Login_Paper\registerwin.cpp \
    Tools/tool_00_environment.cpp

HEADERS += \
    Windows\Admin_Paper\adminwin.h \
    carouselchart.h \
    Windows\Login_Paper\loginwin.h \
    Windows\Login_Paper\registerwin.h \
    Tools/tool_00_environment.h \
    Windows\Control_Pager\controlwin.h

FORMS += \
    Windows\Login_Paper\loginwin.ui \
    Windows\Login_Paper\registerwin.ui \
    Windows\Control_Pager\controlwin.ui \
    Windows\Admin_Paper\adminwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = _logo.ico
