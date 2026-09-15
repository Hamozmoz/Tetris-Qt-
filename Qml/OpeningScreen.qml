import QtQuick

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
Text{
    id: instructionText
text : "Please Press Space To Start ! "
color : "white"
x : titleText.x + blackBackground.screenPieceWidth
y : blackBackground.screenPieceHeight * 26
font.pixelSize: window.width / 37 + 3

SequentialAnimation{
    running : true
    loops: Animation.Infinite
    PropertyAnimation{
       property : "opacity"
       from: 1
       to : 0
       target: instructionText
       duration: 500
    }
    PropertyAnimation{
       property : "opacity"
       from: 0
       to : 1
       target: instructionText
       duration: 500
    }


}

}


   }

Item{
focus : true
Keys.onSpacePressed:  {
        TetriminoManager.startGame()
    }
}
}
