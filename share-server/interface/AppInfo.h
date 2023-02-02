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
#ifndef APPINFO_H
#define APPINFO_H

#include <QAbstractListModel>
#include <QString>
#include <QVariant>

class ShareTargets
{
    Q_GADGET
    Q_PROPERTY(QString key READ key)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString icon READ icon)

public:
    ShareTargets();
    ShareTargets(QString key, QString name, QString icon);

    QString key() const;
    QString name() const;
    QString icon() const;

private:
    QString m_key;
    QString m_name;
    QString m_icon;
};

Q_DECLARE_METATYPE(ShareTargets)

class DirectTargets
{
    Q_GADGET
    Q_PROPERTY(QString uuid READ uuid)
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString image READ image)
    Q_PROPERTY(int priority READ priority)

public:
    DirectTargets();
    DirectTargets(QString uuid, QString title, QString image, int priority);

    QString uuid() const;
    QString title() const;
    QString image() const;
    int priority() const;
private:
    QString m_uuid;
    QString m_title;
    QString m_image;
    int m_priority;
};

Q_DECLARE_METATYPE(DirectTargets)

class AppInfoObject
{
    Q_GADGET
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString icon READ icon)
    Q_PROPERTY(QString exec READ exec)
    Q_PROPERTY(QString desktop_name READ desktop_name)
    Q_PROPERTY(QList<ShareTargets> share_targets READ share_targets)
    Q_PROPERTY(QList<DirectTargets> direct_targets READ direct_targets)

public:
    AppInfoObject();
    AppInfoObject(QString name, QString icon, QString exec, QString desktop_name, QList<ShareTargets> share_targets, QList<DirectTargets> direct_targets);

    QString name() const;
    QString icon() const;
    QString exec() const;
    QString desktop_name() const;
    QList<ShareTargets> share_targets() const;
    QList<DirectTargets> direct_targets() const;

private:
    QString m_name;
    QString m_icon;
    QString m_exec;
    QString m_desktop_name;
    QList<ShareTargets> m_share_targets;
    QList<DirectTargets> m_direct_targets;
};

Q_DECLARE_METATYPE(AppInfoObject)


class AppInfoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)
public:
    enum AppInfoObjectRoles {
        NameRole = Qt::UserRole + 1,
        IconRole,
        ExecRole,
        DesktopNameRole,
        ShareTargetsRole,
        DirectTargetsRole
    };

    AppInfoModel(QObject *parent = 0);

    Q_INVOKABLE void clearList();

    void addAppInfoObject(const AppInfoObject &data_object);
    void insertAppInfoObject(const int index, const AppInfoObject &data_object);
    void removeAppInfoObject(const int index);

    Q_INVOKABLE QVariant get(const int index) const;

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int length() const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

signals:
    void lengthChanged();

protected:
    QHash<int, QByteArray> roleNames() const;
    QList<AppInfoObject> m_data;
};

#endif
