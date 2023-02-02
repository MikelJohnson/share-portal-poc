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

Item {
    id: shareData
    property string debugText
    Column {
        spacing: 10
        visible: shareReceiver.mime === "text/plain"
        Text {
            text: shareReceiver.extras["title"]
        }
        Text {
            text: shareReceiver.extras["description"]
            font.pixelSize: 10
        }
        Text {
            text: shareReceiver.extras["text"]
            font.pixelSize: 10
        }
    }
    Column {
        spacing: 10
        visible: shareReceiver.mime !== "text/plain"
        Text {
            text: debugText
            font.pixelSize: 10
        }
        Text {
            text: "Imagine a rich preview here!"
            font.pixelSize: 10
        }
    }
    signal fetch()
    onFetch: {
        shareData.debugText = "files: " + JSON.stringify(shareReceiver.variantListFromKey("files"), null, "\r")
    }
}
