import QtQuick

Loader {

id : rootButton
property string text : "Nothing"
property color buttonColor : "black"
signal buttonPressed
signal buttonReleased
signal buttonClicked
    sourceComponent:
    Rectangle{
        id : buttonBackground
    color : buttonColor

    width: window.width/8
    height : window.height/10
    border.color: "white"

    MouseArea{
        id : mouse
        anchors.fill: buttonBackground
    hoverEnabled: true

        onPressed : {
            rootButton.buttonPressed()
                            buttonBackground.color = "gray"
                   }
        onReleased: {
            rootButton.buttonReleased()
                        buttonBackground.color = buttonColor
                    }
        onClicked: {
            rootButton.buttonClicked()
        }

    }

    Text{
        id : buttonText
        text: rootButton.text
        anchors.centerIn: buttonBackground
        color : "white"
        font.family: "consolas"
        font.pixelSize: window.width / 44 +3
    }
    }
}
