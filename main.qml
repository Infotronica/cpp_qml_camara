import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import Camara.CPP 1.0

Window {
    visible: true
    visibility: Window.Maximized
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

        CamaraCPP {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
