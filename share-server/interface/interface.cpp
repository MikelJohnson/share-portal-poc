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
#include <QtQuick/qquickview.h>
#include <QQmlApplicationEngine> 
#include <QGuiApplication>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <QtQuick/qquickitem.h>
#include <qqml.h>
#include <iostream>
#include <QDir>
#include "InterfaceManager.h"

using namespace std;
QQmlContext *context;

int main(int argc, char ** argv) {

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine view;

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    context = view.rootContext();

    app.setWindowIcon(QIcon::fromTheme("emblem-shared-symbolic"));

    QString mime, share_uuid;
    bool multiple_files = false;

    for (int i = 1; i < argc; i++) {
        QString arg(argv[i]);
        if (arg.contains("--multiple-files")) {
            multiple_files = true;
        } if (arg.contains("--share-mime=")) {
            mime = arg.replace("--share-mime=", "");
        }
    }

    AppInfoModel appInfoModel;
    view.rootContext()->setContextProperty("appInfoModel", &appInfoModel);

    BackendManager backend(mime, multiple_files, &appInfoModel);
    view.rootContext()->setContextProperty("backend", &backend);

    view.load("interface/interface.qml");
    
    return app.exec();
    
} 
