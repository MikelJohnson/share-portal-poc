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
import QtQuick 2.12
import QtQuick.Controls 2.12
import org.kde.kirigami 2.15 as Kirigami

ApplicationWindow {
    width: 650
    height: 500
    id: window
    minimumWidth: 360
    minimumHeight: 640
    visible: true
    title: "Share..."
    color: Kirigami.Theme.backgroundColor
    Component.onCompleted: backend.fetchAppInfo()  
    header: Column {
        padding: 20
        Text {
            text: backend ? backend.mime : ""
            color: Kirigami.Theme.textColor
        }
    }
    ListView {
        id: directGrid
        width: parent.width
        height: 145
        ScrollBar.horizontal: ScrollBar { 
            z: 1
            size: 0.15
        }
        
        Rectangle {
            anchors.fill: parent
            color:  Kirigami.Theme.alternateBackgroundColor
            z: -1
        }

        model: appInfoModel
        orientation: ListView.Horizontal
        delegate: Item {
            width: directGrid.width
            height: 145
            ListView {
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height
                clip: true
                delegate: MouseArea {
                    property var values: direct_targets[index]
                    width: 150
                    height: 100
                    Kirigami.Icon {
                        id: drawerIcons
                        width: 50
                        height: 50
                        source: values.image === "" ? icon : values.image
                        anchors.centerIn: parent
                        Kirigami.Icon {
                            anchors.top: parent.bottom
                            anchors.left: parent.right
                            anchors.margins: -15
                            width: 25
                            height: 25
                            source: icon
                            visible: values.image !== ""
                        }
                    }
                    Text {
                        text: values.title
                        font.pixelSize: 10
                        anchors.top: drawerIcons.bottom
                        anchors.topMargin: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Kirigami.Theme.textColor
                    }
                    Text {
                        text: values.uuid
                        font.pixelSize: 10
                        anchors.top: drawerIcons.bottom
                        anchors.topMargin: 25
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Kirigami.Theme.textColor
                        opacity: 0.5
                        width: 100
                        wrapMode: Text.WrapAnywhere
                    }
                    onClicked:{
                        if (mouse.button === Qt.LeftButton){
                            backend.launchApp(exec, values.uuid, desktop_name)
                        }
                    }
                }
                model: direct_targets
                orientation: ListView.Horizontal
            }
        }
    }
    ListView {
        id: appGrid
        anchors.fill: parent
        anchors.topMargin: directGrid.height
        clip: true
        ScrollBar.vertical: ScrollBar { 
            z: 1
            size: 0.15
        }

        model: appInfoModel
        delegate: Item {
            width: appGrid.width
            height: 120
            Item {
                id: appInfo
                width: 150
                height: 100
                Kirigami.Icon {
                    id: drawerIcons
                    width: 50
                    height: 50
                    source: icon
                    anchors.centerIn: parent
                }                       
                Text {
                    text:name
                    font.pixelSize: 10
                    anchors.top: drawerIcons.bottom
                    anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: Kirigami.Theme.textColor
                }
            }
            ListView {
                anchors.left: appInfo.right
                anchors.right: parent.right
                height: parent.height
                clip: true
                delegate: MouseArea {
                    property var values: share_targets[index]
                    width: 150
                    height: 100
                    Kirigami.Icon {
                        id: drawerIcons
                        width: 50
                        height: 50
                        source: values.icon === "" ? icon : values.icon
                        anchors.centerIn: parent
                    }                       
                    Text {
                        text: values.name
                        font.pixelSize: 10
                        anchors.top: drawerIcons.bottom
                        anchors.topMargin: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Kirigami.Theme.textColor
                    }
                    Text {
                        text: values.key
                        font.pixelSize: 10
                        anchors.top: drawerIcons.bottom
                        anchors.topMargin: 25
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Kirigami.Theme.textColor
                        opacity: 0.5
                    }
                    onClicked:{
                        if (mouse.button === Qt.LeftButton){
                            backend.launchApp(exec, values.key, desktop_name)
                        }
                    }
                }
                model: share_targets
                orientation: ListView.Horizontal
            }
        }
    }
}
