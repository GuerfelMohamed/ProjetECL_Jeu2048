import QtQuick 2.0

import QtQuick.Controls 1.6

Item {
    id: element3
    width: 720
    height: 480
    Text {
        id: element
        x: 561
        width: 138
        text: qsTr("2048")
        anchors.top: parent.top
        anchors.topMargin: 21
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 381
        anchors.right: parent.right
        anchors.rightMargin: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 44
    }

    Rectangle {
        id: scorerect
        x: 561
        y: 189
        width: 138
        height: 79
        color: "#ffffff"
        anchors.rightMargin: 20

        Text {
            id: score
            text: qsTr("Text")//get_score
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

    Text {
        id: element1
        x: 561
        y: 105
        width: 138
        height: 78
        text: qsTr("SCORE")
        anchors.rightMargin: 20
        font.pixelSize: 24
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Rectangle {
        id: bestrect
        x: 561
        y: 358
        width: 138
        height: 79
        color: "#ffffff"
        anchors.rightMargin: 20

        Text {
            id: best
            text: qsTr("Text")//get_best
            anchors.fill: parent
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Text {
        id: element2
        x: 561
        y: 274
        width: 138
        height: 78
        text: qsTr("BEST")
        anchors.rightMargin: 20
        font.pixelSize: 24
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }

    Button {
        id: btntroi
        width: 120
        text: qsTr("3x3")
        anchors.top: parent.top
        anchors.topMargin: 21
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 389
        anchors.left: parent.left
        anchors.leftMargin: 8
        onClicked:{
            //trois();

        }
    }

    Button {
        id: btnquatre
        x: 8
        y: 97
        width: 120
        height: 70
        text: qsTr("4x4")
        onClicked:{
            //quatre();

        }
    }

    Button {
        id: btncinq
        x: 8
        y: 173
        width: 120
        height: 70
        text: qsTr("5x5")
        onClicked:{
            //cinq();

        }
    }

    Button {
        id: btnback
        x: 8
        y: 249
        width: 120
        height: 70
        text: qsTr("RETOUR")
        onClicked:{
            //retour();

        }
    }

    Button {
        id: btnew
        x: 8
        y: 325
        width: 120
        height: 70
        text: qsTr("NOUVELLE PARTIE")
        onClicked:{
            //newGame();

        }
    }

    Button {
        id: btnquit
        x: 8
        y: 402
        width: 120
        height: 70
        text: qsTr("QUITTER")
        onClicked: Qt.quit()
    }

}

/*##^##
Designer {
    D{i:1;anchors_height:78;anchors_y:21}D{i:3;anchors_x:58;anchors_y:33}D{i:6;anchors_x:58;anchors_y:33}
D{i:8;anchors_height:70;anchors_x:8;anchors_y:21}
}
##^##*/
