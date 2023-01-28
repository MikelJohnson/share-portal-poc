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
    property string shareMime
    property string shareUuid
    property string debugText
    property string debugText2
    Column {
        spacing: 10
        Text {
            text: shareUuid ? "share_uuid: " + shareUuid : ""
            font.pixelSize: 10
        }
        Text {
            text: shareMime ? "share_mime: " + shareMime : ""
            font.pixelSize: 10
        }
        Text {
            text: debugText ? "extras: " + debugText: ""
            font.pixelSize: 10
        }
        Text {
            text: debugText2
            font.pixelSize: 10
        }
    }
    onShareUuidChanged: {
        if (shareUuid === "") {
            return
        }
        shareReceiver.receive(shareUuid)
        shareData.debugText = JSON.stringify(shareReceiver.extras, null, "\r").replace("\"\"", "object")
        shareData.debugText2 = "files: " + JSON.stringify(shareReceiver.variantListFromKey("files"), null, "\r")
    }
}
