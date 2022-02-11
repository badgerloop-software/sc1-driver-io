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
        property bool battery_eStop: backEnd.battery_eStop
        property bool driver_eStop: backEnd.driver_eStop
    }

    // TODO Replace restartEnable value with actual shutdown circuit values
    // TODO Using the raw value causes issues (bc it's undefined initially?); find a better solution than comparing to true
    property bool restartEnable: (backEnd.battery_eStop === true) || (backEnd.driver_eStop === true)

    onRestartEnableChanged: {
        root.restartWin.show();
    }

    Dashboard{

    }
}
