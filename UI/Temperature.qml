import QtQuick 2.4

Item {
    id: temperature
    width: 900
    height: 150


    function getColor(temp){
        if(temp <= 100) {
            return "#000000"
        }
        else {
            return "#bbbb00"
        }
    }

    Rectangle {
        id: motor
        x: 0
        y: 0
        width: 225
        height: 150
        color: getColor(backEnd.motor_temp)
        border.width: 0
        Text {
            x: 0
            y: 0
            width: 225
            height: 50
            color: "#ffffff"
            text: qsTr("Motor")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: motorTemp
            x: 10
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: backEnd.motor_temp.toFixed(1)
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
        id: driverio
        x: 225
        y: 0
        width: 225
        height: 150
        color: getColor(backEnd.driverIO_temp)
        border.width: 0

        Text {
            x: 0
            y: 0
            width: 225
            height: 50
            color: "#ffffff"
            text: qsTr("Driver IO")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Regular"
            font.family: "Work Sans"
        }

        Text {
            id: driverioTemp
            x: 10
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: backEnd.driverIO_temp.toFixed(1)
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
        id: mainio
        x: 450
        y: 0
        width: 225
        height: 150
        color: getColor(backEnd.mainIO_temp)
        border.width: 0
        Text {
            x: 0
            y: 0
            width: 225
            height: 50
            color: "#ffffff"
            text: qsTr("Main IO")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: mainioTemp
            x: 10
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: backEnd.mainIO_temp.toFixed(1)
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
            font.family: "Work Sans"
            font.styleName: "Regular"
        }
    }

    Rectangle {
        id: cabin
        x: 675
        y: 0
        width: 225
        height: 150
        color: getColor(backEnd.cabin_temp)
        border.width: 0
        Text {
            x: 0
            y: 0
            width: 225
            height: 50
            color: "#ffffff"
            text: qsTr("Cabin")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: cabinTemp
            x: 10
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: backEnd.cabin_temp.toFixed(1)
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
            font.family: "Work Sans"
            font.styleName: "Regular"
        }
    }
}
