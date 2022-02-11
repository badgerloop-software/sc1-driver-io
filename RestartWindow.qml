import QtQuick 2.0
import QtQuick.Window 2.1 // needed for the Window component

Window {
    id: restartWindow
    flags: Qt.Window | Qt.WindowStaysOnTopHint | Qt.WindowTitleHint
    title: "WARNING: Restart Enable Required"
    width: 300
    height: 200

    Rectangle {

        anchors.fill: parent
        color: "lightGrey"

        Text {

            anchors.centerIn: parent

            text: restartEnable ? "Uh oh there... Something's wrong with your car" : "Oh hey, your car's fine now"
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
