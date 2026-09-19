import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Tetris

Window {
id : window
visible : true
title : "Tetris"
visibility: "FullScreen"


onClosing: (close) =>{
close.accepted = false
GameManager.quitGame()
}

Rectangle {
   width : window.width
   height : window.height
    color : "#282A36"
}
Loader{
    active:GameManager.CurrentGameState === GameManager.GameRunning? true:false
    focus: GameManager.CurrentGameState === GameManager.GameRunning? true:false
    sourceComponent:
GameGrid{
    id: gameGrid

}
}
Loader{
    active: GameManager.CurrentGameState === GameManager.OpeningScreen? true : false
    sourceComponent:
OpeningScreen {
    id : openingScreen
focus : false
}
}
PauseScreen{
active : GameManager.GamePaused?true:false
width : window.width
height : window.height
}

Item{
id : windowResizer
focus : GameManager.CurrentGameState === GameManager.OpeningScreen? true : false
Keys.onPressed: (event)=>{
if(event.key === Qt.Key_Enter && event.modifiers === Qt.AltModifier)
if(window.visibility === "FullScreen"){
window.visibility = "Maximized"
}else{
window.visibility = "FullScreen"
}
}
}

}



