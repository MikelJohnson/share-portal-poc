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

#ifndef VIEWNAV_H
#define VIEWNAV_H

#include <QObject>
#include <QVariant>
#include <memory>
#include "qmake/share_target_interface.h"
#include <QDBusServiceWatcher>

class ShareManager : public QObject
{
    Q_OBJECT
public:
    ShareManager(QObject *parent);

public slots:
    void Send(const QString &mime, const QVariantMap &extras);
    bool CanShare(const QString &mime, const QVariantMap &extras);
    void DynamicRegister(const QString &app, const QList<QVariantMap> &targets);
    void DynamicClear(const QString &app);
    void Process(QStringList info, QString uuid, QString service);
    void Receive(const QString &target, const QString &uuid);
private:
    std::unique_ptr<org::freedesktop::ShareTarget> m_share_target;
    std::unique_ptr<QDBusServiceWatcher> m_dbus_watcher;
    QVariantMap m_requests;
};

#endif // VIEWNAV_H
