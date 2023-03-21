import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Popup {
    id: restartPopup
    parent: Overlay.overlay
    anchors.centerIn: parent
    width: 1625
    height: 875
    padding: 25
    modal: true
    closePolicy: Popup.NoAutoClose

    // TODO Assuming NO E-stops, imd_status=false preferred, NO door sensor, crash=false preferred, and mcu_check=false preferred

    property int mcu_check_point_size: 22
    property int mcu_check_pref_height: 50
    property int shutdown_input_text_size: 30
    property int shutdown_input_pref_height: 60
    property double hidden_opacity: 0.25
    property string grid_item_border_color: "#20ffffff"
    property int grid_item_border_width: 2
    property bool can_close: !battery_eStop_text.battery_eStop_fault && !driver_eStop_text.driver_eStop_fault && !external_eStop_text.external_eStop_fault
                             && !imd_status_text.imd_status_fault && !door_text.door_fault && !crash_text.crash_fault && !mcu_check_text.mcu_check_fault

    Overlay.onPressed: {
        if(can_close) {
            backEnd.restart_enable = false;
            // Reset opacities of fault texts to hidden_opacity so that they aren't shown as being triggered when restartPopup opens again
            var ids = { battery_eStop_text, driver_eStop_text, external_eStop_text, imd_status_text, door_text, crash_text, bps_fault_text, mcu_check_text,
                        mps_enable_text, mppt_contactor_text, low_contactor_text, motor_controller_contactor_text, over_voltage_text, under_voltage_text,
                        over_current_text, under_current_text, bms_input_voltage_high_text, bms_input_voltage_low_text, over_temp_text, bms_canbus_failure_text,
                        voltage_failsafe_text, current_failsafe_text, supply_power_failsafe_text, memory_failsafe_text, relay_failsafe_text, cell_group_voltages_text };

            for(const idx in ids) {
                ids[idx].opacity = hidden_opacity;
            }

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
            y: height / 2
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 24
            text: qsTr("Shutdown Faults")
            color: "#ffffff"
        }

        Rectangle {
            id: bps_fault_rect
            color: 'black'
            anchors.top: shutdownHeader.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            height: shutdown_input_pref_height * 1.5

            Text {
                id: bps_fault_text

                // Trigger BPS fault whenever the external power cut off switch is pressed (and consequently when the MPS is opened)
                // See ASC regulations 8.6.B-8.6.C for more info on BPS fault dash indication:
                //      https://www.americansolarchallenge.org/ASC/wp-content/uploads/2022/03/ASC2022-Regs-EXTERNAL-RELEASE-B.pdf
                property bool bps_fault: (backEnd.bps_fault || backEnd.external_eStop || !backEnd.mps_enable) && backEnd.restart_enable
                onBps_faultChanged: {
                    if(bps_fault) {
                        this.opacity = 1;
                    }
                }

                anchors.centerIn: parent
                font.weight: Font.Bold
                text: qsTr("BPS Fault")
                color: bps_fault ? "red" : "white"
                font.pointSize: shutdown_input_text_size * 1.5
                opacity: hidden_opacity
            }
        }


        GridLayout {
            id: errors
            x: (parent.width - width) / 2
            anchors.top: bps_fault_rect.bottom
            width: parent.width
            columns: 3
            columnSpacing: 0
            rowSpacing: 0

            Rectangle {
                color: 'black'
                border.color: grid_item_border_color
                border.width: grid_item_border_width
                Layout.row: 0
                Layout.column: 0
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height

                Text {
                    id: battery_eStop_text
                    property bool battery_eStop_fault: backEnd.battery_eStop && backEnd.restart_enable
                    onBattery_eStop_faultChanged: {
                        if(battery_eStop_fault) {
                            this.opacity = 1;
                        }
                    }

                    anchors.centerIn: parent
                    text: qsTr("Battery Pack Switch")
                    color: battery_eStop_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                    opacity: hidden_opacity
                }
            }

            Rectangle {
                color: 'black'
                border.color: grid_item_border_color
                border.width: grid_item_border_width
                Layout.row: 0
                Layout.column: 1
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height

                Text {
                    id: driver_eStop_text
                    property bool driver_eStop_fault: backEnd.driver_eStop && backEnd.restart_enable
                    onDriver_eStop_faultChanged: {
                        if(driver_eStop_fault) {
                            this.opacity = 1;
                        }
                    }

                    anchors.centerIn: parent
                    text: qsTr("Driver Shutdown Switch")
                    color: driver_eStop_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                    opacity: hidden_opacity
                }
            }

            Rectangle {
                color: 'black'
                border.color: grid_item_border_color
                border.width: grid_item_border_width
                Layout.row: 0
                Layout.column: 2
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height

                Text {
                    id: external_eStop_text
                    property bool external_eStop_fault: backEnd.external_eStop && backEnd.restart_enable
                    onExternal_eStop_faultChanged: {
                        if(external_eStop_fault) {
                            this.opacity = true;
                        }
                    }

                    anchors.centerIn: parent
                    text: qsTr("External Shutdown Switch")
                    color: external_eStop_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                    opacity: hidden_opacity
                }
            }

            Rectangle {
                color: 'black'
                border.color: grid_item_border_color
                border.width: grid_item_border_width
                Layout.row: 1
                Layout.column: 0
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height

                Text {
                    id: imd_status_text
                    property bool imd_status_fault: backEnd.imd_status && backEnd.restart_enable
                    onImd_status_faultChanged: {
                        if(imd_status_fault) {
                            this.opacity = 1;
                        }
                    }

                    anchors.centerIn: parent
                    text: qsTr("Isolation")
                    color: imd_status_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                    opacity: hidden_opacity
                }
            }

            Rectangle {
                color: 'black'
                border.color: grid_item_border_color
                border.width: grid_item_border_width
                Layout.row: 1
                Layout.column: 1
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height

                Text {
                    id: door_text
                    property bool door_fault: !backEnd.door && backEnd.restart_enable
                    onDoor_faultChanged: {
                        if(door_fault) {
                            this.opacity = 1;
                        }
                    }

                    anchors.centerIn: parent
                    text: qsTr("Driver Door")
                    color: door_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                    opacity: hidden_opacity
                }
            }

            Rectangle {
                color: 'black'
                border.color: grid_item_border_color
                border.width: grid_item_border_width
                Layout.row: 1
                Layout.column: 2
                Layout.fillWidth: true
                Layout.minimumWidth: (errors.width / 3) - 1
                Layout.preferredWidth: errors.width / 3
                Layout.preferredHeight: shutdown_input_pref_height

                Text {
                    id: crash_text
                    property bool crash_fault: backEnd.crash && backEnd.restart_enable
                    onCrash_faultChanged: {
                        if(crash_fault) {
                            this.opacity = 1;
                        }
                    }

                    anchors.centerIn: parent
                    text: qsTr("Crash")
                    color: crash_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                    opacity: hidden_opacity
                }
            }

            Rectangle {
                color: 'black'
                Layout.row: 2
                Layout.columnSpan: 3
                Layout.fillWidth: true
                Layout.preferredHeight: shutdown_input_pref_height

                Text {
                    id: mcu_check_text

                    property bool mcu_check_fault: backEnd.mcu_check && backEnd.restart_enable
                    onMcu_check_faultChanged: {
                        if(mcu_check_fault) {
                            this.opacity = 1;
                        }
                    }

                    anchors.centerIn: parent
                    text: qsTr("MCU Check")
                    color: mcu_check_fault ? "red" : "white"
                    font.pointSize: shutdown_input_text_size
                    opacity: hidden_opacity
                }

                GridLayout {
                    id: mcu_check
                    y: mcu_check_text.height + 10
                    Layout.fillWidth: true
                    columns: 4
                    columnSpacing: 0
                    rowSpacing: 0

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 0
                        Layout.column: 0
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: mps_enable_text

                            property bool mps_enable_fault: !backEnd.mps_enable && backEnd.restart_enable
                            onMps_enable_faultChanged: {
                                if(mps_enable_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "MPS Enable"
                            color: mps_enable_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 0
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: mppt_contactor_text

                            property bool mppt_contactor_fault: backEnd.mppt_contactor && backEnd.restart_enable
                            onMppt_contactor_faultChanged: {
                                if(mppt_contactor_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "MPPT Contactor"
                            color: mppt_contactor_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 0
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: low_contactor_text

                            property bool low_contactor_fault: backEnd.low_contactor && backEnd.restart_enable
                            onLow_contactor_faultChanged: {
                                if(low_contactor_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "Low Contactor"
                            color: low_contactor_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 0
                        Layout.column: 3
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: motor_controller_contactor_text

                            property bool motor_controller_contactor_fault: backEnd.motor_controller_contactor && backEnd.restart_enable
                            onMotor_controller_contactor_faultChanged: {
                                if(motor_controller_contactor_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "Motor Controller Contactor"
                            color: motor_controller_contactor_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 1
                        Layout.column: 0
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height * 1.6

                        Text {
                            id: over_voltage_text

                            property bool over_voltage_fault: (backEnd.pack_voltage > 108) && backEnd.restart_enable
                            onOver_voltage_faultChanged: {
                                if(over_voltage_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.top: parent.top
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Battery overvoltage"
                            color: over_voltage_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }

                        Text {
                            id: under_voltage_text

                            property bool under_voltage_fault: (backEnd.pack_voltage < 69) && backEnd.restart_enable
                            onUnder_voltage_faultChanged: {
                                if(under_voltage_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Battery undervoltage"
                            color: under_voltage_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 1
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height * 1.6

                        Text {
                            id: over_current_text

                            property bool over_current_fault: (backEnd.pack_current > 100) && backEnd.restart_enable // TODO
                            onOver_current_faultChanged: {
                                if(over_current_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.top: parent.top
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Battery overcurrent"
                            color: over_current_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }

                        Text {
                            id: under_current_text

                            property bool under_current_fault: (backEnd.pack_current < 0) && backEnd.restart_enable // TODO
                            onUnder_current_faultChanged: {
                                if(under_current_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Battery undercurrent"
                            color: under_current_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 1
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height * 1.6

                        Text {
                            id: bms_input_voltage_high_text

                            property bool bms_input_voltage_high_fault: (backEnd.bms_input_voltage > 24) && backEnd.restart_enable
                            onBms_input_voltage_high_faultChanged: {
                                if(bms_input_voltage_high_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.top: parent.top
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "BMS input voltage high"
                            color: bms_input_voltage_high_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }

                        Text {
                            id: bms_input_voltage_low_text

                            property bool bms_input_voltage_low_fault: (backEnd.bms_input_voltage < 12) && backEnd.restart_enable
                            onBms_input_voltage_low_faultChanged: {
                                if(bms_input_voltage_low_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 5
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "BMS input voltage low"
                            color: bms_input_voltage_low_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 1
                        Layout.column: 3
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height * 1.6

                        Text {
                            id: over_temp_text

                            property bool over_temp_fault: (backEnd.pack_temp > 60) && backEnd.restart_enable
                            onOver_temp_faultChanged: {
                                if(over_temp_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "Battery overtemperature"
                            color: over_temp_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 2
                        Layout.column: 0
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: bms_canbus_failure_text

                            property bool bms_canbus_failure_fault: backEnd.bms_canbus_failure && backEnd.restart_enable
                            onBms_canbus_failure_faultChanged: {
                                if(bms_canbus_failure_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "BMS CANBUS failure"
                            color: bms_canbus_failure_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 2
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: voltage_failsafe_text

                            property bool voltage_failsafe_fault: backEnd.voltage_failsafe && backEnd.restart_enable
                            onVoltage_failsafe_faultChanged: {
                                if(voltage_failsafe_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "BMS voltage failsafe"
                            color: voltage_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 2
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: current_failsafe_text

                            property bool current_failsafe_fault: backEnd.current_failsafe && backEnd.restart_enable
                            onCurrent_failsafe_faultChanged: {
                                if(current_failsafe_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "BMS current failsafe"
                            color: current_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 2
                        Layout.column: 3
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: supply_power_failsafe_text

                            property bool supply_power_failsafe_fault: backEnd.supply_power_failsafe && backEnd.restart_enable
                            onSupply_power_failsafe_faultChanged: {
                                if(supply_power_failsafe_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "BMS supply power failsafe"
                            color: supply_power_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }

                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 3
                        Layout.column: 1
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: memory_failsafe_text

                            property bool memory_failsafe_fault: backEnd.memory_failsafe && backEnd.restart_enable
                            onMemory_failsafe_faultChanged: {
                                if(memory_failsafe_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "BMS memory failsafe"
                            color: memory_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        color: 'black'
                        border.color: grid_item_border_color
                        border.width: grid_item_border_width
                        Layout.row: 3
                        Layout.column: 2
                        Layout.fillWidth: true
                        Layout.minimumWidth: (mcu_check.width / 4) - 1
                        Layout.preferredWidth: mcu_check.width / 4
                        Layout.preferredHeight: mcu_check_pref_height

                        Text {
                            id: relay_failsafe_text

                            property bool relay_failsafe_fault: backEnd.relay_failsafe && backEnd.restart_enable
                            onRelay_failsafe_faultChanged: {
                                if(relay_failsafe_fault) {
                                    this.opacity = 1;
                                }
                            }

                            anchors.centerIn: parent
                            text: "BMS relay failsafe"
                            color: relay_failsafe_fault ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }
                    }

                    Rectangle {
                        id: cell_group_fault_rect
                        color: 'black'
                        Layout.row: 4
                        Layout.columnSpan: 4
                        Layout.fillWidth: true
                        Layout.preferredWidth: contentItem.width
                        Layout.minimumHeight: mcu_check_pref_height

                        Text {
                            id: cell_group_voltages_text

                            function getCellGroupFaults() {
                                // Loop through cell group voltages and check if any are outside of the nominal range; if any are, return true
                                for(const i in backEnd.cell_group_voltages) {
                                    if((backEnd.cell_group_voltages[i] > 7.2) || (backEnd.cell_group_voltages[i] < 6.4))
                                        return true;
                                }
                                return false;
                            }

                            property bool cell_group_faults: getCellGroupFaults() && backEnd.restart_enable
                            onCell_group_faultsChanged: {
                                if(cell_group_faults) {
                                    this.opacity = 1;
                                }
                            }

                            y: (mcu_check_pref_height - height) / 2
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Cell Group Voltages"
                            color: cell_group_faults ? "red" : "white"
                            font.pointSize: mcu_check_point_size
                            opacity: hidden_opacity
                        }

                        GridLayout {
                            id: cell_group_fault_grid
                            y: mcu_check_pref_height
                            Layout.fillWidth: true
                            columns: 15
                            columnSpacing: 0
                            rowSpacing: 0

                            function generateCellGroupFaultTable() {
                                // Loop through cell group voltages and create grid items for each one
                                // Each grid item will contain the cell group number as well as whether that group's voltage is high or low
                                for(const i in backEnd.cell_group_voltages) {
                                    Qt.createQmlObject(
                                        "import QtQuick 2.0
                                         import QtQuick.Controls 2.12
                                         import QtQuick.Layouts 1.0

                                         Rectangle {
                                             color: 'black'
                                             border.color: \"#40ffffff\"
                                             border.width: 1
                                             Layout.row: " + Math.floor(parseInt(i) / 15) + "
                                             Layout.column: " + (parseInt(i) % 15) + "
                                             Layout.fillWidth: true
                                             Layout.minimumWidth: (cell_group_fault_rect.width / 15) - 1
                                             Layout.preferredWidth: cell_group_fault_rect.width / 15
                                             Layout.preferredHeight: mcu_check_pref_height

                                             Text {
                                                 id: cell_group" + parseInt(i) + "_fault_text_num
                                                 property bool cell_group_voltage_fault: ((backEnd.cell_group_voltages[" + i + "] > 7.2) || (backEnd.cell_group_voltages[" + i + "] < 6.4)) && backEnd.restart_enable
                                                 onCell_group_voltage_faultChanged: {
                                                     if(cell_group_voltage_fault) {
                                                         this.opacity = 1;
                                                     }
                                                 }

                                                 anchors.verticalCenter: parent.verticalCenter
                                                 x: (parent.width - width - 4 - cell_group" + parseInt(i) + "_fault_text_high.width - cell_group" + parseInt(i) + "_fault_text_div.width - cell_group" + parseInt(i) + "_fault_text_low.width) / 2
                                                 text: \"" + (parseInt(i) + 1) + "\"
                                                 color: cell_group_voltage_fault ? \"red\" : \"white\"
                                                 font.pointSize: mcu_check_point_size / 1.1
                                                 opacity: hidden_opacity
                                             }

                                             Text {
                                                id: cell_group" + parseInt(i) + "_fault_text_high

                                                 property bool cell_group_voltage_high_fault: (backEnd.cell_group_voltages[" + i + "] > 7.2) && backEnd.restart_enable
                                                 onCell_group_voltage_high_faultChanged: {
                                                     if(cell_group_voltage_high_fault) {
                                                         this.opacity = 1;
                                                     }
                                                 }

                                                 anchors.top: parent.top
                                                 anchors.left: cell_group" + parseInt(i) + "_fault_text_num.right
                                                 anchors.leftMargin: 4
                                                 text: \"HI\"
                                                 color: cell_group_voltage_high_fault ? \"red\" : \"white\"
                                                 font.pointSize: mcu_check_point_size / 1.25
                                                 opacity: hidden_opacity
                                             }

                                             Text {
                                                 id: cell_group" + parseInt(i) + "_fault_text_div

                                                 anchors.verticalCenter: parent.verticalCenter
                                                 anchors.left: cell_group" + parseInt(i) + "_fault_text_high.right
                                                 text: \"/\"
                                                 color: \"white\"
                                                 font.pointSize: mcu_check_point_size / 1.25
                                                 opacity: ((cell_group" + parseInt(i) + "_fault_text_high.opacity == 1) && (cell_group" + parseInt(i) + "_fault_text_low.opacity == 1)) ? 1 : hidden_opacity
                                             }

                                             Text {
                                                 id: cell_group" + parseInt(i) + "_fault_text_low

                                                 property bool cell_group_voltage_low_fault: (backEnd.cell_group_voltages[" + i + "] < 6.4) && backEnd.restart_enable
                                                 onCell_group_voltage_low_faultChanged: {
                                                     if(cell_group_voltage_low_fault) {
                                                         this.opacity = 1;
                                                     }
                                                 }

                                                 anchors.bottom: parent.bottom
                                                 anchors.left: cell_group" + parseInt(i) + "_fault_text_div.right
                                                 text: \"LO\"
                                                 color: cell_group_voltage_low_fault ? \"red\" : \"white\"
                                                 font.pointSize: mcu_check_point_size / 1.25
                                                 opacity: hidden_opacity
                                             }

                                             // Reset opacity of cell group text when restartPopup closes (div text opacity depends on other opacities, so don't set it)
                                             Connections {
                                                 target: restartPopup
                                                 function onClosed() {
                                                     cell_group" + parseInt(i) + "_fault_text_num.opacity = hidden_opacity;
                                                     cell_group" + parseInt(i) + "_fault_text_high.opacity = hidden_opacity;
                                                     cell_group" + parseInt(i) + "_fault_text_low.opacity = hidden_opacity;
                                                 }
                                             }
                                         }",
                                        cell_group_fault_grid,
                                        "cell_group" + parseInt(i) + "_fault_grid_item"
                                    );
                                }
                            }

                            Component.onCompleted: generateCellGroupFaultTable()
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
