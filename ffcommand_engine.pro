
#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T19:27:55
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FFCommand_Engine
TEMPLATE = app
RC_FILE = FFCommand_Engine.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        qfe_window.cpp \
    qjsonmodel.cpp \
    qfetablewidget.cpp \
    outputfileform.cpp \
    parsecommanddialog.cpp \
    presetsavedialog.cpp \
    ffprocessobj.cpp \
    processqueuedialog.cpp \
    ffmpegbinarydialog.cpp \
    aboutdialog.cpp

HEADERS += \
        qfe_window.h \
    qjsonmodel.h \
    qfetablewidget.h \
    outputfileform.h \
    ffmpegarg.h \
    parsecommanddialog.h \
    presetsavedialog.h \
    ffprocessobj.h \
    processqueuedialog.h \
    ffmpegbinarydialog.h \
    aboutdialog.h

FORMS += \
        qfe_window.ui \
    outputfileform.ui \
    parsecommanddialog.ui \
    presetsavedialog.ui \
    ffprocessobj.ui \
    processqueuedialog.ui \
    ffmpegbinarydialog.ui \
    aboutdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:DISTFILES +=  FFCommand_Engine.rc
ICON = FFCommand_Engine.icns
RESOURCES += \
    images.qrc

DISTFILES += \
    FFCommand_Engine.png
