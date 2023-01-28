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
#include "LockHandler.h"
#include <QFile>
#include <QTextStream>
LockHandler::LockHandler()
{
    lockWatcher = new QFileSystemWatcher(QStringList("lock_log"), this);
    connect(lockWatcher, &QFileSystemWatcher::fileChanged, this, &LockHandler::lockTriggered);
}

void LockHandler::lockTriggered(QString path)
{
    QFile file("./lock_log");
    if (!file.open(QIODevice::ReadWrite)) {
        return;
    }
    QTextStream out(&file);
    QString result = out.readLine();
    if (result.isEmpty()) {
        return;
    }
    file.resize(0);
    handleArgs(result.split(" "));
}

void LockHandler::handleArgs(QStringList args)
{
    QString mode, mime, share, target;
    for (QString arg : args) {
        if (arg.isEmpty()) {
            continue;
        }
        if (arg.contains("--share-mime=")) {
            mime = arg.replace("--share-mime=", "");
        } else if (arg.contains("--share-uuid=")) {
            share = arg.replace("--share-uuid=", "");
        } else if (arg.contains("--target-uuid=")) {
            target = arg.replace("--target-uuid=", "");
        } else {
            mode = arg.replace("--", "");
        }
    }
    emit requestFromLock(mode, mime, share, target);
}
