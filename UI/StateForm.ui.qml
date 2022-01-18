/**import QtQuick 2.4

Item {
    id: stateBox
    width: 64
    height: 64

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 64
        height: 64
        color: "#000000"
        border.color: "#000000"
        Text {
            id: text1
            x: (stateBox.width - width) / 2
            y: (stateBox.height - height) / 2
            width: 64
            color: "#ffffff"
            text: backEnd.state
            font.pixelSize: 48
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            scale: 1.477
        }
    }
}
**/
