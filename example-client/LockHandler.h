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
#ifndef LOCKHANDLER_H
#define LOCKHANDLER_H

#include <QObject>
#include <QString>
#include <QFileSystemWatcher>

class LockHandler : public QObject
{
    Q_OBJECT

public:
    LockHandler();
    void handleArgs(QStringList args);

signals:
    void requestFromLock(QString mode, QString share_mime, QString share_uuid, QString target_uuid);

public slots:
    void lockTriggered(QString path);

private:
    QFileSystemWatcher *lockWatcher;
};

#endif
