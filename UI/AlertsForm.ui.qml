import QtQuick 2.4

Item {
    id: alerts
    width: 800
    height: 200

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 800
        height: 200
        color: "#000000"

        Text {
            id: alertTxt
            x: (alerts.width - width) / 2
            y: (alerts.height - height) / 2
            color: "#ffffff"
            text: qsTr("Alerts")
            font.pixelSize: 50
        }
    }
}
