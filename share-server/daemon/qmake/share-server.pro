QT += dbus

SOURCES += ../daemon.cpp\
           ../ShareManager.cpp

HEADERS += ../ShareManager.h

DBUS_ADAPTORS += ../share.xml

DESTDIR = ../../
target.path = ../../
INSTALLS += target
