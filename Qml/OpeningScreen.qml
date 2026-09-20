import QtQuick
import Tetris
FocusScope {
    id:openingScreenRoot
    focus : true

   objectName: "OpeningScreen"
   Rectangle{
       id: blackBackground

    width:  window.width
    height: window.height
    color : "black"
    property real screenPieceWidth: width/30
    property real screenPieceHeight: height/30
Text{
    id: titleText
text: "Tetris\n    Game"
color :"#c71585"
font.family: "consolas"
x : blackBackground.screenPieceWidth *9
font.pixelSize: blackBackground.width /10 + 2
SequentialAnimation{
    running : true
    loops : Animation.Infinite
    PropertyAnimation{
        property: "color"
        target: titleText
        from: "#c71585"
        to : "royalblue"
        duration : 1000
    }

    PauseAnimation {
        duration: 1000
    }
    PropertyAnimation{
        property: "color"
        target: titleText
        from: "royalblue"
        to : "#e79aff"
        duration : 1000
}
    PauseAnimation {
        duration: 1000
    }
    PropertyAnimation{
        property: "color"
        target: titleText
        from: "#e79aff"
        to : "#90ee90"
        duration : 1000
}
    PauseAnimation {
        duration: 1000
    }
    PropertyAnimation{
        property: "color"
        target: titleText
        from: "#90ee90"
        to : "#c71585"
        duration : 1000
}
    PauseAnimation {
        duration: 1000
    }


}
}

Button{
    id : startButton
 text: "Start"
anchors.horizontalCenter: blackBackground.horizontalCenter
y : blackBackground.screenPieceHeight *22
onButtonClicked: {
    TetriminoManager.startGame()
}

}
Button {
id :quitButton
text: "Quit"
anchors.horizontalCenter: blackBackground.horizontalCenter
y : blackBackground.screenPieceHeight *26
onButtonClicked: {
GameManager.quitGame()
}
}

Button{
active: GameManager.DebugMode? true:false
x : 0
anchors.bottom: blackBackground.bottom
buttonColor:  TetriminoManager.DebugMode? "red" : "black"
text : "Debug"
onButtonReleased: {

TetriminoManager.changeDebugMode()


}

}
Text{
visible: GameManager.HighScore >0?true:false
id : highScoreText
text : "HighScore : " + GameManager.HighScore
color : "white"
x : blackBackground.width - width- width/10
anchors.bottom: blackBackground.bottom
font.pixelSize: blackBackground.width/30 +2
font.family: "consolas"
SequentialAnimation{
running: true
loops : Animation.Infinite
PropertyAnimation{
property: "scale"
target: highScoreText
from : 1
to : 1.1
duration : 600
}
PropertyAnimation{
property: "scale"
target: highScoreText
from : 1.1
to : 1
duration : 600
}

}
}
   }


}
