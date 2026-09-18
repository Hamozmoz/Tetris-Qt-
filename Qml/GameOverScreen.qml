import QtQuick

Loader{
id : gameOverScreenroot
sourceComponent:
Rectangle{
    id : gameOverScreenBackground
    property real backgroundHeightPiece : height/10
    property real backgroundWidthPiece : width/10
    color: "gray"
    opacity: 0.8
    height: gameOverScreenroot.height
    width: gameOverScreenroot.width
    radius : width / 8
Text {
    text : "You Lost!"
    color : "white"
    font.family: "consolas"
    font.pixelSize: window.width/39 + 7
    anchors.horizontalCenter: gameOverScreenBackground.horizontalCenter
}
Text{
    text : "Score :  " + TetriminoManager.Score
    color : "white"
    font.family: "consolas"
    font.pixelSize: window.width/39
    anchors.verticalCenter: gameOverScreenBackground.verticalCenter



}
Button{
    anchors.bottom: gameOverScreenBackground.bottom
    anchors.horizontalCenter: gameOverScreenBackground.horizontalCenter
   text : "Exit"
   onButtonClicked: {
       TetriminoManager.exitGame()

   }
}

}
}


