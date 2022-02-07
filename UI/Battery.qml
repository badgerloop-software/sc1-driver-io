import QtQuick 2.4

Item {
    width: 400
    height: 800
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

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 800
        color: "#000000"
        border.color: "#000000"

        Text {
            id: batVal
            x: (bat.width - width) / 2
            y: 640
            color: "#ffffff"
            text: backEnd.soc.toFixed(1)
            font.pixelSize: 60
        }


        Rectangle {
            id: batLevel
            x: 100
            y: 605 - height
            width: 200
            height: 530 * ( batVal.text / 100)
            color: getColor(backEnd.soc)
            border.color: "#000000"
        }


        Image {
            id: image
            x: 58
            y: 37
            width: 285
            height: 597
            source: "Images/Battery.png"
            fillMode: Image.PreserveAspectFit
        }
        Text {
            id: text1
            x: 188
            y: 708
            color: "#ffffff"
            text: qsTr("%")
            font.pixelSize: 30
            z: 1
        }
    }
}
