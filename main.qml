import QtQuick 1.0

Rectangle {
    id : screen

    width: 400; height: 600
    color : "lightGrey"

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

    //Top Line

    Rectangle {
        id : search_line

        anchors.top : parent.top
        height: parent.height/10; width: parent.width
        color : "black"
        border.color: "grey"
        border.width: 2

        Glossy {}

        Button{
            text : "move"
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter


            onClicked: page_container.inSearchPage = !page_container.inSearchPage

        }
        SearchBox{
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Item {
        id: page_container

        width: parent.width; height: 9/10*parent.height
        anchors.top : search_line.bottom
        Image { source: "/images/stripes.png"; fillMode: Image.Tile; anchors.fill: parent; opacity: 0.3 }

        property bool inSearchPage : true

        Item{

            anchors.fill: parent
            anchors.margins: 5


            Rectangle {
                id : search_page

                color : "blue"
                radius: 5
                width : parent.width; height : parent.height

                ListView {
                    id : search_view
                    model : testModel
                    //width: parent.width; height: parent.height
                    anchors.fill : parent
                    delegate: CompanyDelegate {}
                    highlight: Rectangle{
                        color: "steelblue";
                        anchors.horizontalCenter: parent.horizontalCenter;
                        width: parent.width-10;
                        radius: 2
                    }
                }
            }

            Column {
                id : info_page

                width : parent.width; height : parent.height
                x : -(1.5*parent.width)
                spacing: 2


                Rectangle {
                    id : top
                    color: "lightblue"
                    radius: 5
                    width: parent.width; height: parent.height/2


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(info_page.state == "") info_page.state = "Down"
                            else if(info_page.state == "Up") info_page.state = ""
                        }
                    }
                }

                Rectangle {
                    id : bottom
                    color: "gold"
                    radius: 5
                    width: parent.width; height: parent.height/2

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(info_page.state == "") info_page.state = "Up"
                            else if(info_page.state == "Down") info_page.state = ""
                        }
                    }
                }

                states: [
                    State {
                        name: "Up"
                        PropertyChanges {target: bottom; height: 7/8*info_page.height}
                        PropertyChanges {target : top; height : 1/8*info_page.height}
                    },
                    State {
                        name : "Down"
                        PropertyChanges { target: top; height: 7/8*info_page.height}
                        PropertyChanges {target : bottom; height : 1/8*info_page.height}
                    }
                ]

                transitions: [
                    Transition {
                        from: "Up"
                        to: ""
                        reversible: true
                        NumberAnimation { target: top; property: "height" ;duration: 400}
                        NumberAnimation { target: bottom; property: "height" ;duration: 400}
                        NumberAnimation { target: txt; property: "opacity" ;duration: 400}
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

            states: State {
                name: "InfoPageState"; when: page_container.inSearchPage == false
                PropertyChanges { target: search_page; x: -(1.5*parent.width) }
                PropertyChanges { target: info_page; x: 0 }
            }

            transitions: Transition {
                from : ""
                to : "InfoPageState"
                reversible: true
                NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
            }

        }
    }
}


/*
Item {
    id : main_page
    width: 400; height: 600

    Item{

        id : container
        anchors.fill : parent

        property bool inSearchPage : false

        Rectangle {
            id : search_page

            color : "red"
            width: parent.width; height: parent.height
            x : (-parent.width*1.5)

            MouseArea {
                anchors.fill: parent
                onClicked: container.inSearchPage = false

            }

        }

        Column {
            id : info_page
            //anchors.horizontalCenter: parent.horizontalCenter
            //anchors.verticalCenter: parent.verticalCenter

            //spacing: 5

            Rectangle {
                id : top
                color: "lightblue"
                radius: 10.0
                width: main_page.width
                height: main_page.height/2

                Text {
                    id: txt
                    anchors.centerIn: parent
                    text : "TOP"
                    font.pixelSize: 72
                    opacity: 0.5
                }

                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: container.inSearchPage = true
                    onClicked: {
                        if(main_page.state == "")
                            main_page.state = "Down"
                        else if(main_page.state == "Up")
                            main_page.state = ""
                    }
                }

            }
            Rectangle {
                id : bottom
                color: "gold"
                radius: 10.0
                width: main_page.width
                height: main_page.height/2

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(main_page.state == ""){
                            main_page.state = "Up"
                        }
                        else if(main_page.state == "Down")
                            main_page.state = ""
                    }
                }
            }
        }

        states: State {
            name: "SearchPageState"; when: container.inSearchPage == true
            PropertyChanges { target: search_page; x: 0 }
            PropertyChanges { target: info_page; x: -(1.5*parent.width) }
        }

        transitions: Transition {
            from : ""
            to : "SearchPageState"
            reversible: true
            NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
        }

    }
    states: [
        State {
            name: "Up"
            PropertyChanges { target: bottom; height: 500}
            PropertyChanges {target : top; height : 100}
            PropertyChanges {target : txt; opacity : 0.0}

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
            NumberAnimation { target: txt; property: "opacity" ;duration: 400}
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

*/


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
