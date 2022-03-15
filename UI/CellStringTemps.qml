import QtQuick 2.15

Item {
    width: 575
    height: 161

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
            text: qsTr("50.5")
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
            text: qsTr("50.5")
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
            text: qsTr("50.5")
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

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}D{i:2}D{i:3}D{i:4}D{i:1}D{i:6}D{i:7}D{i:8}D{i:5}D{i:10}
D{i:11}D{i:12}D{i:9}D{i:13}D{i:14}
}
##^##*/
