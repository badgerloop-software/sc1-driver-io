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
        if(!restartEnable) {
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
                Layout.alignment: Qt.AlignHCenter
                text: qsTr("MCU Check")
                color: mcu_check_fault ? "red" : "white"
                font.pointSize: 36
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
