import QtQuick 2.4
import "UI"

Item {
    id: dashboard
    //x: -380
    //y: -200
    //width: 1024
    //height: 600
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
        //x: 212
        //y: 436
        scale: 1
    }

    Blinkers {
        id: rightBlinker
        x: 1353
        y: 123
        //x: -272
        //y: -140
        scale: 1
    }

    ClockUI {
        id: clockUI
        //x: 696
        //y: -40
        x: dashboard.width - width * (scale + 1) / 2
        y: height * (scale - 1) / 2
        scale: 1
    }

    Battery {
        id: battery
        x: 1566
        y: 190
        //x: -63
        //y: -40
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

    Blinkers {
        id: leftBlinker
        x: 628
        y: 123
        rotation: 180
        scale: 1
    }

    Image {
        id: mainioCommsIcon
        x: 108
        y: 43
        width: 175
        height: 175
        source: "UI/Images/Main IO Comms Lost.png"
        sourceSize.height: 175
        sourceSize.width: 175
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: powerWarningIcon
        x: 390
        y: 46
        width: 95
        height: 169
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
        source: "UI/Images/Cruise Control.png"
        sourceSize.height: 120
        sourceSize.width: 120
        fillMode: Image.PreserveAspectFit
    }
} //scale: 0.4

/*Speed {
    id: speedometer
    x: (dashboard.width - width) / 2
    y: (dashboard.height - width) / 2
    scale: 1.35
}

State {
    id: stateChar
    x: speedometer.x + speedometer.width * (speedometer.scale + 1) / 2 - width / 2
    y: speedometer.y - speedometer.height * (speedometer.scale - 1) / 2 - height / 2
    scale: 2
    //x: dashboard.width/2(speedometer.width - width)
    //y: 140
}

Rectangle {
    id: rectangle
    x: 0
    y: 0
    //width: 1034
    //height: 608
    width: 1920
    height: 1080
    color: "#000000"
    z: -1
}

Temperature {
    id: temperature
    //x: 212
    //y: 436
    x: (dashboard.width - width) / 2
    y: dashboard.height - height * (scale + 1) / 2
    scale: 1
}

Blinkers {
    id: blinkers
    //x: -272
    //y: -140
    x: width * (scale - 1) / 2
    y: height * (scale - 1) / 2
    scale: 0.5
}

Battery {
    id: batt
    //x: -63
    //y: -40
    x: width * (scale - 1) / 2
    y: dashboard.height - height * (scale + 1) / 2
    scale: 1.1
}

Power {
    //x: 654
    //y: 100
    x: dashboard.width - width * (scale + 1) / 2
    y: (dashboard.height - height) / 2
    scale: 1.5
}

Alerts {
    id: alerts
    //x: 112
    //y: -40
    x: (dashboard.width - width) / 2
    y: height * (scale - 1) / 2
    scale: 1
}

ClockUI {
    id: clockUI
    //x: 696
    //y: -40
    x: dashboard.width - width * (scale + 1) / 2
    y: height * (scale - 1) / 2
    scale: 1
}

Cruise {
    id: cruise
    //x: 178
    //y: -26
    x: speedometer.x - speedometer.width * (speedometer.scale - 1) / 2 - width / 2
    y: speedometer.y - speedometer.height * (speedometer.scale - 1) / 2 - height / 2
    scale: 0.3
}*/


/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:1}D{i:2}D{i:3}D{i:4}D{i:5}D{i:6}D{i:7}D{i:8}D{i:9}D{i:10}
D{i:11}D{i:12}D{i:13}
}
##^##*/

