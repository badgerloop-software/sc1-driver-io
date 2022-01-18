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
        border.color: "#ffffff"

        Text {
            id: text1
            x: 30
            y: 45
            color: "#ffffff"
            text: qsTr("Solar")
            font.pixelSize: 32
        }

        Text {
            id: solarP
            x: (solar.width - width) / 2
            y: 43
            color: "#ffffff"
            text: backEnd.solarPower.toFixed(1)
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
        border.color: "#ffffff"
        Text {
            id: text3
            x: 30
            y: 45
            color: "#ffffff"
            text: qsTr("Net")
            font.pixelSize: 32
            verticalAlignment: Text.AlignTop
        }

        Text {
            id: netP
            x: (net.width - width) / 2
            y: 0
            color: "#ffffff"
            text: backEnd.batteryPower.toFixed(1)
            font.pixelSize: 36
        }

        Text {
            id: text4
            x: 308
            y: 7
            color: "#ffffff"
            text: qsTr("W")
            font.pixelSize: 25
        }

        Text {
            id: batteryV
            x: (net.width - width) / 2
            y: 44
            color: "#ffffff"
            text: backEnd.batteryVoltage.toFixed(1)
            font.pixelSize: 36
        }

        Text {
            id: text5
            x: 312
            y: 51
            color: "#ffffff"
            text: qsTr("V")
            font.pixelSize: 25
        }

        Text {
            id: batteryI
            x: (net.width - width) / 2
            y: 88
            color: "#ffffff"
            text: backEnd.batteryCurrent.toFixed(1)
            font.pixelSize: 36
        }

        Text {
            id: text6
            x: 312
            y: 95
            color: "#ffffff"
            text: qsTr("A")
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
        border.color: "#ffffff"
        Text {
            id: text7
            x: 30
            y: 46
            color: "#ffffff"
            text: qsTr("Motor")
            font.pixelSize: 32
        }

        Text {
            id: motorP
            x: (motor.width - width) / 2
            y: 43
            color: "#ffffff"
            text: backEnd.motorPower.toFixed(1)
            font.pixelSize: 40
        }

        Text {
            id: text8
            x: 308
            y: 52
            color: "#ffffff"
            text: qsTr("W")
            font.pixelSize: 25
        }
    }
}
