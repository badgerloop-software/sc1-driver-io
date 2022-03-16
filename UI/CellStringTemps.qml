import QtQuick 2.15

Item {
    width: 575
    height: 161


    function getColor(temp){
        if((temp >= 20) && (temp <= 50)){
            return "#000000"
        }
        else{
            return "#bbbb00"
        }
    }


    Rectangle {
        id: cellString2Background
        x: 288
        y: 3
        width: 284
        height: 155
        color: getColor(backEnd.string2_temp)
        border.width: 0
    }

    Image {
        id: cellString2
        x: 0
        y: 0
        width: 575
        height: 161
        source: "Images/Cell String 2 (No Number).png"
        sourceSize.width: 575
        sourceSize.height: 161
        fillMode: Image.PreserveAspectFit

        Text {
            x: 290
            y: 5
            width: 25
            height: 25
            visible: true
            color: "#ffffff"
            text: qsTr("2")
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "SemiBold"
            font.family: "Work Sans"
        }

        Text {
            id: string2Temp
            x: 389
            y: 46
            width: 143
            height: 67
            visible: true
            color: "#ffffff"
            text: backEnd.string2_temp.toFixed(1)
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }

        Text {
            x: 519
            y: 55
            width: 50
            height: 50
            visible: true
            color: "#ffffff"
            text: "°C"
            font.pixelSize: 36
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            textFormat: Text.RichText
            font.family: "Work Sans"
            font.styleName: "Regular"
        }
    }

    Rectangle {
        id: cellString3Background
        x: 3
        y: 3
        width: 284
        height: 79
        color: getColor(backEnd.string3_temp)
        border.width: 0
    }

    Image {
        id: cellString3
        x: 0
        y: 0
        width: 290
        height: 80
        source: "Images/Cell String 3 (No Number).png"
        sourceSize.height: 80
        sourceSize.width: 290
        fillMode: Image.PreserveAspectFit

        Text {
            x: 5
            y: 5
            width: 25
            height: 25
            visible: true
            color: "#ffffff"
            text: qsTr("3")
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            id: string3Temp
            x: 40
            y: 9
            width: 143
            height: 67
            visible: true
            color: "#ffffff"
            text: backEnd.string3_temp.toFixed(1)
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }

        Text {
            x: 183
            y: 17
            width: 50
            height: 50
            visible: true
            color: "#ffffff"
            text: "°C"
            font.pixelSize: 36
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
            textFormat: Text.RichText
        }
    }

    Rectangle {
        id: cellString1Background
        x: 5
        y: 83
        width: 387
        height: 73
        color: getColor(backEnd.string1_temp)
        border.width: 0
    }

    Image {
        id: cellString1
        x: 0
        y: 80
        width: 395
        height: 81
        source: "Images/Cell String 1 (No Number).png"
        sourceSize.height: 81
        sourceSize.width: 395
        fillMode: Image.PreserveAspectFit

        Text {
            x: 5
            y: 5
            width: 25
            height: 25
            visible: true
            color: "#ffffff"
            text: qsTr("1")
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            id: string1Temp
            x: 40
            y: 7
            width: 143
            height: 67
            visible: true
            color: "#ffffff"
            text: backEnd.string1_temp.toFixed(1)
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Medium"
        }

        Text {
            x: 183
            y: 17
            width: 50
            height: 50
            visible: true
            color: "#ffffff"
            text: "°C"
            font.pixelSize: 36
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
            textFormat: Text.RichText
        }
    }

    Rectangle {
        id: cellString1TopBoxBackground
        x: 258
        y: 53
        width: 29
        height: 32
        color: getColor(backEnd.string1_temp)
        border.width: 0
    }

    Image {
        id: cellString1TopBox
        x: 253
        y: 50
        width: 32
        height: 30
        source: "Images/Cell String 1 Top Box.png"
        sourceSize.height: 30
        sourceSize.width: 32
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: cabin
        x: 285
        y: 50
        width: 110
        height: 61
        source: "Images/Cabin.png"
        sourceSize.width: 110
        sourceSize.height: 61
        fillMode: Image.PreserveAspectFit
    }
}
