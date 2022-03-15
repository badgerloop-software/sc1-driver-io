import QtQuick 2.4

Item {
    id: temp
    width: 750
    height: 150

    Rectangle {
        id: driverio
        x: 0
        y: 0
        width: 250
        height: 150
        color: "#000000"
        border.width: 0

        Text {
            x: 0
            y: 0
            width: 250
            height: 50
            color: "#ffffff"
            text: qsTr("Driver IO Board")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Regular"
            font.family: "Work Sans"
        }

        Text {
            id: driverioTemp
            x: 20
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: qsTr("50.5")
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 180
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
        x: 250
        y: 0
        width: 250
        height: 150
        color: "#000000"
        border.width: 0
        Text {
            x: 0
            y: 0
            width: 250
            height: 50
            color: "#ffffff"
            text: qsTr("Main IO Board")
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: mainioTemp
            x: 20
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: qsTr("50.5")
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 180
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
        x: 500
        y: 0
        width: 250
        height: 150
        color: "#000000"
        border.width: 0
        Text {
            x: 0
            y: 0
            width: 250
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
            x: 20
            y: 50
            width: 150
            height: 75
            color: "#ffffff"
            text: qsTr("50.5")
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 180
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

/*function colour(num){
    if(num<100){
        return "#000000"
    }
    else{
        return "#bbbb00"
    }
}

Rectangle {
    id: rectangle
    x: 0
    y: 0
    width: 200
    height: 200
    color: colour(temp1.text)

    Text {
        id: text1
        //x: 68
        x: (rectangle.width - width) / 2
        y: 33
        color: "#ffffff"
        text: qsTr("Battery Pack")
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
        text: backEnd.pack_temp.toFixed(1)
        font.pixelSize: 50
    }
}

Rectangle {
    id: rectangle1
    x: 200
    y: 0
    width: 200
    height: 200
    color: colour(temp2.text)
    Text {
        id: text3
        //x: 68
        x: (rectangle1.width - width) / 2
        y: 33
        color: "#ffffff"
        text: qsTr("Motor")
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
        text: backEnd.motor_temp.toFixed(1)
        font.pixelSize: 50
    }
}

Rectangle {
    id: rectangle2
    x: 400
    y: 0
    width: 200
    height: 200
    color: colour(temp3.text)
    Text {
        id: text5
        //x: 68
        x: (rectangle2.width - width) / 2
        y: 33
        color: "#ffffff"
        text: qsTr("Motor Controller")
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
}*/

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:2}D{i:3}D{i:4}D{i:1}D{i:6}D{i:7}D{i:8}D{i:5}D{i:10}
D{i:11}D{i:12}D{i:9}
}
##^##*/
