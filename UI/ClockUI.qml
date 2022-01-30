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
            y: (rectangle.height-height)/2
            color: "#ffffff"
            text: hours + ":" + formatTime(minutes) + ":" + formatTime(seconds)
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
