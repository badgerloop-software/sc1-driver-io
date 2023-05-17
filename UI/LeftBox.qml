import QtQuick 2.0

Item {
    width: 350
    height: 606
    visible: true

    function green(b) {
        return b ? "#40C321" : "#FFFFFF"
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

        Text {
            x: 0
            y: 62
            width: 350
            height: 100
            color: green((backEnd.pack_voltage * backEnd.pack_current) < 4320)
            text: (backEnd.pack_voltage * backEnd.pack_current).toFixed(1)
            font.pixelSize: 48
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }

        Text {
            x: 0
            y: 162
            width: 350
            height: 100
            color: green((backEnd.pack_voltage * backEnd.pack_current) < 4320)
            text: (backEnd.pack_voltage * backEnd.pack_current).toFixed(1)
            font.pixelSize: 48
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }

        Text {
            x: 276
            y: 62
            width: 50
            height: 100
            color: "#ffffff"
            text: qsTr("w")
            font.pixelSize: 42
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            z: 1
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 276
            y: 162
            width: 50
            height: 100
            color: "#ffffff"
            text: qsTr("w")
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
        x: 0
        y: 262
        width: 350
        height: 182
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
                text: qsTr("Cruise Speed")
                font.pixelSize: 48
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Work Sans"
                font.styleName: "Medium"
            }
        }

        Text {
            x: 0
            y: 162
            width: 350
            height: 100
            color: green((backEnd.pack_voltage * backEnd.pack_current) < 4320)
            text: (backEnd.pack_voltage * backEnd.pack_current).toFixed(1)
            font.pixelSize: 48
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }
    }
}
