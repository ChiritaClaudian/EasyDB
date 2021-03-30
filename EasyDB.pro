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
    admin.cpp \
    baseuser.cpp \
    createtabelui.cpp \
    credential.cpp \
    cryptmanager.cpp \
    databasemanager.cpp \
    ilogicalsqlobject.cpp \
    insertqueryui.cpp \
    iuser.cpp \
    iuseruilogic.cpp \
    joinui.cpp \
    logicalcolumn.cpp \
    logicalsqlobject.cpp \
    logicalsqlobjectdao.cpp \
    logicaltable.cpp \
    loginui.cpp \
    main.cpp \
    mainwindow.cpp \
    permission.cpp \
    permissiondao.cpp \
    queryresultui.cpp \
    registrationui.cpp \
    selectqueryui.cpp \
    simplecrypt.cpp \
    user.cpp \
    userdao.cpp \
    useruilogic.cpp \
    wizardqueryui.cpp

HEADERS += \
    admin.h \
    baseuser.h \
    createtabelui.h \
    credential.h \
    cryptmanager.h \
    databasemanager.h \
    ilogicalsqlobject.h \
    insertqueryui.h \
    iuser.h \
    iuseruilogic.h \
    joinui.h \
    logicalcolumn.h \
    logicalsqlobject.h \
    logicalsqlobjectdao.h \
    logicaltable.h \
    loginui.h \
    mainwindow.h \
    permission.h \
    permissiondao.h \
    queryresultui.h \
    registrationui.h \
    selectqueryui.h \
    simplecrypt.h \
    user.h \
    userdao.h \
    useruilogic.h \
    wizardqueryui.h

FORMS += \
    BaseUserUI.ui \
    createtabelui.ui \
    insertqueryui.ui \
    joinui.ui \
    loginui.ui \
    mainwindow.ui \
    queryresultui.ui \
    registrationui.ui \
    selectqueryui.ui \
    wizardqueryui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    fakeDataBase.db
