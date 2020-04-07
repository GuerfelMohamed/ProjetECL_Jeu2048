import QtQuick 2.0



Rectangle {

    property int taille: 400
    property int gridSpacing: 10
    color: "#bbada0"
    radius: 5

    width: taille
    height: taille


    id: gr


    focus: true

    Keys.onPressed: {
        if (event.key===Qt.Key_Up) {/*Key UP clicked movment*/}
        if (event.key===Qt.Key_Right) {/* Key Right movment*/}
        if (event.key===Qt.Key_Left) {/* Key Left movement*/}
        if (event.key===Qt.Key_Down) {/*Key Down movement*/}
    }


    Grid {
        y: 10
        anchors.horizontalCenter: parent.horizontalCenter
        rows: 4
        columns: 4
        spacing: 10

        Repeater {
            model: {/*model of Grid here ??!*/}
            delegate: Cellule {
                value: display
                state : display
            }
        }
    }

    Text {
        text: {
            // Game over
            //  if win print you win else game over
        }
        font.pointSize: 40
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
     }

}

