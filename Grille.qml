import QtQuick 2.0

// https://doc.qt.io/qt-5/qml-qtquick-gridview.html
// https://doc.qt.io/qt-5/qml-qtquick-grid.html

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
        if (event.key===Qt.Key_Up) {modelgrille.mvtH()}
        if (event.key===Qt.Key_Right) {modelgrille.mvtD()}
        if (event.key===Qt.Key_Left) {modelgrille.mvtG()}
        if (event.key===Qt.Key_Down) {modelgrille.mvtB()}
    }


    Grid {
        y: 10
        anchors.horizontalCenter: parent.horizontalCenter
        rows: modelgrille.get_Taille
        columns: modelgrille.get_Taille
        spacing: 10

        Repeater {
            model:modelgrille
            delegate: Cellule {
                value: display
                state : display
            }
        }
    }

    Text {
        text: modelgrille.get_text
        font.pointSize: 40
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
     }

}

