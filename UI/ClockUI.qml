import QtQuick 2.4

Item {
    property int hours
    property int minutes
    property int seconds

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

    function getDelay(packetHr, packetMin, packetSec) {
        var realTime = new Date
        var packetTime = new Date
        realTime.setHours(hours)
        packetTime.setHours(packetHr)
        packetTime.setMinutes(packetMin)
        packetTime.setSeconds(packetSec)

        return (realTime.getTime() - packetTime.getTime()) / 1000;
    }

    width: 400
    height: 220

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 220
        color: "#000000"

        Text {
            id: clock
            x: (rectangle.width-width)/2
            y: (rectangle.height/2-height)/2
            color: "#ffffff"
            text: formatTime(hours) + ":" + formatTime(minutes) + ":" + formatTime(seconds)
            font.pixelSize: 80
        }

        Text {
            property int delay: getDelay(backEnd.rtc_hr, backEnd.rtc_mn, backEnd.rtc_sc)

            id: packetDelay
            x: (rectangle.width-width)/2
            y: (rectangle.height/2+height)/2
            color: (delay < 2) ? "#ffffff" : "red"
            text: ((delay > 0) ? "-" : "") + formatTime((Math.floor((delay/3600))%24)) + ":" + formatTime(Math.floor((delay/60))%60) + ":" + formatTime(delay%60)
            font.pixelSize: 60
        }
    }

    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered: updateTime()
    }
}
