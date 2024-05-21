import QtQuick 2.4
import "UI"

Item {
    id: dashboard
    width: 1920
    height: 1080
    property alias rectangle: rectangle

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
        x: 611
        y: 198
        width: 698
        height: 950
        scale: 1
    }

    Blinkers {
        id: blinkers
        x: 311
        y: 211
        width: 1299
        height: 104
    }

    Clock {
        id: clock
        x: dashboard.width - width * (scale + 1) / 2
        y: height * (scale - 1) / 2
        scale: 1
    }

    Image {
        id: headlights
        x: 885
        y: 214
        width: 150
        height: 105
        visible: backEnd.headlights
        source: "UI/Images/Headlights.png"
        sourceSize.height: 105
        sourceSize.width: 150
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: engDashComm
        x: 1229
        y: 56
        width: 125
        height: 114
        source: "UI/Images/comm.png"
        visible: backEnd.eng_dash_commfail
        sourceSize.height: 169
        fillMode: Image.PreserveAspectFit
        sourceSize.width: 90
    }

    Batteries {
        id: batteries
        x: 22
        y: 898
        width: 558
        height: 159
    }

    Image {
        id: main_telem
        x: 560
        y: 38
        source: "UI/Images/main_telem.png"
        fillMode: Image.PreserveAspectFit
        visible: backEnd.main_telem
    }

    Image {
        id: parkingBrake
        x: 898
        y: 50
        source: "UI/Images/Parking Brake.png"
        fillMode: Image.PreserveAspectFit
        visible: backEnd.parking_brake
    }

    Image {
        id: eco
        x: 913
        y: 849
        width: 94
        height: 50
        source: "UI/Images/ECO.png"
        fillMode: Image.PreserveAspectFit
        visible: backEnd.eco
    }

    PackTempFanSpeed {
        id: packTempFanSpeed
        x: 1664
        y: 787
        width: 223
        height: 303
    }

    BatteryInfo {
        id: batteryInfo
        x: 1419
        y: 353
    }

    SolarInfo {
        id: solarInfo
        x: 126
        y: 358
    }
}
