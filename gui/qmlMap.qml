import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6


Item {
    id: qmlMap

    Plugin {
        id: osmPlugin
        name: "osm"
        PluginParameter { name: "osm.useragent"; value: "My great Qt OSM application" }
    }

    Map {
        anchors.fill: parent
        plugin: osmPlugin
        center: QtPositioning.coordinate(52.220443, 21.010738)
        zoomLevel: 18
    }
}