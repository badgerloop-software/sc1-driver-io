import QtQuick 2.4

Item {
    width: 875
    height: 104
    property bool blinkersOn: true


    Image {
        id: leftBlinker
        x: 0
        y: 0
        width: 150
        height: 104
        source: "Images/Blinker.png"
        rotation: 180
        fillMode: Image.PreserveAspectFit
        sourceSize.width: 150
        sourceSize.height: 104
    }

    Image {
        id: rightBlinker
        x: 725
        y: 0
        width: 150
        height: 104
        source: "Images/Blinker.png"
        sourceSize.height: 104
        sourceSize.width: 150
        fillMode: Image.PreserveAspectFit
    }

    Timer {
        interval: 500
        running: backEnd.left_turn || backEnd.right_turn || backEnd.hazards || blinkersOn
        repeat: true
        onTriggered: {
            blinkersOn = !blinkersOn;
            leftBlinker.visible = (backEnd.left_turn || backEnd.hazards) && blinkersOn;
            rightBlinker.visible = (backEnd.right_turn || backEnd.hazards) && blinkersOn;
        }
    }
}
