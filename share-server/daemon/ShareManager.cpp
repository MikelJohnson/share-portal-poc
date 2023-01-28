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

#include "ShareManager.h"
#include <QUuid>
#include <QDBusArgument>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

ShareManager::ShareManager(QObject *parent) : QObject(parent) { }

void ShareManager::Send(const QString &mime, const QVariantMap &extras) {
    QString uuid = QUuid::createUuid().toString().replace("{", "").replace("}", "");
    QString multiple;
    m_requests[uuid] = QVariant(QVariantList{QVariant(mime), QVariant(extras)});
    if (extras.contains("files")) {
        QDBusArgument dbusList = extras["files"].value<QDBusArgument>();
        QVariantList result;
        dbusList >> result;
        if (result.count() > 1) {
            multiple = " --multiple-files";
        }
    }
    system(QString("nohup ./share-interface --share-mime=" + mime + " --share-uuid=" + uuid + multiple + " </dev/null >/dev/null 2>&1 &").toStdString().c_str());
}

QVariantMap ShareManager::Receive(const QString &uuid) {
    if (!m_requests.contains(uuid)) {
        return QVariantMap();
    }
    QVariantMap extras = m_requests[uuid].toList().at(1).toMap();
    m_requests.remove(uuid);
    return extras;
}

void ShareManager::DynamicRegister(const QString &app, const QList<QVariantMap> &targets) {
    QJsonArray targets_array;
    for (const QVariantMap &varMap : targets) {
        targets_array.push_back(QJsonObject::fromVariantMap(varMap));
    }
    QFile loadFile(QStringLiteral("./daemon/DirectInfo.json"));

    if (!loadFile.open(QIODevice::ReadWrite)) {
        return;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonObject file = QJsonDocument::fromJson(saveData).object();
    file[app] = targets_array;
    loadFile.resize(0);
    loadFile.write(QJsonDocument(file).toJson());
}

void ShareManager::DynamicClear(const QString &app) {
    QFile loadFile(QStringLiteral("./daemon/DirectInfo.json"));

    if (!loadFile.open(QIODevice::ReadWrite)) {
        return;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonObject file = QJsonDocument::fromJson(saveData).object();
    file.remove(app);
    loadFile.resize(0);
    loadFile.write(QJsonDocument(file).toJson());
}
