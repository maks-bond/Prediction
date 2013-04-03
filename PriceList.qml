import QtQuick 1.1

ListView {
    id: listView
    //anchors.fill: parent
    //anchors.bottomMargin: 40

    header: bannercomponent
    delegate: priceDelegate
    focus: true
    highlight: highlightBar
    highlightFollowsCurrentItem: false

    Component {     //instantiated when header is processed
         id: bannercomponent
         Rectangle {
             id: banner
             width: listView.width
             height: 60
             gradient: Gradient {
                 id: clubcolors
                 GradientStop { position: 0.0; color: "darkGrey"}
                 GradientStop { position: 0.7; color: "#343434"}
             }
             Text {
                 x: 5 ; y: 5
                 text: "Company: Adobe, items:" + listView.count
                 font.pixelSize: 25
                 color : "white"
             }
         }
     }

    Component {
        id: highlightBar
        Rectangle {
            width: 200; height: 50
            color: "lightsteelblue"
            radius: 3
            y: listView.currentItem.y;
            Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
        }
    }

    Component{
        id : priceDelegate
        Item {
            id: wrapper
            width: 200; height: 55
            Column {
                Text { text: "Date: " + date; color : "white"; }
                Text { text: "Price: " + price; color : "white"; }
            }
            // indent the item if it is the current item
            states: State {
                name: "Current"
                when: wrapper.ListView.isCurrentItem
                PropertyChanges { target: wrapper; x: 20 }
            }
            transitions: Transition {
                NumberAnimation { properties: "x"; duration: 200 }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: wrapper.ListView.view.currentIndex = index
            }
        }
    }
}
