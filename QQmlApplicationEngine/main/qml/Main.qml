import QtQuick
import QtQuick.Controls

Window {
    objectName: "rootWindow"
    id: rootId
    width: 640
    height: 480
    visible: true
    title: qsTr("QQmlApplicationEngine getting started")

    Rectangle {
        id: rect1Id
        objectName: "rect"
        width: 100
        height: 100
        color: "green"
    }

    Rectangle {
        id: rect2Id
        objectName: "rect"
        anchors.top: rect1Id.bottom
        anchors.topMargin: 3
        width: 100
        height: 100
        color: "blue"
    }

    TextArea {
        id: textAreaId
        objectName: "myTextArea"
        text: qsTr("Some QML text")
        font.pointSize: 20
        anchors.left: rect1Id.right
    }

    Rectangle {
        id: rect3Id
        objectName: "rect3"
        anchors.left: rect1Id.right
        anchors.top: textAreaId.bottom
        color: "yellowgreen"
        width: rect4Id.width // Binding is defined here
        height: 100
    }

    Rectangle {
        id: rect4Id
        anchors.left: rect1Id.right
        anchors.top: rect3Id.bottom
        objectName: "rect4"
        color: "beige"
        width: 100
        height: 100

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rect4Id.width = rect4Id.width + 20
            }
        }
    }
}
