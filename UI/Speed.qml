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
        height: 802
        source: "Images/Masked SpeedometerNo Numbers.svg"
        smooth: true
        fillMode: Image.PreserveAspectFit

        Text {
            id: speed
            x: 269
            y: 305
            width: 337
            height: 168
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
            x: 355
            y: 488
            width: 166
            height: 166
            color: "#ffffff"
            text: backEnd.state === "C" ? "D" : qsTr(backEnd.state)
            font.pixelSize: 142
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Regular"
            font.family: "Work Sans"
        }

        Text {
            x: 166
            y: 629
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("0")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 94
            y: 485
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("10")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 94
            y: 323
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("20")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 178
            y: 179
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("30")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 296
            y: 96
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("40")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 478
            y: 96
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("50")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 597
            y: 179
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("60")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 680
            y: 323
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("70")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 680
            y: 485
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("80")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 597
            y: 629
            width: 100
            height: 67
            color: "#ffffff"
            text: qsTr("90")
            font.pixelSize: 65
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "SemiBold"
        }

        Text {
            x: 338
            y: 233
            width: 200
            height: 67
            color: "#ffffff"
            text: qsTr("MPH")
            font.pixelSize: 54
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Image {
            id: needle
            x: 30
            y: 423
            width: 188
            height: 29
            source: "Images/Needle (More Fade).svg"
            sourceSize.width: 188
            sourceSize.height: 31
            smooth: true
            clip: false
            fillMode: Image.PreserveAspectFit

            property real prevSpeed: 0
            property real newSpeed: 0

            Connections {
                target: backEnd
                function onDataChanged() {
                    needle.prevSpeed = needle.newSpeed
                    needle.newSpeed = displaySpeed
                }
            }

            Behavior on newSpeed {
                PathAnimation {
                    id: arcPath
                    target: needle
                    anchorPoint: Qt.point(0, 14.5)
                    orientation: (displaySpeed - needle.prevSpeed >= 0) ? PathAnimation.TopFirst : PathAnimation.BottomFirst;
                    duration: refreshTime
                    path: Path {
                        PathAngleArc {
                            centerX: 437.5
                            centerY: 437.5
                            radiusX: 407.5
                            radiusY: 407.5
                            startAngle: 135 + (needle.prevSpeed/90)*270
                            sweepAngle: ((displaySpeed-needle.prevSpeed)/90)*270
                        }
                    }
                }
            }
        }

        Image {
            id: crzNeedle
            x: 30
            y: 423
            width: 188
            height: 29
            source: "Images/Cruise Needle (More Fade).svg"
            sourceSize.width: 188
            sourceSize.height: 31
            smooth: true
            clip: false
            fillMode: Image.PreserveAspectFit
            visible: backEnd.crz_spd_mode && backEnd.state === "C"

            property real prevCrzSpeed: 0
            property real newCrzSpeed: 0

            Connections {
                target: backEnd
                function onDataChanged() {
                    crzNeedle.prevCrzSpeed = crzNeedle.newCrzSpeed
                    crzNeedle.newCrzSpeed = crzDisplaySpeed
                }
            }

            Behavior on newCrzSpeed {
                PathAnimation {
                    id: crzArcPath
                    target: crzNeedle
                    anchorPoint: Qt.point(0, 14.5)
                    orientation: (crzDisplaySpeed - crzNeedle.prevCrzSpeed >= 0) ? PathAnimation.TopFirst : PathAnimation.BottomFirst;
                    duration: refreshTime
                    path: Path {
                        PathAngleArc {
                            centerX: 437.5
                            centerY: 437.5
                            radiusX: 407.5
                            radiusY: 407.5
                            startAngle: 135 + (crzNeedle.prevCrzSpeed/90)*270
                            sweepAngle: ((crzDisplaySpeed-crzNeedle.prevCrzSpeed)/90)*270
                        }
                    }
                }
            }
        }

        Accelerator {
            id: accelerator
            x: 257
            y: 710
        }

        Text {
            x: 303
            y: 665
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
            y: 750
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
            y: 750
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
