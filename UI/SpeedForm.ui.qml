import QtQuick 2.4

Item {
    id: speedBox
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 400
        color: "#000000"
        border.color: "#000000"

        Text {
            id: text1
            x: (speedBox.width-width)/2
            y: (speedBox.height-height)/2
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 150
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            scale: 1.477
        }

        Text {
            id: text2
            x: 160
            y: 295
            width: 80
            height: 59
            color: "#ffffff"
            text: qsTr("mph")
            font.pixelSize: 40
        }
    }
}
