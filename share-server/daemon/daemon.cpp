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

#include <QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QDir>
#include "ShareManager.h"
#include "qmake/share_adaptor.h"

int main(int argc, char *argv[])
{
    qDBusRegisterMetaType<QList<QVariantMap>>();
    QCoreApplication app(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    ShareManager *shareManager = new ShareManager(&app);

    new ShareAdaptor(shareManager);

    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/org/freedesktop/Share", shareManager);
    connection.registerService("org.freedesktop.Share");

    return app.exec();
}
