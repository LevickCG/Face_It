QT       += core gui sql multimedia multimediawidgets

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
    admin_win.cpp \
    camera.cpp \
    face_renew.cpp \
    global_var.cpp \
    main.cpp \
    mainwindow.cpp \
    psw_modf.cpp \
    reg.cpp \
    sql_log.cpp \
    user_delete.cpp \
    user_win.cpp

HEADERS += \
    admin_win.h \
    camera.h \
    face_renew.h \
    global_var.h \
    mainwindow.h \
    psw_modf.h \
    reg.h \
    sql_log.h \
    user_delete.h \
    user_win.h

FORMS += \
    admin_win.ui \
    camera.ui \
    face_renew.ui \
    mainwindow.ui \
    psw_modf.ui \
    reg.ui \
    sql_log.ui \
    user_delete.ui \
    user_win.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

