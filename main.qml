import QtQuick 1.0

Item {
    id : main_form
    width: 400; height: 600

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter

        //spacing: 5

        Rectangle {
            id : top
            color: "lightblue"
            radius: 10.0
            width: main_form.width
            height: main_form.height/2

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(main_form.state == "")
                        main_form.state = "Down"
                    else if(main_form.state == "Up")
                        main_form.state = ""
                }
            }

        }
        Rectangle {
            id : bottom
            color: "gold"
            radius: 10.0
            width: main_form.width
            height: main_form.height/2

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(main_form.state == ""){
                        main_form.state = "Up"
                    }
                    else if(main_form.state == "Down")
                        main_form.state = ""
                }
            }
        }
    }
    states: [
        State {
            name: "Up"
            PropertyChanges { target: bottom; height: 500}
            PropertyChanges {target : top; height : 100}
        },
        State {
            name : "Down"
            PropertyChanges { target: top; height: 500}
            PropertyChanges {target : bottom; height : 100}
        }
    ]
    transitions: [
        Transition {
            from: "Up"
            to: ""
            reversible: true
            NumberAnimation { target: top; property: "height" ;duration: 400}
            NumberAnimation { target: bottom; property: "height" ;duration: 400}
        },
        Transition {
            from: "Down"
            to: ""
            reversible: true
            NumberAnimation { target: top; property: "height" ; duration: 400}
            NumberAnimation { target: bottom; property: "height" ; duration: 400}
        }
    ]
}




/*
Rectangle {
    color: "#343434"
    width: 400
    height: 600

    ListModel {
         id : testModel
         ListElement {
             date: "Bill Smith"
             price: "555 3264"
         }
         ListElement {
             date: "John Brown"
             price: "555 8426"
         }
         ListElement {
             date: "Sam Wise"
             price: "555 0473"
         }
     }

    VisualItemModel {
        id: itemModel

        PriceList {
            model : mModel
            width: view.width; height: view.height

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

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: 40;}
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 2000
        cacheBuffer: 200
    }

    Rectangle {
        width: parent.width; height: 40
        anchors { top: view.bottom; bottom: parent.bottom }
        color : "black"

        Row {
            anchors.centerIn: parent
            spacing: 20

            Button {
                anchors.verticalCenter: parent.verticalCenter
                x : 10
                text : "Forecast"
            }

            Repeater {
                model: itemModel.count

                Rectangle {
                    width: 5; height: 5
                    radius: 3
                    color: view.currentIndex == index ? "darkGrey" : "white"

                    MouseArea {
                        width: 20; height: 20
                        anchors.centerIn: parent
                        onClicked: view.currentIndex = index
                    }
                }
            }
        }
    }
}
*/
