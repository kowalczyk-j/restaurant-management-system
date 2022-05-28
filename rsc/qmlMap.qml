import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6


Item {
    property real latitude: 10
    property real longitude: -90
    id: qmlMap
    objectName: "qmlMap"


    Plugin {
        id: osmPlugin
        name: "osm"
        PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
    }

    Map {
        id: map
        objectName: "map"

        anchors.fill: parent
        plugin: osmPlugin
        center: QtPositioning.coordinate(latitude, longitude)
        zoomLevel: 18
    }
}