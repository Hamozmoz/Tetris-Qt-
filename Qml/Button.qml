import QtQuick

Item {
    Rectangle{

        id : buttonBackground
    color : "black"

    width: 120
    height : 100
    border.color: "white"

    MouseArea{
        anchors.fill: buttonBackground
    hoverEnabled: true

        onPressed : {
                            buttonBackground.color = "gray"
                   }
        onReleased: {
                        buttonBackground.color = "black"
                    }
    }

    Text{
        text: "Nothing"
        anchors.centerIn: buttonBackground
        color : "white"
    }
    }
}
