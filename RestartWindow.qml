import QtQuick 2.0
import QtQuick.Window 2.1

Window {
    id: restartWindow
    flags: Qt.Window | Qt.WindowStaysOnTopHint | Qt.WindowTitleHint
    title: "WARNING: Restart Enable Required"
    width: 500
    height: 500

    Rectangle {
        anchors.fill: parent
        color: "lightGrey"

        Text {
            anchors.centerIn: parent
            text: restartEnable ? "Uh oh there... Something's wrong with your car" : "Oh hey, your car's fine now"
        }

        Text {
            x: (restartWindow.width - width) / 2
            y: restartWindow.height / 2 + 20
            text: qsTr("Battery Pack Switch: " + battery_eStop)
        }
        Text {
            x: (restartWindow.width - width) / 2
            y: restartWindow.height / 2 + 40
            text: qsTr("Driver Shutdown Switch: " + driver_eStop)
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(!restartEnable) {
                    restartWindow.close();
                }
            }
        }

    }
}
