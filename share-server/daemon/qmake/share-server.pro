QT += dbus

SOURCES += ../daemon.cpp\
           ../ShareManager.cpp

HEADERS += ../ShareManager.h

DBUS_INTERFACES += ../share_target.xml
DBUS_ADAPTORS += ../share.xml

DESTDIR = ../../
target.path = ../../
INSTALLS += target
