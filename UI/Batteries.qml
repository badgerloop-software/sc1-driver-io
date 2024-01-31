import QtQuick 2.4
Item {
    id: batteries
    width: 558
    height: 155
    visible: true

    function getColor(num){
        if (num > 60) {
            return "#00ff00"
        }
        if (num > 20) {
            return "#ffff00"
        }
        return "#ff0000"
    }

    Rectangle {
        id: mainBatteryLevel
        x: 0
        y: 5
        width: 280*backEnd.soc/100
        height: 60
        color: getColor(backEnd.soc)
        anchors.right: mainBattery.right
        anchors.rightMargin: 14
        transformOrigin: Item.Center
    }

    Image {
        id: mainBattery
        x: 102
        y: 2
        width: 304
        height: 67
        source: "Images/Supplemental SoC.svg"
    }

    Text {
        id: mainVoltage
        x: 374
        y: 2
        width: 184
        height: 75
        color: "#ffffff"
        text: backEnd.pack_voltage.toFixed(1)
        font.pixelSize: 52
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Regular"
        font.family: "Work Sans"
    }

    Text {
        x: 525
        y: 12
        width: 50
        height: 50
        color: "#ffffff"
        text: "V"
        font.pixelSize: 48
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Work Sans"
        font.styleName: "Regular"
    }

	Rectangle {
        id: suppBatteryLevel
	    x: 0
        y: 80
        width: 280*backEnd.est_supplemental_soc/100
	    height: 60
        color: getColor(backEnd.est_supplemental_soc)
        anchors.right: suppBattery.right
	    anchors.rightMargin: 14
	    transformOrigin: Item.Center
	}

	Image {
        id: suppBattery
        x: 102
        y: 77
	    width: 304
	    height: 67
	    source: "Images/Supplemental SoC.svg"
    }

    Text {
        id: suppVoltage
        x: 374
        y: 77
	    width: 184
	    height: 75
	    color: "#ffffff"
        text: backEnd.supplemental_voltage.toFixed(1)
        font.pixelSize: 52
	    horizontalAlignment: Text.AlignHCenter
	    verticalAlignment: Text.AlignVCenter
        font.styleName: "Regular"
        font.family: "Work Sans"
    }

    Text {
        x: 525
        y: 87
        width: 50
        height: 50
        color: "#ffffff"
        text: "V"
        font.pixelSize: 48
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Work Sans"
        font.styleName: "Regular"
    }

    Text {
        id: mainLabel
        x: -38
        y: 2
        width: 184
        height: 75
        color: "#ffffff"
        text: "Main"
        font.pixelSize: 32
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Text {
        id: suppLabel
        x: -38
        y: 73
        width: 184
        height: 75
        color: "#ffffff"
        text: "Supp"
        font.pixelSize: 32
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Light"
        font.family: "Work Sans"
    }

    Text {
        id: mainCharge
        x: 187
        y: 2
        width: 184
        height: 75
        color: "#ffffff"
        text: backEnd.soc.toFixed(1) + " %"
        font.pixelSize: 32
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        style: Text.Outline
        font.styleName: "Regularh"
        font.family: "Work Sans"
    }

    Text {
        id: suppCharge
        x: 187
        y: 73
        width: 184
        height: 75
        color: "#ffffff"
        text: backEnd.est_supplemental_soc.toFixed(1) + " %"
        font.pixelSize: 32
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        style: Text.Outline
        font.styleName: "Regular"
        font.family: "Work Sans"
    }

}
