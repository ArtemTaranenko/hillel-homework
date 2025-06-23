import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Temperature Calculator")

    ColumnLayout{
    anchors.centerIn: parent
    anchors.margins: 10
    spacing: 10
    RowLayout{
        anchors.margins: 10
        spacing: 10
        Label{
            text: "Celsius"
            horizontalAlignment: Text.AlignRight
            Layout.alignment: Qt.AlignRight | Qt.AlignCenter
            font.pointSize: 20
            Layout.preferredWidth: 100
        }

        TextField{
            id: cel
            Layout.fillWidth: true
            onTextEdited: {
            controller.setCel(cel.text)
            fahr.text = controller.getFahrenheit()
            kel.text = controller.getKelvin()
            }

            background: Rectangle{
            id: cel_background
            width: cel.width
            height: cel.height

            border.color: "transparent"
            border.width: 1
            }
        }
    }

    RowLayout{
        spacing: 10
        Label{
            text: "Fahrenheit"
            horizontalAlignment: Text.AlignRight
            Layout.alignment: Qt.AlignRight | Qt.AlignCenter
            font.pointSize: 20
            Layout.preferredWidth: 100
        }

        TextField{
            id: fahr
            Layout.fillWidth: true
            onTextEdited: {
            controller.setFahr(fahr.text)
            cel.text = controller.getCelsius()
            kel.text = controller.getKelvin()
            }
            background: Rectangle{
            id: fahr_background
            width: fahr.width
            height: fahr.height

            border.color: "black"
            border.width: 1
            }
        }
    }

    RowLayout{
        spacing: 10
        Label{
            text: "Kelvin"
            horizontalAlignment: Text.AlignRight
            Layout.alignment: Qt.AlignRight | Qt.AlignCenter
            font.pointSize: 20
            Layout.preferredWidth: 100
        }

        TextField{
            id: kel
            Layout.fillWidth: true
            onTextEdited: {
            controller.setKel(kel.text)
            cel.text = controller.getCelsius()
            fahr.text = controller.getFahrenheit()
            }
            background: Rectangle{
            id: kel_background
            width: kel.width
            height: kel.height

            border.color: "transparent"
            border.width: 1
            }
        }
    }

    }

    Connections{
        target: model
                function onCel_validChanged(opv_new) {
                    cel_background.border.color = opv_new ? "transparent" : "red"
                }

                function onFahr_validChanged(opv_new) {
                    fahr_background.border.color = opv_new ? "transparent" : "red"
                }
                function onKel_validChanged(opv_new){
                    kel_background.border.color = opv_new ? "transparent" : "reds"
                }
            }
}
