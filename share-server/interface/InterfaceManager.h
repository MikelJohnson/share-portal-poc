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
#ifndef BACKENDMANAGER
#define BACKENDMANAGER

#include <QObject>
#include <QString>
#include "AppInfo.h"

using namespace std;

class BackendManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString mime READ mime NOTIFY mimeChanged)
    Q_PROPERTY(QString share_uuid READ share_uuid NOTIFY shareUuidChanged)

public:
    BackendManager(QString mime, QString share_uuid, bool multiple_files, AppInfoModel *appInfo, QObject *parent = nullptr);
    Q_INVOKABLE void fetchAppInfo();    
    Q_INVOKABLE void launchApp(QString launchPath, QString target_uuid = "");
    void getDesktopFileInfo(QString path);
    QList<DirectTargets> getDirectShareInfo(QString path);

    QString mime() const;
    QString share_uuid() const;

signals:
    void mimeChanged();
    void shareUuidChanged();

private:
    AppInfoModel *m_appInfoModel;
    QString m_mime;
    QString m_share_uuid;
    bool m_multiple_files;
};

#endif
