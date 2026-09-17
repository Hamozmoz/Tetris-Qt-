import QtQuick
import Tetris
FocusScope {
focus : true
    id : gamegridroot
width : window.width /3
height: window.height
x : width
property int columns : TetriminoManager.GameGrid.columns
property int rows : TetriminoManager.GameGrid.rows
property real tileWidth :width /columns
property real tileHeight :height /rows
Repeater{
    model : TetriminoManager.GameGrid
Rectangle{
id : tile
    objectName: "GameTile : " + index
    property int currentrow: Math.floor(index/gamegridroot.columns)
    property int currentcolumn : index % gamegridroot.columns
    color : {model.Color === GameMatrix.Null? "#000000":
             (model.Color === GameMatrix.Red || model.Color === GameMatrix.TetreRed) ? "#c71585":
             (model.Color === GameMatrix.Blue|| model.Color === GameMatrix.TetreBlue)? "royalblue":
             (model.Color === GameMatrix.Purple|| model.Color === GameMatrix.TetrePurple)? "#e79aff":
             "#90ee90"
    }
    opacity: model.Transperancy === GameMatrix.Opaque? 1:0.5
        border.color: model.Color === GameMatrix.Null? "#242323": "white"
        border.width:width >32 ? width / 32 : 1
        width : tileWidth
        height : tileHeight
        x : width * currentcolumn
        y : height * currentrow
    Loader {
active : TetriminoManager.DebugMode?true:false
anchors.fill: tile

sourceComponent: MouseArea{
 anchors.fill: parent
onReleased: {
        TetriminoManager.changeTileColor(index)
}
}
        }



}
}

Button{
 x : gamegridroot.width
 y : tileHeight *3
    active: TetriminoManager.DebugMode?true:false
    text : "LineCheck"
    onButtonReleased: {
        TetriminoManager.checkLines()
    }
}

Item{
    focus : true
    Keys.onPressed:  (event)=> {
                         if(event.key === Qt.Key_Left || event.key === Qt.Key_A){
                             TetriminoManager.moveTetrimino(TetriminoManager.Left)
                            event.accepted = true
                         }else if(event.key === Qt.Key_Right || event.key === Qt.Key_D){
                             TetriminoManager.moveTetrimino(TetriminoManager.Right)
                            event.accepted = true
                         }else if((event.key === Qt.Key_Down || event.key === Qt.Key_S) && !event.isAutoRepeat){

                             TetriminoManager.changeFastDropToTrue()
                          }else if (event.key === Qt.Key_Up || event.key === Qt.Key_W){
                               TetriminoManager.rotateTetrimino()
                             }
                     }
Keys.onReleased: (event)=> {
                     if((event.key === Qt.Key_Down || event.key === Qt.Key_S) && !event.isAutoRepeat){
            TetriminoManager.changeFastDropToFalse()
                     }else if(event.key ===Qt.Key_Escape){
                         GameManager.changeGamePaused()
                     }


                     }

                 }

Rectangle{
    objectName: "Score Text "
        anchors.top:  gamegridroot.top
        anchors.left: gamegridroot.right

    Text{
        width : parent.width *3
        height: parent.height
      font.family: "Consolas"
      font.pixelSize: window.width /43 +3

        text : "Score : " + TetriminoManager.Score
        color : "white"
    }

}

}



