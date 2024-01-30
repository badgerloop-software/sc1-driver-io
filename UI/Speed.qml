import QtQuick 2.15

Item {
    id: speedBox
    width: 800
    height: 950

    property real displaySpeed: 0
    property real crzDisplaySpeed: 0
    property int refreshTime: 500
    property int crzRefreshTime: 100

    function updateSpeed() {
        displaySpeed = backEnd.speed;
    }

    function updateCrzSpeed() {
        crzDisplaySpeed = backEnd.crz_spd_setpt;
    }

    Item {
        id: speedometer
        x: 0
        y: 0
        width: 800
        height: 950

        Text {
            id: speed
            x: 420
            y: 106
            width: 337
            height: 168
            color: "#ffffff"
            text: displaySpeed.toFixed(1)
            font.pixelSize: 156
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: mph
            x: 514
            y: 281
            width: 150
            height: 55
            color: "#ffffff"
            text: "MPH"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: stateText
            x: 317
            y: 267
            width: 166
            height: 82
            color: "#ffffff"
            text: backEnd.state === "C" ? "D" : qsTr(backEnd.state)
            font.pixelSize: 76
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Medium"
            font.family: "Work Sans"
        }

        Text {
            id: power
            x: 46
            y: 106
            width: 337
            height: 168
            color: "#ffffff"
            text: ((backEnd.pack_voltage * backEnd.pack_current) / 1000).toFixed(1)
            font.pixelSize: 156
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: kw
            x: 140
            y: 281
            width: 150
            height: 55
            color: "#ffffff"
            text: "KW"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Rectangle {
            x: 130
            y: 341
            width: 540
            height: 2
            color: "#ffffff"
        }

        Accelerator {
            id: accelerator
            x: 219
            y: 757
        }

        Text {
            x: 265
            y: 712
            width: 270
            height: 40
            color: "#ffffff"
            text: qsTr("Accelerator")
            font.pixelSize: 33
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: kw1
            x: 168
            y: 433
            width: 150
            height: 55
            color: "#ffffff"
            text: "KW"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: mph1
            x: 497
            y: 433
            width: 150
            height: 55
            color: "#ffffff"
            text: "MPH"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }
    }

    Timer {
        interval: refreshTime; running: true; repeat: true
        onTriggered: updateSpeed();
    }

    Timer {
        interval: crzRefreshTime; running: true; repeat: true
        onTriggered: updateCrzSpeed();
    }

}
