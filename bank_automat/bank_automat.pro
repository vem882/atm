QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    checker.cpp \
    env.cpp \
    main.cpp \
    mainwindow.cpp \
    pinscreen.cpp \
    transactions.cpp

HEADERS += \
    checker.h \
    env.h \
    mainwindow.h \
    pinscreen.h \
    transactions.h

FORMS += \
    mainwindow.ui \
    pinscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources.qrc

TRANSLATIONS += translations/translations_en.ts \
                translations/translations_fi.ts \
                translations/translations_sv.ts
