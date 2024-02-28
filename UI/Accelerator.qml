import QtQuick 2.15



Item {
    width: 362
    height: 45

    /*function abs(val) {
        if(val>0)
            return val
        else
            return -val
    }

    function hsv2rgb(hue,saturation,value){
        //console.log(hue)
        var r,g,b,rp,gp,bp
        var c=value*saturation/10000
        var x=c*(1-abs((hue/60)%2-1))
        var m=value/100-c

        if(hue >= 0 && hue < 45) {
            rp=c
            gp=c*(hue/60)
            bp=0
        }
        if(hue >= 45 && hue < 60) {
            rp=c
            gp=c*(hue/60)
            bp=c*(hue/240)
        }

        if(hue >= 60 && hue < 120) {
            rp=0
            gp=c
            bp=c*(hue/120)
        }

        else if(hue >= 120 && hue < 180) {
            rp=0
            gp=c
            bp=c
        }

        else if(hue >= 180 && hue < 240) {
            rp=0
            gp=x
            bp=c
        }

        else if(hue >= 240 && hue < 300) {
            rp=x
            gp=0
            bp=c
        }

        else if(hue >= 300 && hue < 360) {
            rp=c
            gp=0
            bp=x
        }

        r=(rp+m)*255
        g=(gp+m)*255
        b=(bp+m)*255

        var rgbDec=Math.floor((r<<16)+(g<<8)+b)
        var str= rgbDec.toString(16);

        //when r=0
        if(str.length==4) {
            str="00"+str;
        }

        //when 0<r<16
        else if(str.length==5) {
            str = "0"+str;
        }

        return str;

    }

    //for mapping the accelerator value to desired hue
    function hue(x){
        return(172/(1+Math.pow(2.718,4*(x-2.5))))
    }

    //-50*e^-(2*(x-3.5))^2
    //for mapping the accelerator value to desired saturation
    function saturation(x) {
        return(-40*Math.pow(2.718,-(Math.pow(2*(x-3.5),2))))+100
    }
    */

    function bluebar(val) {
        return val>3.5?3.5:val
    }

    function redbar(val) {
        return val>3.5?val:0
    }

    Rectangle {
        id: acceleratorBlue
        x: 5
        y: 3
        width: 352*bluebar(backEnd.accelerator_pedal)/5
        height: 41
        color: "#00ffff"
    }

    Rectangle {
        id: acceleratorRed
        x:5
        y:3
        z: -1
        width: 352*redbar(backEnd.accelerator_pedal)/5
        height: 40
        color: "#ff0000"
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 362
        height: 45
        color: "#00000000"
        radius: 5
        border.color: "#ffffff"
        border.width: 5

        /*Text {
            x: rectangle.width/2
            y: rectangle.height/2
            width: 50
            color: "#00ffff"
            text: hsv2rgb(f((5-backEnd.accelerator)*24),100,100)
            font.pixelSize: 42
            font.styleName: "Regular"
            font.family: "Work Sans"
        }*/

        Rectangle {
            id: rectangle1
            x: 74
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle2
            x: 251
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle3
            x: 109
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle4
            x: 38
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle5
            x: 180
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle6
            x: 215
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle7
            x: 286
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle8
            x: 145
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle9
            x: 3
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle10
            x: 322
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle11
            x: 357
            y: 4
            width: 2
            height: 37
            color: "#ffffff"
        }
    }
}
