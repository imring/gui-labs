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
            font.pixelSize: 16
            color: "white"
            text: qsTr("К121-19")
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
            text: qsTr("<a href=\"https://www.qt.io/\">https://www.qt.io/</a>")
            onLinkActivated: Qt.openUrlExternally(link)
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
            height: parent.height
            width: parent.width
            font.italic: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            color: "white"
            text: qsTr("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.")
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
            height: parent.height
            width: parent.width
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            text: qsTr("Воробець Віталій")
        }
    }
}