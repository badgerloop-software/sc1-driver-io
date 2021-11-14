import QtQuick 2.4

Item {
    id: cruise
    x: -380
    y: -200
    width: 1280
    height: 720
    scale: 0.4

    Text {
        id: time
        x: 1104
        y: 37
        width: 85
        height: 41
        text: qsTr("00:00:00")
        font.pixelSize: 30
    }

    Text {
        id: alerts
        x: 591
        y: 42
        text: qsTr("No Altert")
        font.pixelSize: 30
    }

    Text {
        id: text1
        x: 1105
        y: 278
        text: qsTr("Solar")
        font.pixelSize: 16
    }

    Text {
        id: solarwattage
        x: 1161
        y: 268
        text: qsTr("0W")
        font.pixelSize: 30
    }

    Text {
        id: text2
        x: 1105
        y: 318
        text: qsTr("Motor")
        font.pixelSize: 16
    }

    Text {
        id: motorwattage
        x: 1159
        y: 310
        text: qsTr("0W")
        font.pixelSize: 30
    }

    Text {
        id: text3
        x: 1104
        y: 357
        text: qsTr("Net")
        font.pixelSize: 16
    }

    Text {
        id: motorwattage1
        x: 1159
        y: 352
        text: qsTr("0W")
        font.pixelSize: 30
    }

    Text {
        id: text4
        x: 526
        y: 615
        width: 41
        height: 16
        text: qsTr("Temp 1")
        font.pixelSize: 12
    }

    Text {
        id: text5
        x: 625
        y: 615
        width: 47
        height: 16
        text: qsTr("Temp 2")
        font.pixelSize: 12
    }

    Text {
        id: text6
        x: 729
        y: 615
        width: 47
        height: 16
        text: qsTr("Temp 3")
        font.pixelSize: 12
    }

    Text {
        id: temp1
        x: 527
        y: 637
        text: qsTr("0℃")
        font.pixelSize: 30
    }

    Text {
        id: temp2
        x: 625
        y: 637
        text: qsTr("0℃")
        font.pixelSize: 30
    }

    Text {
        id: temp3
        x: 729
        y: 637
        text: qsTr("0℃")
        font.pixelSize: 30
    }

    Text {
        id: text7
        x: 522
        y: 302
        width: 150
        height: 86
        font.pixelSize: 12

        Text {
            id: speedometer
            x: 67
            y: 25
            text: qsTr("0 mph")
            font.pixelSize: 30
        }

        Text {
            id: speedometer1
            x: 61
            y: 67
            text: qsTr("0 miles left")
            font.pixelSize: 20
        }

        AnimatedImage {
            id: analogspeed
            x: -61
            y: -126
            width: 373
            height: 353
            source: "qrc:/qtquickplugin/images/template_image.png"
        }
    }

    Text {
        id: text8
        x: 117
        y: 460
        text: qsTr("100%")
        font.pixelSize: 30
    }

    AnimatedImage {
        id: animatedImage
        x: 274
        y: 100
        width: 43
        height: 43
        source: "Images/cruiseControl.png"
    }

    Image {
        id: image
        x: 97
        y: 128
        width: 95
        height: 401
        source: "qrc:/Images/Battery.png"
        fillMode: Image.PreserveAspectFit
    }
}
