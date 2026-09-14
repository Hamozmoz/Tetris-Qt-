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

GameGrid{
    focus: GameManager.CurrentGameState === GameManager.GameRunning? true:false

}
Item {
    id : openingScreenInputHandler
    focus: GameManager.CurrentGameState === GameManager.OpeningScreen? true : false

    Keys.onSpacePressed:  {
        TetriminoManager.startGame()
    }

}
}

