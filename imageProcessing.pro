QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bmp.cpp \
    gaussiansmoothing.cpp \
    getpixelgdialog.cpp \
    imageinterpolation.cpp \
    impulsenoise.cpp \
    main.cpp \
    mainwindow.cpp \
    medianfiltering.cpp \
    processing.cpp \
    setpiexeldialog2.cpp \
    setpixeldialog.cpp \
    sharpening.cpp

HEADERS += \
    bmp.h \
    gaussiansmoothing.h \
    getpixelgdialog.h \
    imageinterpolation.h \
    impulsenoise.h \
    mainwindow.h \
    medianfiltering.h \
    processing.h \
    setpiexeldialog2.h \
    setpixeldialog.h \
    sharpening.h

FORMS += \
    gaussiansmoothing.ui \
    getpixelgdialog.ui \
    imageinterpolation.ui \
    impulsenoise.ui \
    mainwindow.ui \
    medianfiltering.ui \
    setpiexeldialog2.ui \
    setpixeldialog.ui \
    sharpening.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    My_resource.qrc

RC_ICONS = 1.ico
