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

    //scale: 0.4
    Speed {
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
    }
}

