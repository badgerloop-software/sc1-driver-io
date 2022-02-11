import QtQuick 2.0
import QtQuick.Window 2.1 // needed for the Window component

Window {
    id: restartWindow
    title: "WARNING: Restart Enable Required"
    flags: Qt.WindowStaysOnTopHint | Qt.Window
    width: 300
    height: 200

    Rectangle {

        anchors.fill: parent
        color: "lightGrey"

        Text {

            anchors.centerIn: parent

            text: "Uh oh there... Something's wrong with your car"
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
