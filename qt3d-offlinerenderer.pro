android|ios|tvos|winrt {
    warning( "This example is not supported for android, ios, tvos, or winrt." )
}

QT += 3dcore 3drender 3dinput 3dextras
QT += widgets

SOURCES += main.cpp \
    scenemodifier.cpp \
    offscreenengine.cpp \
    offscreensurfaceframegraph.cpp \
    texturerendertarget.cpp \
    offscreenenginedelegate.cpp \
    mainwidget.cpp

HEADERS += \
    scenemodifier.h \
    offscreenengine.h \
    offscreensurfaceframegraph.h \
    texturerendertarget.h \
    offscreenenginedelegate.h \
    mainwidget.h


