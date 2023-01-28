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

#include "ShareReceiver.h"
#include <QRandomGenerator>
#include <QFileInfo>
ShareReceiver::ShareReceiver(ContactModel *shareModel) : m_shareModel(shareModel)
{
    m_shareReceiver = new org::freedesktop::Share("org.freedesktop.Share", "/org/freedesktop/Share",
                           QDBusConnection::sessionBus(), this);
}

QVariantMap ShareReceiver::extras() const {
    return m_extras;
}

void ShareReceiver::receive(QString uuid) {
    QDBusPendingReply<QVariantMap> reply = m_shareReceiver->Receive(uuid);
    reply.waitForFinished();
    m_extras = reply.value();
    emit extrasChanged();
};

void ShareReceiver::dynamicRegister() {
    QList<QVariantMap> dynamicList;
    for (int i = 0; i < m_shareModel->length(); i++) {
        ContactObject obj = m_shareModel->getObject(i);
        QVariantMap share_target;
        share_target["uuid"] = QVariant(obj.uuid());
        share_target["title"] = QVariant(obj.name());
        share_target["image"] = QVariant(QFileInfo(obj.image()).canonicalFilePath());
        share_target["mime"] = QVariant(QStringList{"image/png", "text/plain"});
        share_target["acceptsMultipleFiles"] = QVariant(true);
        share_target["priority"] = QVariant(int(QRandomGenerator::global()->bounded(0, 100)));
        dynamicList.push_back(share_target);
    }
    m_shareReceiver->DynamicRegister("/usr/share/applications/foosocial.desktop", dynamicList);
}

void ShareReceiver::dynamicClear() {
    m_shareReceiver->DynamicClear("/usr/share/applications/foosocial.desktop");
}

QVariantList ShareReceiver::variantListFromKey(QString key) {
    if (!m_extras.contains(key)) {
        return QVariantList();
    }
    QDBusArgument dbusList = m_extras["files"].value<QDBusArgument>();
    QVariantList result;
    dbusList >> result;
    return result;
}
