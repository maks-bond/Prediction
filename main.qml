import QtQuick 1.0

 Rectangle {
     width:400
     height: 400
     color: "#343434"

     ListModel {
        id: fruitModel
        ListElement {
              name: "Apple"
              cost: 2.45
        }
        ListElement {
            name: "Orange"
            cost: 3.25
        }
        ListElement {
            name: "Banana"
            cost: 1.95
        }
     }

     Component {
         id: fruitDelegate
         Item {
             id: delegateItem
             width: listView.width
             height: 55
             clip: true
             Column {
                  anchors.verticalCenter: parent.verticalCenter
                  Text {
                      text: name
                      font.pixelSize: 15
                      color: "white"
                  }
                  Text {
                      text: '$' + cost
                      color : "white"
                  }

              }

         }
     }

     ListView {
         id: listView
         anchors.fill: parent
         anchors.margins: 20
         model: fruitModel
         delegate: fruitDelegate
         highlight: Rectangle { color: "lightsteelblue"; radius: 3 }
         focus: true
     }


     Rectangle {
         id: mButton

         anchors { left: parent.left; bottom: parent.bottom; margins: 20 }


         property variant text
         signal clicked

         height: text.height + 10; width: text.width + 20
         //border.width: 1
         radius: 4

         gradient: Gradient {
             GradientStop {
                 position: 0.0
                 color: !mouseArea.pressed ? "#eeeeee" : "#888888"
             }
             GradientStop {
                 position: 1.0
                 color: !mouseArea.pressed ? "#888888" : "#333333"
             }
         }

         MouseArea {
             id: mouseArea
             anchors.fill: parent
             onClicked: container.clicked()
         }

         Text {
             id: text
             anchors.centerIn:parent
             font.pointSize: 10
             text: "Refresh"
         }
     }
 }
