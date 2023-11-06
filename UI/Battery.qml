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
        if(num<5)
            return 1
        return 0
    }


    Rectangle {
        id: batteryLevel
        x: 35
        y: 355
        width: 120
        height: 390*backEnd.soc/100
        color: getColor(backEnd.soc)
        anchors.bottom: battery.top
        anchors.bottomMargin: -600
        transformOrigin: Item.Center
    }

    Image {
        id: exclamation
        x: 60
        y: 260
        z: 1
        source: "Images/Exclamation.png"
        opacity: getOpacity(backEnd.soc)
        scale: 1
        fillMode: Image.PreserveAspectFit
        sourceSize.width: 75
        sourceSize.height: 104
    }


    Item {
        id: battery
        x: 25
        y: 5
        width: 250
        height: 755

        //top border
        Rectangle {
            id: rectangle10
            x: 33
            y: 215
            width: 70
            height: 30
            color: "#ffffff"
            radius: 10
        }

        //top border
        Rectangle {
            id: rectangle9
            x: 2
            y: 235
            width: 130
            height: 10
            color: "#ffffff"
            radius: 10
        }

           //Long border left
        Rectangle {
            id: rectangle5
            x: 0
            y: 235
            width: 10
            height: 363
            color: "#ffffff"
            radius: 10
        }

        //Long border right
        Rectangle {
            id: rectangle6
            x: 125
            y: 235
            width: 10
            height: 363
            color: "#ffffff"
            radius: 10
        }

        //bottom border
        Rectangle {
            id: rectangle7
            x: 2
            y: 590
            width: 130
            height: 10
            color: "#ffffff"
            radius: 10
        }

        Rectangle {
            id: rectangle16
            x: 5
            y: 578
            width: 120
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle2
            x: 5
            y: 528
            width: 120
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle17
            x: 5
            y: 478
            width: 120
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle21
            x: 5
            y: 428
            width: 120
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle18
            x: 5
            y: 378
            width: 120
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle19
            x: 5
            y: 328
            width: 120
            height: 4
            color: "#ffffff"
            radius: 0
        }

        Rectangle {
            id: rectangle20
            x: 5
            y: 278
            width: 120
            height: 4
            color: "#ffffff"
            radius: 0
        }

    }

    Text {
        id: charge
        x: 0
        y: 600
        width: 166
        height: 100
        color: "#ffffff"
        text: backEnd.soc.toFixed(1)
        font.pixelSize: 82
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Regular"
        font.family: "Work Sans"
    }

    Text {
        x: 190
        y: 630
        width: 50
        height: 50
        color: "#ffffff"
        text: qsTr("%")
        font.pixelSize: 64
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Work Sans"
        font.styleName: "Regular"
    }
}
