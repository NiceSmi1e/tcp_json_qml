import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 320
    height: 480
    title: qsTr("TCP JSON QML")

    ListModel {
        id: name_latitude
    }

    Component {
        id: mDelegate
        Rectangle {
            border {color: "black"; width: 1}
            implicitWidth: 320
            implicitHeight: 75
            Row {
                spacing: 25
                Text { text: name; font.pixelSize: 24; anchors.verticalCenter: parent.verticalCenter; width: 210;}
                Rectangle { radius: 75/2
                    color: {
                        if (lat > 0) {
                            return "green";
                        }
                        else {
                            return "red";
                        }
                    }
                    border {color: "black"; width: 2}
                    width: 75; height: 75
                    Text {
                        anchors.centerIn: parent
                        text: lat
                        font.pixelSize: 12
                    }
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: name_latitude
        delegate: mDelegate
    }


    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label { id: statusBarText; text: "Read Only" }
        }
    }

    Connections {
        target: connection
        function onSendJsonToQml(JSON_str) {
            try {
                var JsonObject = JSON.parse(JSON_str)

                for (var key in JsonObject) {
                    name_latitude.append({
                                             "name" : JsonObject[key].name,
                                             "lat" : JsonObject[key]["address"]["geo"]["lat"]
                                         })
                }
                statusBarText.text = "JSON data received";
            }
            catch (e) {
                statusBarText.text = "Error in parsing JSON data";
            }
        }
        function onSendStatusToQml(message) {
            statusBarText.text = message;
        }
    }
}
