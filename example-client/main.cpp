//
//     Copyright (C) 2023 Mikel Johnson <mikel5764@gmail.com> 
//
//     This program is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Lesser General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.
// 
//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Lesser General Public License for more details.
// 
//     You should have received a copy of the GNU Lesser General Public
//     License along with this library. If not, see <http://www.gnu.org/licenses/>.
//

#include <QtQuick/qquickview.h>
#include <QQmlApplicationEngine> 
#include <QGuiApplication>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <QtQuick/qquickitem.h>
#include <qqml.h>
#include <QtDBus>
#include <QStandardPaths>
#include <QFileInfo>
#include "ShareReceiver.h"
#include "Contact.h"
#include "LockHandler.h"

QString loadConfig() {
    QString config_location = QStringLiteral("./Contacts.json");

    QFile loadFile(config_location);

    if (!loadFile.open(QIODevice::ReadWrite)) {
        return QString();
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    return QJsonDocument(loadDoc.object()["contacts"].toArray()).toJson();
}

QList<QString> userInfo() {
    QList<QString> info;
    QString config_location = QStringLiteral("./Contacts.json");

    QFile loadFile(config_location);

    if (!loadFile.open(QIODevice::ReadWrite)) {
        return info;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    info.push_back(loadDoc.object()["profile"].toObject()["name"].toString());
    info.push_back(loadDoc.object()["profile"].toObject()["image"].toString());
    return info;
}

bool alreadyLaunched() { return QFileInfo::exists("./lock"); }

void writeToLockLog(QStringList args) {
    QFile file("./lock_log");
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }
    QTextStream out(&file);
    for (QString arg : args) {
        out << arg << " ";
    }
}

int main(int argc, char *argv[])
{
    qDBusRegisterMetaType<QList<QVariantMap>>();
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine view;
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    QStringList args;

    for (int i = 1; i < argc; i++) {
        args.push_back(QString(argv[i]));
    }

    if (alreadyLaunched()) {
        writeToLockLog(args);
        return 0;
    }

    QFile file("./lock");
    file.open(QIODevice::WriteOnly);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &app, [=](){ QFile::remove("./lock"); });

    LockHandler lockHandler;
    view.rootContext()->setContextProperty("lockHandler", &lockHandler);

    ContactModel contacts;
    view.rootContext()->setContextProperty("contactsModel", &contacts);

    ShareReceiver *shareReceiver = new ShareReceiver(&contacts);
    view.rootContext()->setContextProperty("shareReceiver", shareReceiver);

    view.rootContext()->setContextProperty("user_name", userInfo().at(0));
    view.rootContext()->setContextProperty("user_image", userInfo().at(1));

    contacts.addContactObjects(loadConfig());

    view.load("main.qml");

    lockHandler.handleArgs(args);

    return app.exec();
}
