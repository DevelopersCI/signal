QT += gui websockets core serialport widgets printsupport
requires(qtConfig(combobox))

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

INCLUDEPATH += $$PWD

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    screens/basculascreen.cpp \
    screens/printerscreen.cpp \
    screens/serverscreen.cpp \
    utils/server.cpp \
    utils/utils.cpp \
    utils/bascula.cpp \
    widgets/leftsidebar.cpp \
    widgets/pushbutton.cpp \
    window.cpp

HEADERS += \
    screens/basculascreen.h \
    screens/printerscreen.h \
    screens/serverscreen.h \
    utils/server.h \
    utils/utils.h \
    utils/bascula.h \
    widgets/leftsidebar.h \
    widgets/pushbutton.h \
    window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

RC_ICONS = app.ico

DISTFILES += \
    assets/bacula.svg \
    assets/bacula2.png


