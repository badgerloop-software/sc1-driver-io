import QtQuick 2.4

DashboardUI {

    function getTextSize() {
        if(backEnd.mppt_contactor || backEnd.low_contactor || backEnd.motor_controller_contactor) {
            return 20
        }
        return 50
    }
    
    function getColor() {
        if(backEnd.mppt_contactor || backEnd.low_contactor || backEnd.motor_controller_contactor) {
            return "#ff0000"
        }
        return "#00ff00"
    }

    function getText() {
        if (backEnd.mppt_contactor || backEnd.low_contactor || backEnd.motor_controller_contactor) {
            var txt = "";
            if (backEnd.mppt_contactor) {
                txt += "MPPT Contactor\n";
            }
            if (backEnd.low_contactor) {
                txt += "Low Contactor\n";
            }
            if (backEnd.motor_controller_contactor) {
                txt += "Motor Controller Contactor";
            }
            return txt;
        }
        return "Ready";
    }

    Rectangle {
    id: contactor
    x: 0
    y: 0
    width: 400
    height: 200
    color: "#000000"
    Text {
        x: 20
        y: 20
        text: getText()
        color: getColor()
        font.pixelSize: getTextSize()
        font.styleName: "Medium"
        }
    }
}
