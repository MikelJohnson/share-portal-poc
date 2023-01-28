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
#include "AppInfo.h"

ShareTargets::ShareTargets() { }
ShareTargets::ShareTargets(QString key, QString name, QString icon, QString exec) : m_key(key), m_name(name), m_icon(icon), m_exec(exec) { }

QString ShareTargets::key() const { return m_key; }
QString ShareTargets::name() const { return m_name; }
QString ShareTargets::icon() const { return m_icon; }
QString ShareTargets::exec() const { return m_exec; }

DirectTargets::DirectTargets() { }
DirectTargets::DirectTargets(QString uuid, QString title, QString image, int priority) : m_uuid(uuid), m_title(title), m_image(image), m_priority(priority) { }

QString DirectTargets::uuid() const { return m_uuid; }
QString DirectTargets::title() const { return m_title; }
QString DirectTargets::image() const { return m_image; }
int DirectTargets::priority() const { return m_priority; }

AppInfoObject::AppInfoObject() { }
AppInfoObject::AppInfoObject(QString name, QString icon, QString exec, QString directExec, QList<ShareTargets> share_targets, QList<DirectTargets> direct_targets) : m_name(name), m_icon(icon), m_exec(exec), m_directExec(directExec), m_share_targets(share_targets), m_direct_targets(direct_targets) { }

QString AppInfoObject::name() const { return m_name; }
QString AppInfoObject::icon() const { return m_icon; }
QString AppInfoObject::exec() const { return m_exec; }
QString AppInfoObject::directExec() const { return m_directExec; }
QList<ShareTargets> AppInfoObject::share_targets() const { return m_share_targets; }
QList<DirectTargets> AppInfoObject::direct_targets() const { return m_direct_targets; }

AppInfoModel::AppInfoModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void AppInfoModel::addAppInfoObject(const AppInfoObject &data_object)
{
    beginInsertRows(QModelIndex(), length(), length());
    m_data << data_object;
    endInsertRows();
    emit lengthChanged();
}

void AppInfoModel::insertAppInfoObject(const int index, const AppInfoObject &data_object)
{
    beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, data_object);
    endInsertRows();
    emit lengthChanged();
}

void AppInfoModel::removeAppInfoObject(const int index) {
    beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    endRemoveRows();
    emit lengthChanged();
}

QVariant AppInfoModel::get(const int index) const {
    if (index > m_data.size() - 1) return QVariant();
    return QVariant::fromValue<AppInfoObject>(m_data[index]);
}

void AppInfoModel::clearList() {
    beginRemoveRows(QModelIndex(), 0, m_data.size()-1);
    m_data.clear();
    endRemoveRows();
    emit lengthChanged();
}

int AppInfoModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}

int AppInfoModel::length() const {
    return m_data.count();
}

QVariant AppInfoModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    const AppInfoObject &data_object = m_data[index.row()];

    if (role == NameRole) return data_object.name();
    else if (role == IconRole) return data_object.icon();
    else if (role == ExecRole) return data_object.exec();
    else if (role == DirectExecRole) return data_object.directExec();
    else if (role == ShareTargetsRole) return QVariant::fromValue<QList<ShareTargets>>(data_object.share_targets());
    else if (role == DirectTargetsRole) return QVariant::fromValue<QList<DirectTargets>>(data_object.direct_targets());

    return QVariant();
}

QHash<int, QByteArray> AppInfoModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[ExecRole] = "exec";
    roles[DirectExecRole] = "direct_exec";
    roles[ShareTargetsRole] = "share_targets";
    roles[DirectTargetsRole] = "direct_targets";

    return roles;
}
