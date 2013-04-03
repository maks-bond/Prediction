 import QtQuick 1.0

 Rectangle {
     property alias text: textItem.text

     width: 100; height: 20
     //border.width: 1
     radius: 2
     smooth: true

     gradient: Gradient {
         GradientStop { position: 0.0; color: "darkGrey" }
         GradientStop { position: 0.66; color: "#343434" }

     }

     Text {
         id: textItem
         anchors.centerIn: parent
         font.pointSize: 13
         color: "white"
     }

 }
