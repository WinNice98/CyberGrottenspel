QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    finalwindow.cpp \
    information.cpp \
    load_game.cpp \
    main.cpp \
    mainwindow.cpp \
    new_game.cpp \
    save_game.cpp

HEADERS += \
    about.h \
    finalwindow.h \
    game.h \
    information.h \
    load_game.h \
    mainwindow.h \
    new_game.h \
    save_game.h

FORMS += \
    about.ui \
    finalwindow.ui \
    information.ui \
    load_game.ui \
    mainwindow.ui \
    new_game.ui \
    save_game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/media.qrc

DISTFILES +=
