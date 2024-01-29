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
            x: 440
            y: 105
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
            x: 527
            y: 280
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
            x: 355
            y: 288
            width: 166
            height: 166
            color: "#ffffff"
            text: backEnd.state === "C" ? "D" : qsTr(backEnd.state)
            font.pixelSize: 112
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Medium"
            font.family: "Work Sans"
        }

        Text {
            id: power
            x: 100
            y: 105
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
            x: 195
            y: 280
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
            x: 173
            y: 340
            width: 540
            height: 2
            color: "#ffffff"
        }

        Accelerator {
            id: accelerator
            x: 257
            y: 760
        }

        Text {
            x: 303
            y: 715
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
