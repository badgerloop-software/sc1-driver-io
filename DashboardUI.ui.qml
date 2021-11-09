import QtQuick 2.4

Item {
    width: 800
    height: 600

    Text {
        id: time
        x: 625
        y: 41
        width: 85
        height: 28
        text: qsTr("00:00:00")
        font.pixelSize: 30
    }

    Text {
        id: alerts
        x: 343
        y: 37
        text: qsTr("No Altert")
        font.pixelSize: 30
    }

    Text {
        id: text1
        x: 646
        y: 231
        text: qsTr("Solar")
        font.pixelSize: 16
    }

    Text {
        id: solarwattage
        x: 702
        y: 221
        text: qsTr("0W")
        font.pixelSize: 30
    }

    Text {
        id: text2
        x: 646
        y: 271
        text: qsTr("Motor")
        font.pixelSize: 16
    }

    Text {
        id: motorwattage
        x: 700
        y: 263
        text: qsTr("0W")
        font.pixelSize: 30
    }

    Text {
        id: text3
        x: 645
        y: 310
        text: qsTr("Net")
        font.pixelSize: 16
    }

    Text {
        id: motorwattage1
        x: 700
        y: 305
        text: qsTr("0W")
        font.pixelSize: 30
    }

    Text {
        id: text4
        x: 248
        y: 500
        width: 41
        height: 16
        text: qsTr("Temp 1")
        font.pixelSize: 12
    }

    Text {
        id: text5
        x: 347
        y: 500
        width: 47
        height: 16
        text: qsTr("Temp 2")
        font.pixelSize: 12
    }

    Text {
        id: text6
        x: 451
        y: 500
        width: 47
        height: 16
        text: qsTr("Temp 3")
        font.pixelSize: 12
    }

    Text {
        id: temp1
        x: 249
        y: 522
        text: qsTr("0℃")
        font.pixelSize: 30
    }

    Text {
        id: temp2
        x: 347
        y: 522
        text: qsTr("0℃")
        font.pixelSize: 30
    }

    Text {
        id: temp3
        x: 451
        y: 522
        text: qsTr("0℃")
        font.pixelSize: 30
    }

    Text {
        id: text7
        x: 296
        y: 243
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

    MouseArea {
        id: mouseArea
        x: 137
        y: 101
        width: 64
        height: 58
    }

    Rectangle {
        id: cruise
        x: 143
        y: 108
        width: 61
        height: 49
        color: "#e44b4b"
        Text {
            id: text100
            text: qsTr("cruise button")
        }
    }

    Text {
        id: text8
        x: 40
        y: 522
        text: qsTr("100%")
        font.pixelSize: 30
    }

    AnimatedImage {
        id: animatedImage
        x: 44
        y: 153
        width: 87
        height: 334
        source: "qrc:/qtquickplugin/images/template_image.png"
    }
}
