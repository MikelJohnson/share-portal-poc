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
    width: 650
    height: 500
    visible: true
    Column {
        width: parent.width
        padding: 5
        Row {
            spacing: 5
            Button {
                text: "send stuff"
                onClicked: if (mimeText.text) shareSender.send(mimeText.text, jsonText.text)
            }
            Button {
                text: "text example"
                onClicked: {
                    mimeText.text = "text/plain"
                    titleText.text = ""
                    descriptionText.text = ""
                    filesText.text = ""
                    textText.text = "The quick brown fox jumps over the lazy dog"
                }
            }
            Button {
                text: "image example"
                onClicked: {
                    mimeText.text = "image/png"
                    titleText.text = ""
                    descriptionText.text = ""
                    filesText.text = "\"file://home/user/Pictures/image.png\""
                    textText.text = ""
                }
            }
            Button {
                text: "images example"
                onClicked: {
                    mimeText.text = "image/png"
                    titleText.text = ""
                    descriptionText.text = ""
                    filesText.text = "\"file://home/user/Pictures/image1.png\", \"file://home/user/Pictures/image2.png\", \"file://home/user/Pictures/image3.png\""
                    textText.text = ""
                }
            }
            Button {
                text: "app example"
                onClicked: {
                    mimeText.text = "text/plain"
                    titleText.text = "AwesomeApp"
                    descriptionText.text = "App that does all kinds of awesome things!"
                    filesText.text = ""
                    textText.text = "appstream://org.dev.awesomeapp.desktop"
                }
            }
        }
        Text { text: "Mime" }
        TextField {
            id: mimeText
            width: 200
            placeholderText: "Mime"
            selectByMouse: true
        }

        Text { text: "Title" }
        TextField {
            id: titleText
            width: 200
            placeholderText: "Title"
            selectByMouse: true
        }

        Text { text: "Description" }
        TextField {
            id: descriptionText
            width: 200
            selectByMouse: true
            placeholderText: "Description"
        }

        Text { text: "Text"; visible: mimeText.text === "text/plain" }
        TextField {
            id: textText
            width: 300
            placeholderText: "Text"
            visible: mimeText.text === "text/plain"
            selectByMouse: true
        }

        Text { text: "Files"; visible: mimeText.text !== "text/plain" }
        TextField {
            id: filesText
            width: 300
            visible: mimeText.text !== "text/plain"
            placeholderText: "Files"
            selectByMouse: true
        }

        Text {
            id: jsonText
            width: parent.width
            height: 600
            wrapMode: Text.WordWrap
            text: "{\n\t\"title\": \"" + titleText.text + "\",\n\t\"description\": \"" + descriptionText.text + "\",\n\t\"text\": \"" + textText.text + "\",\n\t\"files\": [ " + filesText.text + " ]\n}"
        }
    }
}

