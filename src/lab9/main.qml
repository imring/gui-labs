import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls 2.15

Window {
    id: root
    width: 500
    height: 500
    
    property color currentColor: "red"

    // left-top
    Rectangle {
        id: rect1
        width: parent.width * 0.375
        height: parent.height * 0.375
        
        border.color: "transparent" 
        border.width: 2

        color: "#880000"
        Text {
            anchors.centerIn: parent
            font.pixelSize: 16
            color: "white"
            text: qsTr("К121-19")
        }

        RotationAnimation {
            id: rotation1
            target: rect1
            property: "rotation"
            from: 0
            to: 360
            duration: 1000
            loops: Animation.Infinite
            running: false
        }
        
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: parent.parent.width - parent.width
            drag.minimumY: 0
            drag.maximumY: parent.parent.height - parent.height

            onPressed: {
                parent.border.color = "black"
                rotation1.start()
            }

            onReleased: {
                parent.Drag.drop()
                parent.border.color = "transparent"
                rotation1.stop()
            }
        }
    }

    // right-top
    Rectangle {
        id: rect2;
        width: parent.width * 0.375
        height: parent.height * 0.375
        
        border.color: "transparent" 
        border.width: 2

        x: parent.width - width
        y: 0

        color: "#FF0000"
        Text {
            anchors.centerIn: parent
            text: qsTr("<a href=\"https://www.qt.io/\">https://www.qt.io/</a>")
            onLinkActivated: Qt.openUrlExternally(link)
        }

        RotationAnimation {
            id: rotation2
            target: rect2
            property: "rotation"
            from: 0
            to: 360
            duration: 1000
            loops: Animation.Infinite
            running: false
        }
        
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: parent.parent.width - parent.width
            drag.minimumY: 0
            drag.maximumY: parent.parent.height - parent.height

            onPressed: {
                parent.border.color = "black"
                rotation2.start()
            }

            onReleased: {
                parent.Drag.drop()
                parent.border.color = "transparent"
                rotation2.stop()
            }
        }
    }

    // right-bottom
    Rectangle {
        id: rect3;
        width: parent.width * 0.375
        height: parent.height * 0.375
        
        border.color: "transparent" 
        border.width: 2

        x: parent.width - width
        y: parent.height - height

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

        RotationAnimation {
            id: rotation3
            target: rect3
            property: "rotation"
            from: 0
            to: 360
            duration: 1000
            loops: Animation.Infinite
            running: false
        }
        
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: parent.parent.width - parent.width
            drag.minimumY: 0
            drag.maximumY: parent.parent.height - parent.height

            onPressed: {
                parent.border.color = "black"
                rotation3.start()
            }

            onReleased: {
                parent.Drag.drop()
                parent.border.color = "transparent"
                rotation3.stop()
            }
        }
    }

    // left-bottom
    Rectangle {
        id: rect4;
        width: parent.width * 0.375
        height: parent.height * 0.375
        
        border.color: "transparent" 
        border.width: 2

        x: 0
        y: parent.height - height

        color: "#00FF00"
        Text {
            anchors.centerIn: parent
            text: qsTr("color: \"#00FF00\"")
        }

        RotationAnimation {
            id: rotation4
            target: rect4
            property: "rotation"
            from: 0
            to: 360
            duration: 1000
            loops: Animation.Infinite
            running: false
        }
        
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: parent.parent.width - parent.width
            drag.minimumY: 0
            drag.maximumY: parent.parent.height - parent.height

            onPressed: {
                parent.border.color = "black"
                rotation4.start()
            }

            onReleased: {
                parent.Drag.drop()
                parent.border.color = "transparent"
                rotation4.stop()
            }
        }
    }

    // center
    Rectangle {
        id: rect5;
        width: parent.width * 0.375
        height: parent.height * 0.375
        
        border.color: "transparent" 
        border.width: 2

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        color: root.currentColor
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
        
        RotationAnimation {
            id: rotation5
            target: rect5
            property: "rotation"
            from: 0
            to: 360
            duration: 1000
            loops: Animation.Infinite
            running: false
        }
        
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.maximumX: parent.parent.width - parent.width
            drag.minimumY: 0
            drag.maximumY: parent.parent.height - parent.height

            onPressed: {
                parent.border.color = "black"
                rotation5.start()
            }

            onReleased: {
                parent.Drag.drop()
                parent.border.color = "transparent"
                rotation5.stop()
            }
        }
    }

    Row {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Repeater {
            model: ["red", "orange", "yellow", "green", "blue", "indigo", "violet"]

            delegate: Rectangle {
                width: 15
                height: 15
                color: modelData

                MouseArea {
                    anchors.fill: parent

                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: (mouse) => {
                        if (mouse.button === Qt.LeftButton) {
                            root.currentColor = modelData;
                        } else if (mouse.button === Qt.RightButton) {
                            root.currentColor = Qt.lighter(modelData);
                        }
                    }
                }
            }
        }
    }

    Button {
        text: "Quit"
        anchors.top: parent.top
        anchors.right: parent.right
        onClicked: { Qt.quit() }
    }
}
