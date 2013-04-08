 import QtQuick 1.0

 Rectangle {
     id : container
     property alias text: textItem.text

     signal clicked

     width: 60; height: 25
     radius: 1
     smooth: true
     color : "steelblue"

     Glossy{}

     MouseArea {
         id : mouseRegion
         anchors.fill : parent
         onClicked: {container.clicked();}
     }

     Text {
         id: textItem
         anchors.centerIn: parent
         font.pointSize: 13
         color: "white"
         style: Text.Raised
         styleColor: "black"
     }

     states: [
         State {
             name: "Pressed"
             when: mouseRegion.pressed == true
             PropertyChanges { target: container; opacity: 0.5 }
         }
     ]

 }
