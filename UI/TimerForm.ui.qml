import QtQuick 2.4

Item {
    width: 400
    height: 200

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 200
        color: "#000000"

        Text {
            id: clock
            x: (rectangle.width-width)/2
            y: (rectangle.height-height)/2
            color: "#ffffff"
            text: qsTr("00:00:00")
            font.pixelSize: 80
        }
    }
}
