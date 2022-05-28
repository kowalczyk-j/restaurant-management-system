import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

MapQuickItem
{
    id: marker
    anchorPoint.x: marker.width / 2
    anchorPoint.y: marker.height / 2
    property string labelText

    sourceItem: Item
    {
        Image
        {
            id: icon
            source: "pin.png"
        }

        Circle
        {
            id: tag
            anchors.centerIn: label
            width: label.width + 4
            height: label.height + 2
            color: "black"
        }

        Label
        {
            id:label
            text: labelText
        }
    }
}