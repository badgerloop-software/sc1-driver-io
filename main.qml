import QtQuick 2.15
import QtQuick.Window 2.1

Window {
    id: root
    //width: 1024
    //height: 600
    width: 1920
    height: 1080
    visible: true
    visibility: "FullScreen"
    title: qsTr("Solar Car Dashboard")

    property var restartWin: RestartWindow {
        flags: Qt.WindowStaysOnTopHint
    }

    //onFrameSwapped: {
    //    root.restartWin.raise();
    //}

    Dashboard{



        Text {
            text: "Click here to open new window!"
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.restartWin.show();
            }
        }
    }
}
