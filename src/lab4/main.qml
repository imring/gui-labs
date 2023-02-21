import QtQuick 2.0
import QtQuick.Layouts

Window {
    width: 360
    height: 360

    ColumnLayout {
        spacing: 2
        anchors.centerIn: parent

        Text {
            text: qsTr("Воробець Віталій")
            color: "green"
            font.weight: Font.DemiBold
        }
        Text {
            text: qsTr("К121-19")
            color: "purple"
            font.italic: true
        }
    }
}
