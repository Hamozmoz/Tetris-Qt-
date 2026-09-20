import QtQuick

Item {
id : displayBoxRoot
property alias title : titleText.text
property int tetriminoType : 7
property string tetriminoColor : "black"
Rectangle{
id : titleBackground
color : "grey"
width: displayBoxRoot.width
height: displayBoxRoot.height/6
topLeftRadius: width/8
topRightRadius: width/8
Text{
id :titleText
text : "None"
color : "white"
anchors.centerIn: titleBackground
font.pixelSize: 24
fontSizeMode: Text.Fit
}
Rectangle{
id : displayBoxBackground
color: "black"
border.color: "white"
width : displayBoxRoot.width
height: displayBoxRoot.height - titleBackground.height
anchors.top: titleBackground.bottom
property real tileWidth : width /6
property real tileHeight : height/6

Rectangle{
id : firstPiece
color : tetriminoColor
x : displayBoxBackground.tileWidth*2
y : displayBoxBackground.tileHeight
border.color: "white"
visible: tetriminoColor == "black"?false:true
width: displayBoxBackground.tileWidth
height: displayBoxBackground.tileHeight
Rectangle{
id : secondPiece
color : tetriminoColor
border.color: "white"
width: firstPiece.width
height: firstPiece.height
x : {
tetriminoType === 0 ? 0 :
tetriminoType === 1 ? -width :
tetriminoType === 2 ? 0 :
tetriminoType === 3 ? 0 :
tetriminoType === 4 ? width :
tetriminoType === 5 ? width :
tetriminoType === 6 ? width : 0
}
y : {
tetriminoType === 0 ? height :
tetriminoType === 1 ? height :
tetriminoType === 2 ? height :
tetriminoType === 3 ? height :
tetriminoType === 4 ? 0 :
tetriminoType === 5 ? 0 :
tetriminoType === 6 ? 0 : 0
}
}
Rectangle{
id : thirdPiece
color : tetriminoColor
border.color: "white"
width: firstPiece.width
height: firstPiece.height
x : {
tetriminoType === 0 ? 0 :
tetriminoType === 1 ? 0 :
tetriminoType === 2 ? 0 :
tetriminoType === 3 ? 0 :
tetriminoType === 4 ? -width :
tetriminoType === 5 ? width :
tetriminoType === 6 ? 0 : 0
}
y : {
tetriminoType === 0 ? height*2 :
tetriminoType === 1 ? height :
tetriminoType === 2 ? height*2 :
tetriminoType === 3 ? height*2 :
tetriminoType === 4 ? height :
tetriminoType === 5 ? height :
tetriminoType === 6 ? height : 0
}
}
Rectangle{
id : fourthPiece
color : tetriminoColor
border.color: "white"
width: firstPiece.width
height: firstPiece.height
x : {
tetriminoType === 0 ? 0 :
tetriminoType === 1 ? width :
tetriminoType === 2 ? width :
tetriminoType === 3 ? -width :
tetriminoType === 4 ? 0 :
tetriminoType === 5 ? width*2 :
tetriminoType === 6 ? width : 0
}
y : {
tetriminoType === 0 ? height*3 :
tetriminoType === 1 ? height :
tetriminoType === 2 ? height*2 :
tetriminoType === 3 ? height*2 :
tetriminoType === 4 ? height :
tetriminoType === 5 ? height :
tetriminoType === 6 ? height : 0
}
}
}
}
}
}

