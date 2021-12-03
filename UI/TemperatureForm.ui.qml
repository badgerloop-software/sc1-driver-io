/**import QtQuick 2.4

Item {
    id: temp
    width: 600
    height: 200

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 200
        height: 200
        color: "#000000"

        Text {
            id: text1
            x: 68
            y: 33
            color: "#ffffff"
            text: qsTr("Temp 1")
            font.pixelSize: 20
        }

        Text {
            id: text2
            x: 88
            y: 149
            width: 25
            height: 22
            color: "#ffffff"
            text: qsTr("℃")
            font.pixelSize: 20
        }

        Text {
            id: temp1
            x: (rectangle.width - width) / 2
            y: (rectangle.height - height) / 2
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 50
        }
    }

    Rectangle {
        id: rectangle1
        x: 200
        y: 0
        width: 200
        height: 200
        color: "#000000"
        Text {
            id: text3
            x: 68
            y: 33
            color: "#ffffff"
            text: qsTr("Temp 2")
            font.pixelSize: 20
        }

        Text {
            id: text4
            x: 88
            y: 149
            width: 25
            height: 22
            color: "#ffffff"
            text: qsTr("℃")
            font.pixelSize: 20
        }

        Text {
            id: temp2
            x: (rectangle1.width - width) / 2
            y: (rectangle1.height - height) / 2
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 50
        }
    }

    Rectangle {
        id: rectangle2
        x: 400
        y: 0
        width: 200
        height: 200
        color: "#000000"
        Text {
            id: text5
            x: 68
            y: 33
            color: "#ffffff"
            text: qsTr("Temp 3")
            font.pixelSize: 20
        }

        Text {
            id: text6
            x: 88
            y: 149
            width: 25
            height: 22
            color: "#ffffff"
            text: qsTr("℃")
            font.pixelSize: 20
        }

        Text {
            id: temp3
            x: (rectangle2.width - width) / 2
            y: (rectangle2.height - height) / 2
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 50
        }
    }
}
/**/
