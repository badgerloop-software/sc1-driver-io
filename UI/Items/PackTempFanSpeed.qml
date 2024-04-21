import QtQuick 2.4

Item {
    id: pack_temp_fan_speed
    width: 223
    height: 303


    function getColor(temp){
        if(temp <= 100) {
            return "#000000"
        }
        else {
            return "#bbbb00"
        }
    }

    Rectangle {
        id: pack_temp
        x: 0
        y: 0
        width: 225
        height: 150
        color: "#000000"
        border.width: 0

        Text {
            x: 0
            y: 0
            width: 225
            height: 50
            color: "#ffffff"
            text: qsTr("Pack Temp")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: packTemp
            x: 10
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: backEnd.pack_temp.toFixed(1)
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 165
            y: 63
            width: 50
            color: "#ffffff"
            text: "°C"
            font.pixelSize: 42
            font.styleName: "Regular"
            font.family: "Work Sans"
        }
    }

    Rectangle {
        id: fan_speed
        x: 0
        y: 150
        width: 225
        height: 100
        color: "#000000"
        border.width: 0

        Text {
            x: 0
            y: 0
            width: 225
            height: 50
            color: "#ffffff"
            text: qsTr("Fan Speed")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Regular"
            font.family: "Work Sans"
        }

        Text {
            id: fanSpeed
            x: 38
            y: 56
            width: 150
            height: 75
            color: "#ffffff"
            text: backEnd.fan_speed
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }
    }
}
