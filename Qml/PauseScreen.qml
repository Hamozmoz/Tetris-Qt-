import QtQuick

Loader {
id :rootPauseScreen
sourceComponent:
Item{
Rectangle{
    id : pauseBackground
   height : rootPauseScreen.height
   width : rootPauseScreen.width
   color : "#282A36"
 opacity: 0.55
 z : 1
 MouseArea{
     anchors.fill: pauseBackground
     onPressed:(mouse)=> {
         mouse.accepted = true;
     }
     onReleased: (mouse)=> {
        mouse.accepted = true;
                 }
     onClicked: (mouse)=>{
                    mouse.accepted = true;
                }
 }

}
 Rectangle{
     radius: width/7
     id: pauseMenu
     z : pauseBackground.z +1
     anchors.centerIn: pauseBackground
     color : "black"
     height: rootPauseScreen.height/3
     width : rootPauseScreen.width/5
     property real heightPiece : height/20

     Button{
         id : continueButton
         anchors.horizontalCenter: pauseMenu.horizontalCenter
         text: "Continue"
         y : pauseMenu.heightPiece *4
         onButtonClicked: {
              GameManager.changeGamePaused()
         }
     }
     Button {
         id : exitButton
         anchors.horizontalCenter: pauseMenu.horizontalCenter
         text: "Exit"
         y : pauseMenu.heightPiece *12
         onButtonClicked: {
              TetriminoManager.exitGame()
              GameManager.changeGamePaused()
         }
     }

 }
}
}
