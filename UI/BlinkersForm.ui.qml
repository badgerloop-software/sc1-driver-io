import QtQuick 2.4

Item {
    width: 400
    height: 400

    Rectangle {
        id: background
        x: 0
        y: 0
        width: 400
        height: 400
        color: "#000000"
        border.color: "#000000"
        z: -1
    }

    Image {
        id: image
        x: 50
        y: 50
        width: 300
        height: 300
        source: "Images/Blinker.png"
        fillMode: Image.PreserveAspectFit
    }
}
