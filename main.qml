import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 720
    height: 480
    color: "#f8c77a"
    title: qsTr("Jeu 2048")

    Grille {
        id: grille
        x: 138
        y: 40
    }

    Menu {
        id: menu
        x: 0
        y: 0
    }
}
