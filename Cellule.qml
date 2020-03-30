import QtQuick 2.0


Rectangle {

    id: tile
    property string value: ""
    property int size: 88
    property int taillePolice: 15
    width: size
    height: size

    color: "#c8cbc2"
    radius: 10

    Text {
        id: val
        text: value
        font.pointSize: taillePolice
        anchors.centerIn: parent
        color: "black"
    }

    states:[
    State{
            name:"0"
            PropertyChanges{target : tile; color: "#c8cbc2"}
            PropertyChanges{target: val; color: "#c8cbc2"}
        },
    State{
            name:"2"
            PropertyChanges{target : tile; color: "#e1d2c4"}
        },
    State{
            name:"4"
            PropertyChanges{target : tile; color: "#e9dbb8"}
        },
    State{
            name:"8"
            PropertyChanges{target : tile; color: "#ea9366"}
        },

    State{
            name:"16"
            PropertyChanges{target : tile; color: "#f16c34"}
        },

    State{
            name:"32"
            PropertyChanges{target : tile; color: "#d44c12"}
        },
    State{
            name:"64"
            PropertyChanges{target : tile; color: "#b62d00"}
        },
    State{
            name:"128"
            PropertyChanges{target : tile; color: "#f4e776"}
        },
    State{
            name:"256"
            PropertyChanges{target : tile; color: "#e4d135"}
        },
    State{
            name:"512"
            PropertyChanges{target : tile; color: "#e3cf0f"}
        },
    State{
            name:"1024"
            PropertyChanges{target : tile; color: "#cfbb05"}
        },
    State{
            name:"2048"
            PropertyChanges{target : tile; color: "#eb2525"}
        }

    ]
}
