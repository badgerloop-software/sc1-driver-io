import QtQuick 2.4

Item {
    property int hours
    property int minutes
    property int seconds
    property int delay

    function updateTime(){
        var date = new Date
        hours = (date.getUTCHours()+18)%24
        minutes = date.getMinutes()
        seconds = date.getUTCSeconds()
    }

    function formatTime(time) {
        if(time<10)
            return "0"+time
        return time
    }

    function updateDelay(packetHr, packetMin, packetSec, packetMSec) {
        var realTime = new Date
        var packetTime = new Date

        realTime.setHours(hours)
        packetTime.setHours(packetHr)
        packetTime.setMinutes(packetMin)
        packetTime.setSeconds(packetSec)
        packetTime.setMilliseconds(packetMSec)

        delay = realTime.getTime() - packetTime.getTime()
    }

    width: 400
    height: 200

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 200
        color: "#000000"

        Text {
            id: clock
            x: (rectangle.width-width)/2
            y: (rectangle.height/2-height)/2
            color: "#ffffff"
            text: formatTime(hours) + ":" + formatTime(minutes) + ":" + formatTime(seconds)
            font.pixelSize: 80
            font.styleName: "Regular"
            font.family: "Work Sans"
        }

        Text {
            id: packetDelay
            x: (rectangle.width-width)/2
            y: (rectangle.height/2+height)/2
            color: (delay < 2000) ? "#ffffff" : "red"
            text: ((delay > 0) ? "-" : "") + formatTime(Math.floor(delay/3600000)%24) + ":" + formatTime(Math.floor(delay/60000)%60) + ":" + formatTime(Math.floor(delay/1000)%60)

            //text: formatTime(backEnd.tstamp_hr) + ":" + formatTime(backEnd.tstamp_mn) + ":" + formatTime(backEnd.tstamp_sc) + ":" + backEnd.tstamp_ms
            font.pixelSize: 60
            font.styleName: "Regular"
            font.family: "Work Sans"
        }
    }

    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            updateTime()
            updateDelay(backEnd.tstamp_hr, backEnd.tstamp_mn, backEnd.tstamp_sc, backEnd.tstamp_ms)
        }
    }
}
