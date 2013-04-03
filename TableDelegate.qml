import QtQuick 1.0

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

