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
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    title: qsTr("FooSocial")
    width: 650
    height: 500
    minimumWidth: 200
    minimumHeight: 50
    visible: true
    ListView {
        anchors.fill: parent
        anchors.rightMargin: parent.width / 2
        model: contactsModel
        delegate: Row {
            topPadding: 10
            leftPadding: 10
            Image {
                width: 50
                height: 50
                source: image
            }
            Text {
                leftPadding: 10
                text: name + "\n" + uuid
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
    Connections {
        target: shareReceiver
        function onDataChanged() {
            switch(shareReceiver.target) {
                case "Debug":
                    viewDebugInfo.activated()
                    break
                case "Generic":
                    shareSelector.activated()
                    break
                case "ChangeProfileImage":
                    changeProfileImage.activated()
                    break
                default:
                    shareDirect.activated()
                    break
            }
        }
    }
    Row {
        anchors.bottom: parent.bottom
        Button {
            text: "Register dynamic targets"
            onClicked: shareReceiver.dynamicRegister()
        }
        Button {
            text: "Clear dynamic targets"
            onClicked: shareReceiver.dynamicClear()
        }
    }
    Dialog {
        id: changeProfileImage
        width: 570
        height: 400
        anchors.centerIn: parent
        modal: true
        focus: true
        padding: 0
        closePolicy: Popup.CloseOnEscape
        header: Row {
            spacing: 10
            padding: 10
            Image {
                width: 50
                height: 50
                source: user_image
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "Change profile image for " + user_name
            }
        }
        standardButtons: Dialog.Close
        Rectangle {
            color: "#E0E0E0"
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 12
            Item {          
                id: userData
                anchors.fill: parent
                anchors.margins: 10

                property string debugText
                Column {
                    spacing: 10
                    Text {
                        text: userData.debugText ? "Change image to: " + userData.debugText + "?" : ""
                    }
                    Text {
                        text: "Imagine a pretty preview here"
                    }
                }
            }

        }
        signal activated()
        onActivated: {
            userData.debugText = shareReceiver.variantListFromKey("files")[0]
            open()
        }
    }
    Dialog {
        id: viewDebugInfo
        width: 570
        height: 400
        anchors.centerIn: parent
        modal: true
        focus: true
        padding: 0
        closePolicy: Popup.CloseOnEscape
        header: Row {
            padding: 10
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "Share info"
            }
        }
        standardButtons: Dialog.Close
        Rectangle {
            color: "#E0E0E0"
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 12
            DebugInfo {
                id: debugData
                anchors.fill: parent
                anchors.margins: 10
            }
        }
        signal activated()
        onActivated: {
            debugData.fetch()
            open()
        }
    }
    Dialog {
        id: shareSelector
        width: 570
        height: 400
        anchors.centerIn: parent
        modal: true
        focus: true
        padding: 0
        closePolicy: Popup.CloseOnEscape
        title: "Send to..."
        standardButtons: Dialog.Close
        ListView {
            clip: true
            anchors.fill: parent
            anchors.rightMargin: parent.width / 2
            model: contactsModel
            delegate: Row {
                topPadding: 10
                leftPadding: 10
                Image {
                    width: 50
                    height: 50
                    source: image
                }
                Text {
                    leftPadding: 10
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        Rectangle {
            color: "#E0E0E0"
            anchors.fill: parent
            anchors.leftMargin: parent.width / 2
            anchors.rightMargin: 12
            ShareData {
                id: selectorData
                anchors.fill: parent
                anchors.margins: 10
            }
        }
        signal activated()
        onActivated: {
            selectorData.fetch()
            open()
        }
    }
    Dialog {
        id: shareDirect
        property var contact
        width: 570
        height: 400
        anchors.centerIn: parent
        modal: true
        focus: true
        padding: 0
        closePolicy: Popup.CloseOnEscape
        header: Row {
            spacing: 10
            padding: 10
            Image {
                width: 50
                height: 50
                source: shareDirect.contact ? shareDirect.contact.image : ""
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: shareDirect.contact ? "Send to " + shareDirect.contact.name + " (" + shareDirect.contact.uuid + ")" : ""
            }
        }
        standardButtons: Dialog.Close
        Rectangle {
            color: "#E0E0E0"
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 12
            ShareData {
                id: directData
                anchors.fill: parent
                anchors.margins: 10
            }
        }
        signal activated()
        onActivated: {
            var contact_index = contactsModel.indexByUuid(shareReceiver.target)
            if (contact_index === -1) {
                close()
            }
            contact = contactsModel.get(contact_index)
            directData.fetch()
            open()
        }
    }
    Row {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 10
        Image {
            width: 50
            height: 50
            source: user_image
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: user_name
        }
    }
} 
