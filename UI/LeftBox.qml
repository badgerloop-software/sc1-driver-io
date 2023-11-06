import QtQuick 2.0

Item {
    width: 350
    height: 606
    visible: true

    function threshold(val, min, max) {
        if(val <= max && val >= min) {
            return "#000000"
        }
        else {
            return "#bbbb00"
        }
    }

    function cruiseGreen(b) {
        return (b && backEnd.state === "C") ? "#40C321" : "#FFFFFF"
    }

    Rectangle {
        id: motor
        x: 0
        y: 0
        width: 350
        height: 262
        color: "#000000"
        border.color: "#ffffff"

        Rectangle {
            x: 0
            y: 1
            width: 350
            height: 62
            color: "#40ffffff"

            Text {
                x: 0
                y: 0
                width: 350
                height: 62
                color: "#ffffff"
                text: qsTr("Motor")
                font.pixelSize: 48
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }
        }

        Rectangle {
            x: 1
            y: 62
            width: 348
            height: 100
            color: threshold(backEnd.pack_voltage * backEnd.pack_current, 0, 100)

            Text {
                x: 19
                y: 0
                width: 256
                height: 100
                color: "#ffffff"
                text: (backEnd.pack_voltage * backEnd.pack_current).toFixed(1)
                font.pixelSize: 64
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }

            Text {
                x: 275
                y: 0
                width: 50
                height: 100
                color: "#ffffff"
                text: qsTr("W")
                font.pixelSize: 42
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                z: 1
                font.family: "Work Sans"
                font.styleName: "Regular"
            }
        }


        Text {
            x: 20
            y: 162
            width: 256
            height: 100
            color: cruiseGreen(backEnd.crz_pwr_mode)
            text: backEnd.crz_pwr_setpt.toFixed(1)
            font.pixelSize: 64
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }

        Text {
            x: 276
            y: 162
            width: 50
            height: 100
            color: cruiseGreen(backEnd.crz_pwr_mode)
            text: qsTr("W")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }
    }

    Rectangle {
        id: cruiseSpeed
        x: 700
        y: 320
        width: 250
        height: 182
        color: "#00FFFFFF"
        border.color: "#00FFFFFF"

        Rectangle {
            x: 0
            y: 1
            width: 350
            height: 62
            color: "#00FFFFFF"

            Text {
                x: 120
                y: 40
                width: 450
                height: 150
                color: "#ffffff"
                text: qsTr("Cruise")
                font.pixelSize: 50
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }

            Text {
                x: 1
                y: 110
                width: 275
                height: 30
                color: "#ffffff"
                text: qsTr("MPH")
                font.pixelSize: 33
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }
        }

        Text {
            x: 1
            y: 40
            width: 300
            height: 50
            color: cruiseGreen(backEnd.crz_spd_mode)
            text: backEnd.crz_spd_setpt.toFixed(1)
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }

        Text {
            x: 250
            y: 36
            width: 50
            height: 120
            color: cruiseGreen(backEnd.crz_spd_mode)
            text: qsTr("")
            font.pixelSize: 35
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }
    }

    Rectangle {
        id: supplemental
        x: 0
        y: 262
        width: 350
        height: 162
        color: "#000000"
        border.color: "#ffffff"

        Rectangle {
            x: 0
            y: 1
            width: 350
            height: 62
            color: "#40ffffff"

            Text {
                x: 0
                y: 0
                width: 350
                height: 62
                color: "#ffffff"
                text: qsTr("Supplemental")
                font.pixelSize: 48
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }
        }

        Rectangle {
            x: 1
            y: 62
            width: 348
            height: 99
            color: threshold(backEnd.supplemental_voltage, 0, 100)

            Text {
                x: 0
                y: 0
                width: 348
                height: 100
                color: "#ffffff"
                text: backEnd.supplemental_voltage.toFixed(1)
                font.pixelSize: 64
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }

            Text {
                x: 275
                y: 0
                width: 50
                height: 100
                color: "#ffffff"
                text: qsTr("V")
                font.pixelSize: 42
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                z: 1
                font.family: "Work Sans"
                font.styleName: "Regular"
            }
        }
    }
}
