import QtQuick 2.4

Item {
    id: temp
    width: 600
    height: 200
    function colour(num){
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
            text: backEnd.batteryTemp.toFixed(1)
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
            text: backEnd.motorTemp.toFixed(1)
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
            text: backEnd.motorControllerTemp.toFixed(1)
            font.pixelSize: 50
        }
    }
}
