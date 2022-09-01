import QtQuick 2.4
import "UI"

Item {
    id: dashboard
    width: 1920
    height: 1080

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 1920
        height: 1080
        color: "#000000"
        border.width: 0
        z: -1
    }

    Speed {
        id: speedometer
        x: 628
        y: 123
        scale: 1
    }

    Temperature {
        id: temperature
        x: 616
        y: 925
        scale: 1
    }

    Blinkers {
        id: blinkers
        x: 628
        y: 123
    }

    Clock {
        id: clock
        x: dashboard.width - width * (scale + 1) / 2
        y: height * (scale - 1) / 2
        scale: 1
    }

    Battery {
        id: battery
        x: 1566
        y: 190
        scale: 1
    }

    BatterySolarBox {
        id: batterySolar
        x: 0
        y: 261
    }

    CellStringTemps {
        id: stringTemps
        x: 10
        y: 894
    }

    Image {
        id: mainioCommsIcon
        x: 37
        y: 58
        width: 115
        height: 132
        visible: backEnd.mainIO_heartbeat
        source: "UI/Images/Main IO Comms Lost.png"
        sourceSize.height: 175
        sourceSize.width: 175
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: powerWarningIcon
        x: 230
        y: 61
        width: 80
        height: 129
        // TODO If there are no specific power warnings, maybe just use this as an alert for when any voltages/currents are within 10% of their nominal min/max
        //      In that case, maybe add an icon to do the same thing but for temperatures.
        source: "UI/Images/Power Warning.png"
        sourceSize.height: 169
        sourceSize.width: 90
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: headlights
        x: 828
        y: 25
        width: 150
        height: 105
        visible: backEnd.headlights
        source: "UI/Images/Headlights.png"
        sourceSize.height: 105
        sourceSize.width: 150
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: cruise
        x: 1160
        y: 17
        width: 120
        height: 120
        visible: backEnd.cruise
        source: "UI/Images/Cruise Control.png"
        sourceSize.height: 120
        sourceSize.width: 120
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: engDashComm
        x: 398
        y: 0
        width: 126
        height: 255
        source: "UI/Images/comm.png"
        visible: backEnd.eng_dash_commfail
        sourceSize.height: 169
        fillMode: Image.PreserveAspectFit
        sourceSize.width: 90
    }
}
