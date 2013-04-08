import QtQuick 1.0

Component{
    id : companyDelegate

    Item {
        id: wrapper
        width : 200; height: 55

        property real detailsOpacity : 0

        Rectangle {
            id : hightlight
            width: parent.width; height : parent.height;
            opacity: wrapper.detailsOpacity
            color: "steelblue"
        }

        Row {
            anchors.fill : parent
            anchors.margins: 10
            Column {
                Text { text: "Company name: "; color : "white"; font.pixelSize: 25}
                Text { text: "Price: "; color : "white"; }
            }
            Button{
                text : "close"
                opacity: wrapper.detailsOpacity
                //anchors.right: parent.right
                //anchors.leftMargin: 10
                //anchors.verticalCenter: parent.verticalCenter

                onClicked:{
                    if(wrapper.state == "Current")
                        wrapper.state = ""
                    else
                        wrapper.state = "Current"
                }
            }
            Button{
                text : "details"
                opacity: wrapper.detailsOpacity
                //anchors.right: parent.right
                //anchors.leftMargin: 10
                //anchors.verticalCenter: parent.verticalCenter

            }
        }
        // indent the item if it is the current item
        states: State {
            name: "Current"
            when: wrapper.ListView.isCurrentItem
            //PropertyChanges { target: wrapper; x: 20 }
            PropertyChanges { target: wrapper; height: 200 }
            PropertyChanges { target: wrapper; detailsOpacity: 1 }
            //PropertyChanges {target : wrapper; color: "black"}
        }
        transitions: Transition {
            from: "Current"
            to : ""
            reversible: true
            ParallelAnimation{
                //NumberAnimation { properties: "x"; duration: 200 }
                NumberAnimation {properties: "height"; duration:  200}
                NumberAnimation {properties: "detailsOpacity"; duration:  200}
                //ColorAnimation { from: "black"; to: "steelblue"; duration: 200 }
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: wrapper.ListView.view.currentIndex = index
        }
    }
}
