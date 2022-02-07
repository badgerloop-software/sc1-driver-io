import QtQuick 2.4

Item {

    function getColor(cruise) {
        if(cruise)
            return "#40C321"
        else
            return "#ffffff"
    }

    width: 400
    height: 400

    Image {
        id: image
        x: 0
        y: 0
        width: 400
        height: 400
        source: "Images/Cruise.png"
        fillMode: Image.PreserveAspectFit
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 400
        height: 400
        color: getColor(backEnd.cruise)
        z: -1
    }
}
