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
#include "InterfaceManager.h"
#include <QFile>
#include <QRegularExpression>
#include <QDirIterator>
#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <iostream>

BackendManager::BackendManager(QString mime, bool multiple_files, AppInfoModel *appInfo, QObject *parent) : m_mime(mime), m_multiple_files(multiple_files), m_appInfoModel(appInfo), QObject(parent) { }

QString BackendManager::mime() const { return m_mime; }
QList<DirectTargets> BackendManager::getDirectShareInfo(QString path) {
    QFile loadFile(QStringLiteral("./daemon/DirectInfo.json"));
    QList<DirectTargets> targets;

    if (!loadFile.open(QIODevice::ReadWrite)) {
        return QList<DirectTargets>();
    }

    QByteArray fileData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(fileData));

    for (const QJsonValue val : loadDoc.object()[path].toArray()) {
        QJsonObject obj = val.toObject();
        if (m_multiple_files && obj["acceptsMultipleFiles"].toBool() == false) {
            continue;
        }
        if (!obj["mime"].toArray().contains(QJsonValue(m_mime))) {
            continue;
        }
        DirectTargets target = DirectTargets(obj["uuid"].toString(), obj["title"].toString(), obj["image"].toString(), obj["priority"].toInt());
        targets.push_back(target);
    }

    return targets;
}

void BackendManager::getDesktopFileInfo(QString path) {
    QFile file(path);
    QString text;
    QRegularExpressionMatch match;
    QList<ShareTargets> share_targets;
    QList<DirectTargets> direct_targets;
    QString name;
    QString icon;
    QString exec;
    QString main_mime;
    QList<QString> chunks;
    QString desktop_name = path.split("/").last();
    desktop_name.replace(".desktop", "");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    
    while (!file.atEnd()) {
        text = QString(file.readAll());
    }
    if (text.isEmpty() || !text.contains("[Desktop Entry]") || text.contains("NoDisplay=true") || text.contains("Hidden=true")  || text.contains("Terminal=true") || text.contains("OnlyShowIn") || !text.contains("Name") || !text.contains("Exec=")) {
        return;
    }
    text = text.split("[Desktop Entry]").at(1);

    chunks = text.split("\n[");

    if (chunks.count() <= 1) {
        return;
    }

    chunks.at(0).indexOf(QRegularExpression("\\bName=.*"), 0, &match);
    name = match.captured().replace("Name=", "");

    if (chunks.at(0).indexOf(QRegularExpression("\\bIcon=.*"), 0, &match) != -1) {
        icon = match.captured().replace("Icon=", "");
    }

    chunks.at(0).indexOf(QRegularExpression("\\bExec=.*"), 0, &match);
    exec = match.captured().replace("Exec=", "");

    chunks.at(0).indexOf(QRegularExpression("\\bMimeType=.*"), 0, &match);
    main_mime = match.captured().replace("bMimeType=", "");

    chunks.removeFirst();

    for (QString i : chunks) {
        if (!i.startsWith("Desktop Share")) {
            continue;
        }
        QString sh_key = i.split("]").at(0);
        sh_key.replace("Desktop Share ", "");
        QString sh_name;
        QString sh_icon;
        QString sh_mime;
        if (m_multiple_files && !i.contains("AcceptsMultipleFiles=true")) {
            continue;
        }
        if (i.indexOf(QRegularExpression("\\bMimeType=.*"), 0, &match) != -1) {
            sh_mime = match.captured().replace("bMimeType=", "");
        } else {
            sh_mime = main_mime;
        }
        if (!sh_mime.contains(m_mime)) {
            continue;
        }
        i.indexOf(QRegularExpression("\\bName=.*"), 0, &match);
        sh_name = match.captured().replace("Name=", "");

        if (i.indexOf(QRegularExpression("\\bIcon=.*"), 0, &match) != -1) {
            sh_icon = match.captured().replace("Icon=", "");
        }
        ShareTargets target(sh_key, sh_name, sh_icon);
        share_targets.push_back(target);
    }

    direct_targets = getDirectShareInfo(path);

    if (share_targets.count() == 0 && direct_targets.count() == 0) {
        return;
    }

    AppInfoObject appInfo(name, icon, exec, desktop_name, share_targets, direct_targets);

    m_appInfoModel->addAppInfoObject(appInfo);
}

void BackendManager::fetchAppInfo() {
    QString result;
    QDirIterator it("/usr/share/applications", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        getDesktopFileInfo(it.next());
    }
    QDirIterator flatpakit("/var/lib/flatpak/exports/share/applications/", QDirIterator::Subdirectories);
    while (flatpakit.hasNext()) {
        getDesktopFileInfo(flatpakit.next());
    }
}  
void BackendManager::launchApp(QString launchPath, QString group, QString desktop_name) {
    cout << launchPath.toStdString() << "\n" << group.toStdString() << "\n" << desktop_name.toStdString();
    QCoreApplication::quit();
}
