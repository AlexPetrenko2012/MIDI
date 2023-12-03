QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += ../CMidi/src/

SOURCES += \
    ../CMidi/src/CMidiFile.cpp \
    ../CMidi/src/CMidiIn.cpp \
    ../CMidi/src/CMidiOut.cpp \
    cmidimessager.cpp \
    main.cpp


HEADERS += \
    ../CMidi/src/CMidiFile.h \
    ../CMidi/src/CMidiIn.h \
    ../CMidi/src/CMidiOut.h \
    cmidimessager.h


linux* {
        LIBS += -lasound
        SOURCES += ../CMidi/src/OS/CMidi_ALSA.cpp
        HEADERS += ../CMidi/src/OS/CMidi_ALSA.h
}

win32 {
        LIBS += -lwinmm
        SOURCES += ../CMidi/src/OS/CMidi_Win32.cpp
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
