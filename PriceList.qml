import QtQuick 1.1

ListView {
    id: listView
    //anchors.fill: parent
    //anchors.bottomMargin: 40

    delegate: priceDelegate
    focus: true
    highlight: highlightBar
    highlightFollowsCurrentItem: false

    Component {
        id: highlightBar
        Rectangle {
            width: 200; height: 50
            color: "lightsteelblue"
            radius: 3
            y: listView.currentItem.y;
            Behavior on y { SpringAnimation { spring: 2; damping: 0.7 } }
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
