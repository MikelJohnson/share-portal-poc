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
#include "qmake/share_interface.h"
#include "Contact.h"

class ShareReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString target READ target NOTIFY dataChanged)
    Q_PROPERTY(QString mime READ mime NOTIFY dataChanged)
    Q_PROPERTY(QVariantMap extras READ extras NOTIFY dataChanged)

public:
    ShareReceiver(ContactModel *shareModel);
    Q_INVOKABLE void dynamicRegister();
    Q_INVOKABLE void dynamicClear();
    Q_INVOKABLE QVariantList variantListFromKey(QString key);
    QString target() const;
    QString mime() const;
    QVariantMap extras() const;

public slots:
    void Receive(QString target, QString mime, QVariantMap extras);

signals:
    void dataChanged();

private:
    org::freedesktop::Share* m_shareReceiver;
    ContactModel *m_shareModel;
    QString m_target;
    QString m_mime;
    QVariantMap m_extras;
};

#endif // VIEWNAV_H
