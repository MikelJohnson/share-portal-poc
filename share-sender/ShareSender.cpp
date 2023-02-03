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

#include "ShareSender.h"
#include <QVariant>
#include <QJsonDocument>

ShareSender::ShareSender()
{
    m_shareSender = new org::freedesktop::Share("org.freedesktop.Share", "/org/freedesktop/Share",
                           QDBusConnection::sessionBus(), this);
}

void ShareSender::send(QString mime, QString json) {
    QJsonObject extras_object = QJsonDocument::fromJson(json.toUtf8()).object();
    QVariantMap extras;
    for (const QString &key : extras_object.keys()) {
        extras[key] = extras_object[key].toVariant();
    }
    m_shareSender->Send(mime, extras);
};

bool ShareSender::canShare(QString mime, QString json) {
    QJsonObject extras_object = QJsonDocument::fromJson(json.toUtf8()).object();
    QVariantMap extras;
    for (const QString &key : extras_object.keys()) {
        extras[key] = extras_object[key].toVariant();
    }
    QDBusPendingReply<bool> reply = m_shareSender->CanShare(mime, extras);
    reply.waitForFinished();
    return reply.value();
};
