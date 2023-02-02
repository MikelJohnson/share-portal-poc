QT += qml quick dbus
DBUS_ADAPTORS += ../share_target.xml
DBUS_INTERFACES += ../share.xml
HEADERS += ../ShareReceiver.h ../LockHandler.h\
           ../Contact.h
SOURCES += ../main.cpp\
           ../ShareReceiver.cpp ../LockHandler.cpp\
           ../Contact.cpp

DESTDIR = ../
target.path = ../
INSTALLS += target
