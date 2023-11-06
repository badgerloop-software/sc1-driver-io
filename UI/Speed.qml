import QtQuick 2.15

Item {
    id: speedBox
    width: 875
    height: 802

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

    Image {
        id: speedometer
        x: 0
        y: 0
        width: 875
        height: 602

        Text {
            id: speed
            x: 269
            y: 305
            width: 337
            height: 0
            color: "#ffffff"
            text: displaySpeed.toFixed(0)
            font.pixelSize: 238
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Medium"
            font.family: "Work Sans"
        }

        Text {
            id: stateText
            x: 555
            y: 340
            width: 166
            height: 166
            color: "#ffffff"
            text: backEnd.state === "C" ? "D" : qsTr(backEnd.state)
            font.pixelSize: 110
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Regular"
            font.family: "Work Sans"
        }

        Text {
            x: 338
            y: 233
            width: 200
            height: 420
            color: "#ffffff"
            text: qsTr("MPH")
            font.pixelSize: 49
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Image {

            property real prevSpeed: 0
            property real newSpeed: 0
        }

        Rectangle {
            id: rectangle
            x: 210
            y: 490
            width: 500
            height: 5
            color: "#ffffff"
            radius: 10
        }

        Accelerator {
            id: accelerator
            x: 257
            y: 810
        }

        Text {
            x: 303
            y: 765
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
            x: 237
            y: 850
            width: 50
            height: 44
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 33
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            x: 574
            y: 850
            width: 80
            height: 44
            color: "#ffffff"
            text: qsTr("100")
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
