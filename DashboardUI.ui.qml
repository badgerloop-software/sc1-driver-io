import QtQuick 2.4
import "UI"

Item {
    id: dashboard
    //x: -380
    //y: -200
    width: 1024
    height: 600

    //scale: 0.4
    Speed {
        id: speedometer
        x: (dashboard.width - width) / 2
        y: (dashboard.height - width) / 2
        scale: 0.85
    }

    State {
        id: stateChar
        x: 614
        y: 140
    }

    Rectangle {
        id: rectangle
        x: -10
        y: -8
        width: 1034
        height: 608
        color: "#000000"
        z: -1
    }

    Temperature {
        id: temperature
        x: 212
        y: 436
        scale: 0.6
    }

    Blinkers {
        id: blinkers
        x: -272
        y: -140
        scale: -0.3
    }

    Battery {
        id: batt
        x: -63
        y: -40
        scale: 0.55
    }

    Power {
        x: 654
        y: 100
        scale: 0.85
    }

    Alerts {
        id: alerts
        x: 112
        y: -40
        scale: 0.6
    }

    ClockUI {
        id: clockUI
        x: 696
        y: -40
        scale: 0.6
    }

    Cruise {
        id: cruise
        x: 178
        y: -26
        scale: 0.15
    }
}
