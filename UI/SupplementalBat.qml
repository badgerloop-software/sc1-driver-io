import QtQuick 2.4

Item {
    id: supbat
    width: 558
    height: 75
    visible: true

    function getColor(num){
        if (num > 60) {
            return "#00ff00"
        }
        if (num > 20) {
            return "#ffff00"
        }
        return "#ff0000"
    }

    Rectangle {
        id: batteryLevel
        x: 0
        y: 5
        width: 280*backEnd.est_supplemental_soc/100
        height: 60
        color: getColor(backEnd.est_supplemental_soc)
        anchors.right: battery.right
        anchors.rightMargin: 14
        transformOrigin: Item.Center
    }

    Image {
        id: battery
        x: 0
        y: 3
        width: 304
        height: 67
        source: "Images/Supplemental SoC.svg"
    }

    Text {
        id: charge
        x: 324
        y: 0
        width: 184
        height: 75
        color: "#ffffff"
        text: backEnd.est_supplemental_soc.toFixed(1)
        font.pixelSize: 72
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Regular"
        font.family: "Work Sans"
    }

    Text {
        x: 490
        y: 12
        width: 50
        height: 50
        color: "#ffffff"
        text: qsTr("%")
        font.pixelSize: 60
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Work Sans"
        font.styleName: "Regular"
    }
}
