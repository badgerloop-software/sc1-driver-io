import QtQuick 2.4

Item {
    id: power
    width: 400
    height: 400

    Rectangle {
        id: solar
        x: 0
        y: 0
        width: 400
        height: power.height / 3
        color: "#000000"

        Text {
            id: text1
            x: 50
            y: 52
            color: "#ffffff"
            text: qsTr("Solar")
            font.pixelSize: 25
        }

        Text {
            id: solarP
            x: (solar.width - width) / 2
            y: 43
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 40
        }

        Text {
            id: text2
            x: 308
            y: 52
            color: "#ffffff"
            text: qsTr("W")
            font.pixelSize: 25
        }
    }

    Rectangle {
        id: net
        x: 0
        y: 1 / 3 * power.height - 1
        width: 400
        height: power.height / 3
        color: "#000000"
        Text {
            id: text3
            x: 50
            y: 52
            color: "#ffffff"
            text: qsTr("Net")
            font.pixelSize: 25
        }

        Text {
            id: netP
            x: (net.width - width) / 2
            y: 43
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 40
        }

        Text {
            id: text4
            x: 308
            y: 52
            color: "#ffffff"
            text: qsTr("W")
            font.pixelSize: 25
        }
    }

    Rectangle {
        id: motor
        x: 0
        y: 2 / 3 * power.height - 1
        width: 400
        height: power.height / 3 + 1
        color: "#000000"
        Text {
            id: text5
            x: 50
            y: 52
            color: "#ffffff"
            text: qsTr("Motor")
            font.pixelSize: 25
        }

        Text {
            id: motorP
            x: (motor.width - width) / 2
            y: 43
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 40
        }

        Text {
            id: text6
            x: 308
            y: 52
            color: "#ffffff"
            text: qsTr("W")
            font.pixelSize: 25
        }
    }
}
