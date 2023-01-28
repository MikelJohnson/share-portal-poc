QT += qml quick dbus

SOURCES += ../main.cpp\
           ../ShareSender.cpp

HEADERS += ../ShareSender.h

DBUS_INTERFACES += ../share.xml

CONFIG += c++17

DESTDIR = ../
target.path = ../
INSTALLS += target
