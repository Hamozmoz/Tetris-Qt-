import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Tetris

Window {
id : window
visible : true
title : "Tetris"
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
    focus: GameManager.CurrentGameState === GameManager.OpeningScreen? true : false
    active: GameManager.CurrentGameState === GameManager.OpeningScreen? true : false
    sourceComponent:
OpeningScreen {
    id : openingScreen

}
}
}

