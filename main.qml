import QtQuick 2.15
import QtQuick.Window 2.1
import QtQuick.Controls 2.12

Window {
    id: root
    width: 1920
    height: 1080
    visible: true
    visibility: "FullScreen"
    title: qsTr("Solar Car Dashboard")

    property var restartWin: RestartWindow {

    }

    // TODO Assuming NC E-stops, imd_status=true preferred, NO door sensor, crash=false preferred, and mcu_check=false preferred
    property bool battery_eStop_fault: !backEnd.battery_eStop
    property bool driver_eStop_fault: !backEnd.driver_eStop
    property bool external_eStop_fault: !backEnd.external_eStop
    property bool imd_status_fault: !backEnd.imd_status
    property bool door_fault: !backEnd.door
    property bool crash_fault: backEnd.crash
    property bool mcu_check_fault: !backEnd.mcu_check
    property bool over_voltage_fault: backEnd.pack_voltage > 108
    property bool under_voltage_fault: backEnd.pack_voltage < 69
    property bool over_current_fault: backEnd.pack_current > 100 // TODO
    property bool under_current_fault: backEnd.pack_current < 0 // TODO
    property bool over_temp_fault: backEnd.pack_temp > 60 // TODO



    property bool restartEnable: backEnd.restart_enable // TODO battery_eStop_fault===true || driver_eStop_fault===true || external_eStop_fault===true || imd_status_fault===true || door_fault===true || crash_fault===true || mcu_check_fault===true

    onRestartEnableChanged: {
        root.restartWin.open();
    }

    Dashboard {

    }
}
