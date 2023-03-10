import QtQuick 2.0
import QtQuick.Layouts

Window {
    width: 500
    height: 500

    // left-top
    Rectangle {
        id: rect1;
        width: parent.width * 0.375
        height: parent.height * 0.375

        color: "#880000"
        Text {
            anchors.centerIn: parent
            text: qsTr("color: \"#880000\"")
        }
    }

    // right-top
    Rectangle {
        id: rect2;
        width: parent.width * 0.375
        height: parent.height * 0.375

        anchors.left: rect1.right
        anchors.leftMargin: parent.width * 0.25

        color: "#FF0000"
        Text {
            anchors.centerIn: parent
            text: qsTr("color: \"#FF0000\"")
        }
    }

    // right-bottom
    Rectangle {
        id: rect3;
        width: parent.width * 0.375
        height: parent.height * 0.375

        anchors.top: rect1.bottom
        anchors.topMargin: parent.height * 0.25

        anchors.left: rect1.right
        anchors.leftMargin: parent.width * 0.25

        color: "#008800"
        Text {
            anchors.centerIn: parent
            text: qsTr("color: \"#008800\"")
        }
    }

    // left-bottom
    Rectangle {
        id: rect4;
        width: parent.width * 0.375
        height: parent.height * 0.375

        anchors.top: rect1.bottom
        anchors.topMargin: parent.height * 0.25

        color: "#00FF00"
        Text {
            anchors.centerIn: parent
            text: qsTr("color: \"#00FF00\"")
        }
    }

    // center
    Rectangle {
        id: rect5;
        width: parent.width * 0.375
        height: parent.height * 0.375

        anchors.centerIn: parent
        color: "royalblue"
        radius: 25
        rotation: -45
        Text {
            anchors.centerIn: parent
            text: qsTr("color: \"royalblue\"\nradius: 25\nrotation: -45")
        }
    }
}
