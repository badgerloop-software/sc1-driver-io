import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Popup {
    id: restartPopup
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 1500
    height: 800
    padding: 25
    modal: true
    closePolicy: Popup.NoAutoClose

    // TODO Assuming NC E-stops, imd_status=true preferred, NO door sensor, crash=false preferred, and mcu_check=false preferred

    property int mcu_check_point_size: 22
    property int mcu_check_pref_height: 40
    property int shutdown_input_text_size: 30
    property int shutdown_input_pref_height: 50
    property bool can_close: !battery_eStop_rect.battery_eStop_fault && !driver_eStop_rect.driver_eStop_fault && !external_eStop_rect.external_eStop_fault && !imd_status_rect.imd_status_fault && !door_rect.door_fault && !crash_rect.crash_fault && !mcu_check_rect.mcu_check_fault

    function getCellGroupFaults() {
        var cellGroups = "Cell group voltage(s)\n"
        for(const i in backEnd.cell_group_voltages) {
            if(backEnd.cell_group_voltages[i] > 7.2) {
                cellGroups += (parseInt(i) + 1) + " high, "
            } else if(backEnd.cell_group_voltages[i] < 6.4) {
                cellGroups += (parseInt(i) + 1) + " low, "
            }
        }

        if(cellGroups.length > 22) {
            return cellGroups.substring(0, cellGroups.length - 2)
        } else {
            return ""
        }
    }


    Overlay.onPressed: {
        if(can_close) {
            backEnd.restart_enable = false;
            backEnd.enableRestart(); // Signal user has enabled restart
            restartPopup.close();
        }
    }

    Overlay.modal: Rectangle {
        color: "#809f6060"
    }

    background: Rectangle {
        color: "#ffffff"
    }

    contentItem: Rectangle {
        color: "#000000"

        Text {
            id: shutdownHeader
            x: (parent.width - width) / 2
            y:  height / 2
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 24
            text: qsTr("Shutdown Faults")
            color: "#ffffff"
        }


        GridLayout {
            id: errors
            x: (parent.width - width) / 2
            y: 2 * shutdownHeader.y + shutdownHeader.height
            width: parent.width
            columns: 3
            columnSpacing: 0
            rowSpacing: 10

            Rectangle {
                id: battery_eStop_rect
                color: 'black'
                Layout.row: 0
                Layout.column: 0
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height
                visible: false

                property bool battery_eStop_fault: !backEnd.battery_eStop
                onBattery_eStop_faultChanged: {
                    if(battery_eStop_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("Battery Pack Switch")
                    color: parent.battery_eStop_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                }
            }

            Rectangle {
                id: driver_eStop_rect
                color: 'black'
                Layout.row: 0
                Layout.column: 1
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height
                visible: false

                property bool driver_eStop_fault: !backEnd.driver_eStop
                onDriver_eStop_faultChanged: {
                    if(driver_eStop_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("Driver Shutdown Switch")
                    color: parent.driver_eStop_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                }
            }

            Rectangle {
                id: external_eStop_rect
                color: 'black'
                Layout.row: 0
                Layout.column: 2
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height
                visible: false

                property bool external_eStop_fault: !backEnd.external_eStop
                onExternal_eStop_faultChanged: {
                    if(external_eStop_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("External Shutdown Switch")
                    color: parent.external_eStop_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                }
            }

            Rectangle {
                id: imd_status_rect
                color: 'black'
                Layout.row: 1
                Layout.column: 0
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height
                visible: false

                property bool imd_status_fault: !backEnd.imd_status
                onImd_status_faultChanged: {
                    if(imd_status_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("Isolation")
                    color: parent.imd_status_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                }
            }

            Rectangle {
                id: door_rect
                color: 'black'
                Layout.row: 1
                Layout.column: 1
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height
                visible: false

                property bool door_fault: !backEnd.door
                onDoor_faultChanged: {
                    if(door_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("Driver Door")
                    color: parent.door_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                }
            }

            Rectangle {
                id: crash_rect
                color: 'black'
                Layout.row: 1
                Layout.column: 2
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height
                visible: false

                property bool crash_fault: backEnd.crash
                onCrash_faultChanged: {
                    if(crash_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    anchors.centerIn: parent
                    text: qsTr("Crash")
                    color: parent.crash_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                }
            }

            Rectangle {
                id: bps_fault_rect
                color: 'black'
                Layout.row: 2
                Layout.columnSpan: 3
                Layout.fillWidth: true
                Layout.preferredHeight: shutdown_input_pref_height * 1.5
                visible: false

                // Trigger BPS fault whenever the external power cut off switch is pressed (and consequently when the MPS is opened)
                // See ASC regulations 8.6.B-8.6.C for more info on BPS fault dash indication:
                //      https://www.americansolarchallenge.org/ASC/wp-content/uploads/2022/03/ASC2022-Regs-EXTERNAL-RELEASE-B.pdf
                property bool bps_fault: !backEnd.bps_fault || !backEnd.external_eStop || !backEnd.mps_enable
                onBps_faultChanged: {
                    if(bps_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    anchors.centerIn: parent
                    font.weight: Font.Bold
                    text: qsTr("BPS Fault")
                    color: parent.bps_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size * 1.5
                }
            }

            Rectangle {
                id: mcu_check_rect
                color: 'black'
                Layout.row: 3
                Layout.columnSpan: 3
                Layout.fillWidth: true
                Layout.preferredHeight: shutdown_input_pref_height
                visible: false

                property bool mcu_check_fault: !backEnd.mcu_check
                onMcu_check_faultChanged: {
                    if(mcu_check_fault) {
                        this.visible = true;
                    }
                }

                Text {
                    id: mcu_check_text
                    anchors.centerIn: parent
                    font.weight: Font.Bold
                    text: qsTr("MCU Check")
                    color: parent.mcu_check_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                }

                GridLayout {
                    id: mcu_check
                    y: mcu_check_text.height + 10
                    Layout.fillWidth: true
                    columns: 4
                    columnSpacing: 0
                    rowSpacing: 10

                    Rectangle {
                        color: 'black'
                        Layout.row: 0
                        Layout.column: 0
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool under_voltage_fault: backEnd.pack_voltage < 69
                        onUnder_voltage_faultChanged: {
                            if(under_voltage_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "Battery undervoltage"
                            color: parent.under_voltage_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 0
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool over_voltage_fault: backEnd.pack_voltage > 108
                        onOver_voltage_faultChanged: {
                            if(over_voltage_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "Battery overvoltage"
                            color: parent.over_voltage_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 0
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool under_current_fault: backEnd.pack_current < 0 // TODO
                        onUnder_current_faultChanged: {
                            if(under_current_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "Battery undercurrent"
                            color: parent.under_current_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 0
                        Layout.column: 3
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool over_current_fault: backEnd.pack_current > 100 // TODO
                        onOver_current_faultChanged: {
                            if(over_current_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "Battery overcurrent"
                            color: parent.over_current_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 1
                        Layout.column: 0
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool mps_enable_fault: !backEnd.mps_enable
                        onMps_enable_faultChanged: {
                            if(mps_enable_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "MPS Enable"
                            color: parent.mps_enable_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 1
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool bms_input_voltage_low_fault: backEnd.bms_input_voltage < 12
                        onBms_input_voltage_low_faultChanged: {
                            if(bms_input_voltage_low_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS input voltage low"
                            color: parent.bms_input_voltage_low_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 1
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool bms_input_voltage_high_fault: backEnd.bms_input_voltage > 24
                        onBms_input_voltage_high_faultChanged: {
                            if(bms_input_voltage_high_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS input voltage high"
                            color: parent.bms_input_voltage_high_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 1
                        Layout.column: 3
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool over_temp_fault: backEnd.pack_temp > 60
                        onOver_temp_faultChanged: {
                            if(over_temp_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "Battery overtemperature"
                            color: parent.over_temp_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 2
                        Layout.column: 0
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool bms_canbus_failure_fault: backEnd.bms_canbus_failure
                        onBms_canbus_failure_faultChanged: {
                            if(bms_canbus_failure_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS CANBUS failure"
                            color: parent.bms_canbus_failure_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 2
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool voltage_failsafe_fault: backEnd.voltage_failsafe
                        onVoltage_failsafe_faultChanged: {
                            if(voltage_failsafe_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS voltage failsafe"
                            color: parent.voltage_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 2
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool current_failsafe_fault: backEnd.current_failsafe
                        onCurrent_failsafe_faultChanged: {
                            if(current_failsafe_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS current failsafe"
                            color: parent.current_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 2
                        Layout.column: 3
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        property bool supply_power_failsafe_fault: backEnd.supply_power_failsafe
                        onSupply_power_failsafe_faultChanged: {
                            if(supply_power_failsafe_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS supply power failsafe"
                            color: parent.supply_power_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }

                    }

                    Rectangle {
                        property bool memory_failsafe_fault: backEnd.memory_failsafe

                        color: 'black'
                        Layout.row: 3
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        onMemory_failsafe_faultChanged: {
                            if(memory_failsafe_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS memory failsafe"
                            color: parent.memory_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        property bool relay_failsafe_fault: backEnd.relay_failsafe

                        color: 'black'
                        Layout.row: 3
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height
                        visible: false

                        onRelay_failsafe_faultChanged: {
                            if(relay_failsafe_fault) {
                                this.visible = true;
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: "BMS relay failsafe"
                            color: parent.relay_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                        }
                    }

                    Rectangle {
                        color: 'black'
                        Layout.row: 4
                        Layout.columnSpan: 4
                        Layout.fillWidth: true
                        Layout.preferredWidth: contentItem.width - 20
                        Layout.minimumHeight: mcu_check_pref_height
                        Layout.preferredHeight: 2.5 * mcu_check_pref_height
                        visible: false

                        property var cell_group_faults: restartPopup.getCellGroupFaults()
                        onCell_group_faultsChanged: {
                            if(cell_group_faults !== "") {
                                this.visible = true;
                            }
                        }

                        Text {
                            wrapMode: Text.Wrap
                            width: contentItem.width - 20
                            anchors.centerIn: parent
                            horizontalAlignment: Text.AlignHCenter
                            text: parent.cell_group_faults
                            color: "red"
                            font.pointSize: 18
                        }
                    }
                }
            }
        }

        Text {
            x: (parent.width - width) / 2
            y: parent.height - height - 15
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 18
            text: can_close ? qsTr("All faults cleared\nTap anywhere to clear warning") : qsTr("")
            color: "#ffffff"
        }
    }
}
