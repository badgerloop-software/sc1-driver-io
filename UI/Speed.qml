import QtQuick 2.15

Item {
    id: speedBox
    width: 919
    height: 950

    function isPowerInKilowatts(watts) {
        return (watts > 1000) ? true : false;
    }

    function dividePower(watts) {
        const value = isPowerInKilowatts(watts) ? watts / 1000 : watts;
        return isPowerInKilowatts(watts) ? value.toFixed(1) : value.toFixed(0);
    }

    function getPowerUnit(watts) {
        return isPowerInKilowatts(watts) ? "KW" : "W";
    }

    Item {
        id: speedometer
        x: -60
        y: 0
        width: 919
        height: 950

        Text {
            id: speed
            x: 420
            y: 106
            width: 337
            height: 168
            color: "#ffffff"
            text: backEnd.speed.toFixed(1)
            font.pixelSize: 156
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: mph
            x: 514
            y: 281
            width: 150
            height: 55
            color: "#ffffff"
            text: "MPH"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: stateText
            x: 317
            y: 267
            width: 166
            height: 82
            color: "#ffffff"
            text: backEnd.state === "C" ? "D" : qsTr(backEnd.state)
            font.pixelSize: 76
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Medium"
            font.family: "Work Sans"
        }

        Text {
            id: power
            x: 46
            y: 106
            width: 337
            height: 168
            color: "#ffffff"
            text: dividePower(backEnd.motor_power)
            font.pixelSize: 156
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: kw
            x: 140
            y: 281
            width: 150
            height: 55
            color: "#ffffff"
            text: getPowerUnit(backEnd.motor_power)
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Rectangle {
            x: 130
            y: 362
            width: 553
            height: 2
            color: "#ffffff"
        }

        Accelerator {
            id: accelerator
            x: 219
            y: 757
        }

        Text {
            x: 265
            y: 712
            width: 270
            height: 40
            color: "#ffffff"
            text: qsTr("Accelerator")
            font.pixelSize: 33
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Work Sans"
            font.styleName: "Regular"
        }

        Text {
            id: kw1
            x: 165
            y: 448
            width: 150
            height: 55
            color: (backEnd.crz_pwr_mode) ? "#00ff00" : "#ffffff"
            text: "KW"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: mph1
            x: 501
            y: 448
            width: 150
            height: 55
            color: (backEnd.crz_spd_mode) ? "#00ff00" : "#ffffff"
            text: "MPH"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: crz_power
            x: 72
            y: 323
            width: 337
            height: 168
            color: (backEnd.crz_pwr_mode) ? "#00ff00" : "#ffffff"
            text: backEnd.crz_pwr_setpt.toFixed(1)
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: crz_speed
            x: 408
            y: 323
            width: 337
            height: 168
            color: (backEnd.crz_spd_mode) ? "#00ff00" : "#ffffff"
            text: backEnd.crz_spd_setpt.toFixed(1)
            font.pixelSize: 80
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Light"
            font.family: "Work Sans"
        }

        Text {
            id: crz_enable
            x: 325
            y: 448
            width: 150
            height: 55
            color: (backEnd.crz_pwr_mode || backEnd.crz_spd_mode) ? "#00ff00" : "#000000"
            text: "Cruise"
            font.pixelSize: 45
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Regular"
            font.family: "Work Sans"
        }
    }
}
