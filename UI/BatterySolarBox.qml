import QtQuick 2.15

Item {
    width: 301
    height: 869
    visible: true


    function threshold(val, min, max) {
        if(val <= max && val >= min) {
            return "#000000"
        }
        else {
            return "#bbbb00"
        }
    }


    Rectangle {
        id: solar
        x: 0
        y: 0
        z: 0
        width: 301
        height: 260
        color: "#000000"
        border.color: "#ffffff"

        Rectangle {
            x: 1
            y: 1
            width: 302
            height: 62
            color: "#40ffffff"
            border.width: 0
            Text {
                x: 0
                y: 0
                width: 301
                height: 62
                color: "#ffffff"
                text: qsTr("Solar Array")
                font.pixelSize: 48
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }
        }

        Text {
            id: solarPower
            x: 0
            y: 62
            width: 301
            height: (solar.height - 62) / 2
            color: "#ffffff"
            text: (backEnd.pack_voltage * backEnd.mppt_current_out).toFixed(1)
            font.pixelSize: 72
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: solarCurrent
            x: 0
            y: 62 + solarPower.height
            width: 301
            height: (solar.height - 62) / 2
            color: "#ffffff"
            text: backEnd.mppt_current_out.toFixed(1)
            font.pixelSize: 64
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 229
            y: 97
            width: 50
            height: 50
            color: "#ffffff"
            text: qsTr("W")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 229
            y: 175
            width: 50
            height: 50
            color: "#ffffff"
            text: qsTr("A")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Rectangle {
            id: samprect1
            x: solarCurrent.x +1
            y: solarCurrent.y
            width: solarCurrent.width -1
            height: solarCurrent.height
            color: threshold(solarCurrent.text, 0, 7)
            z: 0
        }

        Rectangle {
            id: swattrect1
            x: solarPower.x +1
            y: solarPower.y
            width: solarPower.width -1
            height: solarPower.height
            color: threshold(solarPower.text, 0, 756)
            z: 0
        }
    }

    Rectangle {
        id: battery
        x: 0
        y: 260
        width: 301
        height: 338
        color: "#000000"
        border.color: "#ffffff"
        z: 0

        Rectangle {
            x: 0
            y: 0
            width: 301
            height: 62
            color: "#40ffffff"
            border.width: 0

            Text {
                x: 0
                y: 0
                width: 301
                height: 62
                color: "#ffffff"
                text: qsTr("Battery")
                font.pixelSize: 48
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Medium"
                font.family: "Work Sans"
            }
        }

        Text {
            id: packPower
            x: 0
            y: 62
            width: 301
            height: (338 - 62) / 3
            color: "#ffffff"
            text: (backEnd.pack_voltage * backEnd.pack_current).toFixed(1)
            font.pixelSize: 72
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: packVoltage
            x: 0
            y:62 + packPower.height
            width: 301
            height: (338 - 62) / 3
            color: "#ffffff"
            text: backEnd.pack_voltage.toFixed(1)
            font.pixelSize: 64
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: packCurrent
            x: 0
            y:62 + packPower.height + packVoltage.height
            width: 301
            height: (338 - 62) / 3
            color: "#ffffff"
            text: backEnd.pack_current.toFixed(1)
            font.pixelSize: 64
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }


        Text {
            x: 229
            y: 97
            width: 50
            height: 50
            color: "#ffffff"
            text: qsTr("W")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 229
            y: 175
            width: 50
            height: 50
            color: "#ffffff"
            text: qsTr("V")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 229
            y: 253
            width: 50
            height: 50
            color: "#ffffff"
            text: qsTr("A")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Rectangle {
            id: voltrect
            x: packVoltage.x + 1
            y: packVoltage.y
            width: packVoltage.width - 1
            height: packVoltage.height
            color: threshold(packVoltage.text, 69, 108)
            rotation: 0
            z: 0
        }

        Rectangle {
            id: amprect
            x: packCurrent.x + 1
            y: packCurrent.y
            width: packCurrent.width - 1
            height: packCurrent.height
            color: threshold(packCurrent.text, 0, 100)
            z: 0
        }

        Rectangle {
            id: wattrect
            x: packPower.x + 1
            y: packPower.y
            width: packPower.width - 1
            height: packPower.width
            color: threshold(packPower.text, 0, 10800)
            z: 0
        }
    }

    Rectangle {
        id: tempFan
        x: 0
        y: 598
        width: 301
        height: 271
        color: "#000000"
        border.color: "#ffffff"
        z: 0

        Text {
            id: packTemp
            x: 150
            y: 60
            width: 0
            height: 0
            color: "#ffffff"
            text: backEnd.pack_temp.toFixed(1)
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignHCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 229
            y: 70
            width: 50
            height: 50
            color: "#ffffff"
            text: qsTr("°C")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 66
            y: 10
            width: 170
            height: 50
            color: "#ffffff"
            text: qsTr("Pack Temp")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 66
            y: 142
            width: 170
            height: 50
            color: "#ffffff"
            text: qsTr("Fan Speed")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: fanSpeed
            x: 150
            y: 220
            width: 0
            height: 0
            color: "#ffffff"
            text: backEnd.fan_speed
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Rectangle {
            id: packtmprect
            x: 1
            y: 1
            width: 300
            height: tempFan.height/2
            color: threshold(packTemp.text, 0, 60)
            z: 0
        }

        Rectangle {
            id: fanspeedrect
            x: 1
            y: packtmprect.height
            width: 300
            height: tempFan.height/2
            color: threshold(fanSpeed.text, (backEnd.pack_temp < 50) ? Math.floor(((backEnd.pack_temp >= 20) ? (backEnd.pack_temp - 15) : 0) / 5) : 6, 6)
            z: 0
        }
    }
}


