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
        x: 560
        y: 205
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
        x: 624
        y: 87
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
        x: 916
        y: 79
        width: 120
        height: 120
        visible: backEnd.crz_pwr_mode || backEnd.crz_spd_mode
        source: backEnd.crz_spd_mode ? "UI/Images/Cruise Speed.png" : "UI/Images/Cruise Power.png"
        sourceSize.height: 120
        sourceSize.width: 120
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: engDashComm
        x: 1390
        y: 50
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
        x: 155
        y: 194
        source: "UI/Images/main_telem.png"
        fillMode: Image.PreserveAspectFit
        visible: backEnd.main_telem
    }

    Image {
        id: parkingBrake
        x: 265
        y: 40
        source: "UI/Images/Parking Brake.png"
        fillMode: Image.PreserveAspectFit
        visible: backEnd.parking_brake
    }

    Image {
        id: eco
        x: 909
        y: 379
        width: 103
        height: 51
        source: "UI/Images/ECO.png"
        fillMode: Image.PreserveAspectFit
        visible: backEnd.eco
    }

    Text {
        id: text1
        x: 1036
        y: 72
        width: 92
        height: 56
        color: "#40c321"
        text: qsTr("SET")
        font.pixelSize: 48
        font.weight: Font.Bold
        font.family: "Work Sans"
        visible: (backEnd.crz_pwr_mode || backEnd.crz_spd_mode)
                 && backEnd.state === "C"
    }
}
