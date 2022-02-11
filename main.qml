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
        property bool restartEnable: root.restartEnable
    }

    // TODO Replace restartEnable value with actual shutdown circuit values
    property bool restartEnable: (backEnd.speed > 2) && (backEnd.speed < 20)

    onRestartEnableChanged: {
        root.restartWin.show();
    }

    Dashboard{

    }
}
