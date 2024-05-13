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
    Tools/BuyNumBar/buynumbar.cpp \
    Tools/DishIconLabel/dishiconlabel.cpp \
    Tools/DishInfoBar/dishinfobar.cpp \
    Tools/DishShowBar/dishshowbar.cpp \
    Tools/DishShowManager/dishshowmanager.cpp \
    Tools/DishTurnPageBar/dishturnpagebar.cpp \
    Tools/MenuAlgorithm/menualgorithm.cpp \
    Tools/OrderDetailTools/DetailBar/detailbar.cpp \
    Tools/OrderDetailTools/OderDetailBar/oderdetailbar.cpp \
    Tools/OrderDetailTools/OrderDishShowBar/orderdishshowbar.cpp \
    Tools/UserIconLabel/usericonlabel.cpp \
    Windows/BuyCar_Pager/buycarwin.cpp \
    Windows/OrderDetail_Pager/orderdetailwin.cpp \
    Windows\Admin_Paper\adminwin.cpp \
    Windows\Control_Pager\carouselchart.cpp \
    Windows\Login_Paper\loginwin.cpp \
    Windows\Control_Pager\controlwin.cpp \
    main.cpp \
    Windows\Login_Paper\registerwin.cpp \
    Tools/tool_00_environment.cpp

HEADERS += \
    Tools/BuyNumBar/buynumbar.h \
    Tools/DishIconLabel/dishiconlabel.h \
    Tools/DishInfoBar/dishinfobar.h \
    Tools/DishShowBar/dishshowbar.h \
    Tools/DishShowManager/dishshowmanager.h \
    Tools/DishTurnPageBar/dishturnpagebar.h \
    Tools/MenuAlgorithm/menualgorithm.h \
    Tools/OrderDetailTools/DetailBar/detailbar.h \
    Tools/OrderDetailTools/OderDetailBar/oderdetailbar.h \
    Tools/OrderDetailTools/OrderDishShowBar/orderdishshowbar.h \
    Tools/UserIconLabel/usericonlabel.h \
    Windows/BuyCar_Pager/buycarwin.h \
    Windows/OrderDetail_Pager/orderdetailwin.h \
    Windows\Admin_Paper\adminwin.h \
    Windows\Control_Pager\carouselchart.h \
    Windows\Login_Paper\loginwin.h \
    Windows\Login_Paper\registerwin.h \
    Tools/tool_00_environment.h \
    Windows\Control_Pager\controlwin.h

FORMS += \
    Tools/BuyNumBar/buynumbar.ui \
    Tools/DishInfoBar/dishinfobar.ui \
    Tools/DishShowBar/dishshowbar.ui \
    Tools/DishTurnPageBar/dishturnpagebar.ui \
    Tools/OrderDetailTools/DetailBar/detailbar.ui \
    Tools/OrderDetailTools/OderDetailBar/oderdetailbar.ui \
    Tools/OrderDetailTools/OrderDishShowBar/orderdishshowbar.ui \
    Windows/BuyCar_Pager/buycarwin.ui \
    Windows/OrderDetail_Pager/orderdetailwin.ui \
    Windows\Login_Paper\loginwin.ui \
    Windows\Login_Paper\registerwin.ui \
    Windows\Control_Pager\controlwin.ui \
    Windows\Admin_Paper\adminwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = logo.ico

RESOURCES +=
