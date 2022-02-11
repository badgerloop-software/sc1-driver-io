import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Popup {
    id: restartPopup
    anchors.centerIn: parent
    //x: (parent.width - width) / 2
    //y: (parent.height - height) / 2
    width: 500
    height: 500
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    background: Rectangle {
        color: "lightGrey"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(!restartEnable) {
                restartPopup.close();
            }
        }
    }

    Text {
        x: (parent.width - width) / 2
        y: 25
        text: restartEnable ? "Uh oh... Something's wrong with your car." : "Oh hey, your car's fine now.\nTap this window to close it."
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 5

        Text {
            //x: (restartPopup.width - width) / 2
            //y: restartPopup.height / 2 + 40
            text: qsTr("Battery Pack Switch")
            color: battery_eStop ? "black" : "red"
            font.pointSize: 12
        }

        Text {
            //x: (restartPopup.width - width) / 2
            //y: restartPopup.height / 2 + 60
            text: qsTr("Driver Shutdown Switch")
            color: driver_eStop ? "black" : "red"
            font.pointSize: 12
        }

        /*CheckBox {
            /*topInset: -2
            leftInset: -2
            rightInset: -2
            bottomInset: -2
            background: Rectangle {
                opacity: battery_eStop ? 0 : 0.5
                color: "red"
            }*/
            // Change text color based on shutdown circuit input value
            /*text: qsTr("<font color=\"%1\">Battery Pack Switch</font>".arg(battery_eStop ? "black" : "red"))
            checkable: false // Don't allow user input
            focusPolicy: Qt.NoFocus // CheckBox won't accept focus
            Binding on checked { value: battery_eStop }
        }

        CheckBox {
            /*topInset: -2
            leftInset: -2
            rightInset: -2
            bottomInset: -2
            background: Rectangle {
                opacity: driver_eStop ? 0 : 0.5
                color: "red"
            }*/
            // Change text color based on shutdown circuit input value
            /*text: qsTr("<font color=\"%1\">Driver Shutdown Switch</font>".arg(driver_eStop ? "black" : "red"))
            checkable: false // Don't allow user input
            focusPolicy: Qt.NoFocus // CheckBox won't accept focus
            Binding on checked { value: driver_eStop }

        }*/
    }
}
/*
Window {
    id: restartWindow
    flags: Qt.Window | Qt.WindowStaysOnTopHint | Qt.WindowTitleHint
    title: "WARNING: Restart Enable Required"
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 500
    height: 500

    Rectangle {
        anchors.fill: parent
        color: "lightGrey"

        Text {
            anchors.centerIn: parent
            text: restartEnable ? "Uh oh... Something's wrong with your car." : "Oh hey, your car's fine now.\nTap this window to close it."
        }

        Text {
            x: (restartWindow.width - width) / 2
            y: restartWindow.height / 2 + 40
            text: qsTr("Battery Pack Switch: " + battery_eStop)
        }
        Text {
            x: (restartWindow.width - width) / 2
            y: restartWindow.height / 2 + 60
            text: qsTr("Driver Shutdown Switch: " + driver_eStop)
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
}*/
