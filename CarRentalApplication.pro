QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountsadminwindow.cpp \
    admin.cpp \
    admindashboard.cpp \
    category.cpp \
    categoryadminwindow.cpp \
    client.cpp \
    clientdashboard.cpp \
    clientrentalhistory.cpp \
    item.cpp \
    itemadminwindow.cpp \
    main.cpp \
    loginwindow.cpp \
    registerwindow.cpp \
    rentalrequest.cpp \
    rentalrequestsadminwindow.cpp \
    user.cpp

HEADERS += \
    accountsadminwindow.h \
    admin.h \
    admindashboard.h \
    category.h \
    categoryadminwindow.h \
    client.h \
    clientdashboard.h \
    clientrentalhistory.h \
    item.h \
    itemadminwindow.h \
    loginwindow.h \
    registerwindow.h \
    rentalrequest.h \
    rentalrequestsadminwindow.h \
    user.h

FORMS += \
    accountsadminwindow.ui \
    admindashboard.ui \
    categoryadminwindow.ui \
    clientdashboard.ui \
    clientrentalhistory.ui \
    itemadminwindow.ui \
    loginwindow.ui \
    registerwindow.ui \
    rentalrequestsadminwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
