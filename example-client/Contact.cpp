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

#include "Contact.h"

#include <QJsonArray>
#include <QJsonDocument>

ContactObject::ContactObject(QJsonObject jsonObject)
{
    m_name = (jsonObject["name"].toString());
    m_image = (jsonObject["image"].toString());
    m_uuid = (jsonObject["uuid"].toString());
}

ContactObject::ContactObject() { }

QString ContactObject::name() const { return m_name; }
QString ContactObject::image() const { return m_image; }
QString ContactObject::uuid() const { return m_uuid; }

void ContactObject::set_name(QString name) { m_name = name; }
void ContactObject::set_image(QString image) { m_image = image; }
void ContactObject::set_uuid(QString uuid) { m_uuid = uuid; }

ContactModel::ContactModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ContactModel::addContactObject(const ContactObject &data_object)
{
    beginInsertRows(QModelIndex(), length(), length());
    m_data << data_object;
    endInsertRows();
    emit lengthChanged();
}

void ContactModel::insertContactObject(const int index, const ContactObject &data_object)
{
    beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, data_object);
    endInsertRows();
    emit lengthChanged();
}

void ContactModel::removeContactObject(const int index) {
    beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    endRemoveRows();
    emit lengthChanged();
}

QVariant ContactModel::get(const int index) const {
    if (index > m_data.size() - 1) return QVariant();
    return QVariant::fromValue<ContactObject>(m_data[index]);
}

ContactObject ContactModel::getObject(const int index) const {
    if (index > m_data.size() - 1) return ContactObject();
    return m_data[index];
}

void ContactModel::addContactObject(QString data)
{
    if (data.isEmpty()) { return; }
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8());
    ContactObject object(jsonDocument.object());
    addContactObject(object);
}

void ContactModel::addContactObjects(QString data)
{
    if (data.isEmpty()) { return; }
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8());
    QJsonArray objectsArray = jsonDocument.array();
    if (objectsArray.isEmpty()) { return; }
    beginInsertRows(QModelIndex(), length(), length() + objectsArray.count() - 1);
    for (const QJsonValue &value : objectsArray) {
        ContactObject ContactObjectValue(value.toObject());
        m_data << ContactObjectValue;
    }
    endInsertRows();
    emit lengthChanged();
}

void ContactModel::clearList() {
    beginRemoveRows(QModelIndex(), 0, m_data.size()-1);
    m_data.clear();
    endRemoveRows();
    emit lengthChanged();
}

int ContactModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

int ContactModel::length() const {
    return m_data.count();
}

QVariant ContactModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    const ContactObject &data_object = m_data[index.row()];

    if (role == NameRole) return data_object.name();
    else if (role == ImageRole) return data_object.image();
    else if (role == UuidRole) return data_object.uuid();

    return QVariant();
}

QHash<int, QByteArray> ContactModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[NameRole] = "name";
    roles[ImageRole] = "image";
    roles[UuidRole] = "uuid";

    return roles;
}

int ContactModel::indexByUuid(QString uuid) {
    QModelIndexList results = match(index(0,0), ContactModel::UuidRole, uuid, -1, Qt::MatchFlags(Qt::MatchExactly));
    if (results.empty()) {
        return -1;
    }
    return results[0].row();
}
