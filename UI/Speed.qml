/*import QtQuick 2.4

SpeedForm {

}*/

import QtQuick 2.15
import QtQuick.Studio.Components 1.0
import QtQuick.Shapes 1.0

Item {
    id: speedBox
    width: 875
    height: 802

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
            text: qsTr("15")
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
            text: qsTr("D")
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


}

/*Rectangle {
    id: genRect
    //x: 0
    //y: 200
    width: 10
    height: 100
    color: "#00fcff"
    property int prevSpeed: 0
    property int newSpeed: 0
    property int speed: backEnd.speed

    onSpeedChanged: {
        prevSpeed = newSpeed
        newSpeed = speed
    }

    //rotation: backEnd.speed
    Behavior on newSpeed {
        PathAnimation {
            id: arcPath
            target: genRect
            anchorPoint: Qt.point(5, 50)
            orientation: PathAnimation.RightFirst
            duration: 1000
            path: Path {
                PathAngleArc {
                    centerX: 200
                    centerY: 200
                    radiusX: 200
                    radiusY: 200
                    startAngle: 135 + (genRect.prevSpeed/100)*270
                    sweepAngle: ((genRect.speed-genRect.prevSpeed)/100)*270
                }
            }
        }
    }
}*/

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:2}D{i:3}D{i:4}D{i:5}D{i:6}D{i:7}D{i:8}D{i:9}D{i:10}
D{i:11}D{i:12}D{i:13}D{i:14}D{i:15}D{i:16}D{i:17}D{i:18}D{i:19}D{i:1}
}
##^##*/
