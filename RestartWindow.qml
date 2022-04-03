import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Popup {
    id: restartPopup
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 750
    height: 750
    padding: 25
    modal: true
    //focus: true
    closePolicy: Popup.NoAutoClose

    Overlay.onPressed: {
        // TODO if(battery_eStop_fault===true || driver_eStop_fault===true || external_eStop_fault===true || imd_status_fault===true || door_fault===true || crash_fault===true || mcu_check_fault===true)
        // TODO if(!restartEnable) {
        if(!battery_eStop_fault && !driver_eStop_fault && !external_eStop_fault && !imd_status_fault && !door_fault && !crash_fault && !mcu_check_fault) {
            backEnd.restart_enable = false; // TODO Maybe I should use a getter and setter for restart_enable instead of using a member. Would this mess with getting controls the restart enable siganl? Could I just also modify an additional member inside of the getter/settter methods?
            restartPopup.close();
        }
    }

    Overlay.modal: Rectangle {
        color: "#409f6060"
    }

    background: Rectangle {
        color: "#ffffff"
    }

    contentItem: Rectangle {
        id: popupRect
        color: "#000000"

        Text {
            x: (parent.width - width) / 2
            y: (errors.y - parent.y) / 2 - 10
            horizontalAlignment: Text.AlignHCenter
            //font.pointSize: restartEnable ? 30 : 24
            //text: restartEnable ? "Shutdown Fault" : "All faults cleared\nTap anywhere to clear warning"
            font.pointSize: 30
            text: qsTr("Shutdown Fault")
            color: "#ffffff"
        }

        ColumnLayout {
            id: errors
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            spacing: 7

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Battery Pack Switch")
                color: battery_eStop_fault ? "red" : "white"
                font.pointSize: 36
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Driver Shutdown Switch")
                color: driver_eStop_fault ? "red" : "white"
                font.pointSize: 36
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("External Shutdown Switch")
                color: external_eStop_fault ? "red" : "white"
                font.pointSize: 36
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Isolation")
                color: imd_status_fault ? "red" : "white"
                font.pointSize: 36
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Driver Door")
                color: door_fault ? "red" : "white"
                font.pointSize: 36
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("Crash")
                color: crash_fault ? "red" : "white"
                font.pointSize: 36
            }

            Text {
                id: mcu_check_text
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("MCU Check")
                color: mcu_check_fault ? "red" : "white"
                font.pointSize: 36
            }

            ColumnLayout {
                id: mcu_check
                Layout.alignment: Qt.AlignHCenter
                spacing: 3

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    visible: over_voltage_fault || under_voltage_fault
                    text: qsTr(over_voltage_fault ? "Overvoltage" : under_voltage_fault ? "Undervoltage" : "")
                    color: (over_voltage_fault || under_voltage_fault) ? "red" : "white"
                    font.pointSize: 30
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Driver Shutdown Switch")
                    color: driver_eStop_fault ? "red" : "white"
                    font.pointSize: 30
                }
            }
        }



        Text {
            x: (parent.width - width) / 2
            y: parent.height - height - 20
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 20
            text: restartEnable ? qsTr("") : qsTr("All faults cleared\nTap anywhere to clear warning")
            color: "#ffffff"
        }
    }
}
