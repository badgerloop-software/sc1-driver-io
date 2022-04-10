import QtQuick 2.4

Item {
    width: 304
    height: 875
    visible: true
    id: bat

    function getColor(num){
        if (num > 60) {
            return "#00ff00"
        }
        if (num > 20) {
            return "#ffff00"
        }
        return "#ff0000"
    }

    function getOpacity(num) {
        if(num<20)
            return 1
        return 0
    }


    Rectangle {
        id: batteryLevel
        x: 40
        y: 550
        width: 220
        height: 715*backEnd.soc/100
        color: getColor(backEnd.soc)
        anchors.bottom: battery.top
        anchors.bottomMargin: -735
        transformOrigin: Item.Center
    }

    Image {
        id: exclamation
        x: (bat.width-width)/2
        y: (bat.height-height)/2-50
        z: 1
        source: "Images/Exclamation.png"
        opacity: getOpacity(backEnd.soc)
        scale: 1.5
        fillMode: Image.PreserveAspectFit
        sourceSize.width: 150
        sourceSize.height: 104
    }


    Item {
        id: battery
        x: 25
        y: 5
        width: 250
        height: 755

        Rectangle {
            id: rectangle20
            x: 0
            y: 0
            width: 60
            height: 40
            color: "#000000"
        }

        Rectangle {
            id: rectangle21
            x: 190
            y: 0
            width: 60
            height: 40
            color: "#000000"
        }

        Rectangle {
            id: rectangle
            x: 50
            y: 0
            width: 150
            height: 20
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle1
            x: 50
            y: 0
            width: 20
            height: 50
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle2
            x: 180
            y: 0
            width: 20
            height: 50
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle3
            x: 180
            y: 30
            width: 70
            height: 20
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle4
            x: 0
            y: 30
            width: 70
            height: 20
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle5
            x: 0
            y: 30
            width: 20
            height: 725
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle6
            x: 230
            y: 30
            width: 20
            height: 725
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle7
            x: 0
            y: 735
            width: 250
            height: 20
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle8
            x: 5
            y: 735
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle9
            x: 5
            y: 88
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle10
            x: 5
            y: 376
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle11
            x: 5
            y: 304
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle12
            x: 5
            y: 232
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle13
            x: 5
            y: 519
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle14
            x: 5
            y: 591
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle15
            x: 5
            y: 447
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle16
            x: 5
            y: 160
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle17
            x: 5
            y: 663
            width: 240
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle18
            x: 55
            y: 16
            width: 140
            height: 4
            color: "#ffffff"
            radius: 0
        }
    }

    Text {
        id: charge
        x: 4
        y: 760
        width: 246
        height: 100
        color: "#ffffff"
        text: backEnd.soc.toFixed(1)
        font.pixelSize: 96
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Regular"
        font.family: "Work Sans"
    }

    Text {
        x: 250
        y: 785
        width: 50
        height: 50
        color: "#ffffff"
        text: qsTr("%")
        font.pixelSize: 60
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Work Sans"
        font.styleName: "Regular"
    }
}
