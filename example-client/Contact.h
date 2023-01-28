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

#ifndef CONTACT_H
#define CONTACT_H

#include <QJsonObject>
#include <QAbstractListModel>
#include <QString>
#include <QVariant>
#include <QDBusMetaType>


class ContactObject
{
    Q_GADGET
    Q_PROPERTY(QString name READ name WRITE set_name)
    Q_PROPERTY(QString image READ image WRITE set_image)
    Q_PROPERTY(QString uuid READ uuid WRITE set_uuid)

public:
    ContactObject(QJsonObject jsonObject);
    ContactObject();

    QString name() const;
    QString image() const;
    QString uuid() const;

    void set_name(QString name);
    void set_image(QString image);
    void set_uuid(QString uuid);

private:
    QString m_name;
    QString m_image;
    QString m_uuid;
};

Q_DECLARE_METATYPE(ContactObject)


class ContactModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)
public:
    enum ContactObjectRoles {
        NameRole = Qt::UserRole + 1,
        ImageRole,
        UuidRole
    };

    ContactModel(QObject *parent = 0);

    Q_INVOKABLE void clearList();

    void addContactObject(const ContactObject &data_object);
    void insertContactObject(const int index, const ContactObject &data_object);
    void removeContactObject(const int index);

    Q_INVOKABLE QVariant get(const int index) const;
    ContactObject getObject(const int index) const;

    Q_INVOKABLE void addContactObject(QString data);
    Q_INVOKABLE void addContactObjects(QString data);

    Q_INVOKABLE int indexByUuid(QString uuid);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int length() const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

signals:
    void lengthChanged();

protected:
    QHash<int, QByteArray> roleNames() const;
    QList<ContactObject> m_data;
};

#endif
