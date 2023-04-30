import QtQuick 2.15
import QtQuick.Window 2.1
import QtQuick.Controls 2.12

Window {
    id: root
    width: 1920
    height: 1080
    visible: true
    //visibility: "FullScreen"
    title: qsTr("Solar Car Dashboard")

    property var restartWin: RestartWindow {

    }

    property bool restartEnable: backEnd.restart_enable

    onRestartEnableChanged: {
        root.restartWin.open();
    }

    Dashboard {

    }
}
