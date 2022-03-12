/*import QtQuick 2.4

SpeedForm {

}*/

import QtQuick 2.15

Item {
    id: speedBox
    width: 400
    height: 400
    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 400
        color: "#000000"
        border.color: "#000000"

        Text {
            id: text1
            x: (speedBox.width - width) / 2
            y: (speedBox.height - height) / 2
            color: "#ffffff"
            text: backEnd.speed
            font.pixelSize: 150
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            scale: 1.477
        }

        Text {
            id: text2
            x: 160
            y: 295
            width: 80
            height: 59
            color: "#ffffff"
            text: qsTr("mph")
            font.pixelSize: 40
        }

        Rectangle {
            id: genRect
            x: 0
            y: 200
            width: 10
            height: 100
            color: "green"
            //property int prevSpeed: prevSpeed
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
                            startAngle: 180 + (genRect.prevSpeed/100)*180
                            sweepAngle: ((genRect.speed-genRect.prevSpeed)/100)*180
                        }
                    }
                }
            }
        }
    }
}
