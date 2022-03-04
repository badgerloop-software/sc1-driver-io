import QtQuick 2.4

Item {
    property int hours
    property int minutes
    property int seconds

    function updateTime(){
        var date = new Date
        hours = (date.getUTCHours()+24-6)%24
        minutes = date.getMinutes()
        seconds = date.getUTCSeconds()
    }

    function formatTime(time) {
        if(time<10)
            return "0"+time
        return time
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
            text: hours + ":" + formatTime(minutes) + ":" + formatTime(seconds)
            font.pixelSize: 80
        }

        Text {
            property bool delay: (backEnd.rtc_hr !== hours) || (backEnd.rtc_mn !== minutes) || (backEnd.rtc_sc !== seconds)

            id: packetDelay
            x: (rectangle.width-width)/2
            y: (rectangle.height/2+height)/2
            color: delay ? "red" : "#ffffff"
            text: (delay ? "-" : "") + Math.abs(backEnd.rtc_hr - hours) + ":" + formatTime(Math.abs(backEnd.rtc_mn - minutes)) + ":" + formatTime(Math.abs(backEnd.rtc_sc - seconds))
            font.pixelSize: 80
        }
    }

    Timer {
        interval: 100
        running: true
        repeat: true
        onTriggered: updateTime()
    }
}
