import QtQuick 2.15

Item {
    width: 585
    height: 600
    visible: true
    z: 0

    function threshold(val, min, max) {
        if(val <= max && val >= min) {
            return "#000000"
        }
        else {
            return "#bbbb00"
        }
    }



    Rectangle {
        id: battery
        x: 0
        y: 0
        width: 585
        height: 375
        color: "#000000"
        border.color: "#ffffff"
        z: 0

        Rectangle {
            x: 0
            y: 0
            width: 585
            height: 62
            color: "#40ffffff"
            border.width: 0

            Text {
                x: 0
                y: 0
                width: 585
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
            x: 295
            y: 108
            width: 200
            height: 70
            color: "#ffffff"
            text: (backEnd.pack_voltage * backEnd.pack_current).toFixed(1)
            font.pixelSize: 72
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Rectangle {
            id: rectangle
            x: 0
            y: 225
            width: 585
            height: 150
            color: "#000000"
            border.color: "#ffffff"
            z: 0
        }

        Text {
            id: packVoltage
            x: 25
            y: 69
            width: 160
            height: 70
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
            x: 25
            y: 147
            width: 160
            height: 70
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
            x: 510
            y: 118
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
            x: 200
            y: 79
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
            x: 200
            y: 157
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

        Text {
            id: packTemp
            x: 39
            y: 280
            width: 150
            height: 70
            color: "#ffffff"
            text: backEnd.pack_temp.toFixed(1)
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 204
            y: 290
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
            x: 62
            y: 230
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
            x: 354
            y: 230
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
            x: 407
            y: 280
            width: 64
            height: 70
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
            id: voltrect
            x: 1
            y: 62
            width: 268
            height: 81
            color: threshold(packVoltage.text, minimum.pack_voltage, maximum.pack_voltage)
            rotation: 0
            z: 0
        }

        Rectangle {
            id: amprect
            x: 1
            y: 144
            width: 268
            height: 81
            color: threshold(packCurrent.text, minimum.pack_current, maximum.pack_current)
            z: 0
        }

        Rectangle {
            id: wattrect
            x: 269
            y: 62
            width: 315
            height: 163
            color: threshold(packPower.text, minimum.pack_current*minimum.pack_voltage, maximum.pack_current*maximum.pack_voltage)
            z: 0
        }

        Rectangle {
            id: packtmprect
            x: 1
            y: 227
            width: 292
            height: 148
            color: threshold(packTemp.text, minimum.pack_temp, maximum.pack_temp)
            z: 0
        }

        Rectangle {
            id: fanspeedrect
            x: 293
            y: 227
            width: 291
            height: 148
            color: threshold(fanSpeed.text, (backEnd.pack_temp < 50) ? Math.floor(((backEnd.pack_temp >= 20) ? (backEnd.pack_temp - 15) : 0) / 5) : 6, 6)
            z: 0
        }
    }

    Rectangle {
        id: solar
        x: 0
        y: 375
        width: 585
        height: 225
        color: "#000000"
        border.color: "#ffffff"

        Rectangle {
            x: 0
            y: 0
            width: 585
            height: 62
            color: "#40ffffff"
            border.width: 0
            Text {
                x: 0
                y: 0
                width: 585
                height: 62
                color: "#ffffff"
                text: qsTr("Solar")
                font.pixelSize: 48
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }
        }

        Text {
            id: solarPower
            x: 295
            y: 108
            width: 200
            height: 70
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
            id: solarVoltage
            x: 25
            y: 69
            width: 160
            height: 70
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
            id: solarCurrent
            x: 25
            y: 147
            width: 160
            height: 70
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
            x: 510
            y: 118
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
            x: 200
            y: 79
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
            x: 200
            y: 157
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
            id: svoltrect
            x: 1
            y: 62
            width: 268
            height: 81
            color: threshold(solarVoltage.text, minimum.pack_voltage, maximum.pack_voltage)
            rotation: 0
            z: 0
        }

        Rectangle {
            id: samprect1
            x: 1
            y: 142
            width: 268
            height: 81
            color: threshold(solarCurrent.text, minimum.mppt_current_out, maximum.mppt_current_out)
            z: 0
        }

        Rectangle {
            id: swattrect1
            x: 269
            y: 62
            width: 315
            height: 162
            color: threshold(solarPower.text, minimum.mppt_current_out*minimum.pack_voltage, maximum.mppt_current_out*maximum.pack_voltage)
            z: 0
        }
    }
}
