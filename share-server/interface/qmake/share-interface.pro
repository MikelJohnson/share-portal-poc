QT += qml quick

SOURCES += ../interface.cpp\
           ../AppInfo.cpp\
           ../InterfaceManager.cpp

HEADERS += ../AppInfo.h\
           ../InterfaceManager.h

DESTDIR = ../../
target.path = ../../
INSTALLS += target
