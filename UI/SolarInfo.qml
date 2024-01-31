import QtQuick 2.4

Item {
    id: solarInfo
    width: 350
    height: 400

    Text {
        id: name
        x: 125
        y: -26
        width: 100
        height: 100
        color: "#ffffff"
        text: "Solar"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Text {
        id: primaryValue
        x: 125
        y: 52
        width: 100
        height: 100
        color: "#ffffff"
        text: (backEnd.mppt_current_out * backEnd.pack_voltage).toFixed(0)
        font.pixelSize: 96
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Text {
        id: primaryValueUnitLabel
        x: 125
        y: 127
        width: 100
        height: 100
        color: "#ffffff"
        text: "W"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Rectangle {
        id: horizontalSeparator
        x: 0
        y: 208
        width: 350
        height: 2
        color: "#ffffff"
    }

    Text {
        id: secondaryValueLeft
        x: 50
        y: 233
        width: 100
        height: 100
        color: "#ffffff"
        text: backEnd.pack_voltage.toFixed(0)
        font.pixelSize: 48
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Text {
        id: secondaryValueRight
        x: 217
        y: 233
        width: 100
        height: 100
        color: "#ffffff"
        text: backEnd.mppt_current_out.toFixed(0)
        font.pixelSize: 48
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Text {
        id: secondaryValueUnitLabelLeft
        x: 50
        y: 300
        width: 100
        height: 100
        color: "#ffffff"
        text: "V"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Text {
        id: secondaryValueUnitLabelRight
        x: 217
        y: 300
        width: 100
        height: 100
        color: "#ffffff"
        text: "A"
        font.pixelSize: 36
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }
}
