import QtQuick 1.0

 Rectangle {
     width:400; height: 400
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
             width: listView.width; height: 55
             //clip: true
             Row {
                 anchors.verticalCenter: parent.verticalCenter
                 spacing: 10
                 //Text { text: name }
                 //Text { text: '$' + cost }

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
 }
