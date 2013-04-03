import QtQuick 1.0

VisualItemModel {
         id: itemModel

         Rectangle {
             width: view.width; height: view.height
             color: "#FFFEF0"
             Text { text: "Page 1"; font.bold: true; anchors.centerIn: parent }

             Component.onDestruction: print("destroyed 1")
         }
         Rectangle {
             width: view.width; height: view.height
             color: "#F0FFF7"
             Text { text: "Page 2"; font.bold: true; anchors.centerIn: parent }

             Component.onDestruction: print("destroyed 2")
         }
         Rectangle {
             width: view.width; height: view.height
             color: "#F4F0FF"
             Text { text: "Page 3"; font.bold: true; anchors.centerIn: parent }

             Component.onDestruction: print("destroyed 3")
         }
     }
