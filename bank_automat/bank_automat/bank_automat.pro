QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    src/checker.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pinscreen.cpp

HEADERS += \
    src/checker.h \
    src/mainwindow.h \
    src/pinscreen.h

FORMS += \
    src/mainwindow.ui \
    src/pinscreen.ui

RESOURCES += src/resources.qrc

TRANSLATIONS += src/translations/translations_en.ts \
                src/translations/translations_fi.ts \
                src/translations/translations_sv.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target