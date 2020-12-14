QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        astrocalculator.cpp \
        main.cpp \
        scheduleorganizer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    astrocalculator.h \
    scheduleorganizer.h
