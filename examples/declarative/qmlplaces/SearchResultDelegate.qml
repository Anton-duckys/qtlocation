import QtQuick 1.0
import Qt.location 5.0

Rectangle {
    property SearchResult result
    id: thisItem
    width: parent.width
    radius: 10
    height: textFields.height
    Behavior on height { PropertyAnimation{} }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "lightgray" }
        GradientStop { id: gradStop; position: 1.0; color: 'gray'
            Behavior on color { ColorAnimation{} }
        }
    }

    function categoryNames(categories) {
        var result = "";

        for (var i = 0; i < categories.length; ++i) {
            if (result == "") {
                result = categories[i].name;
            } else {
                result = result + ", " + categories[i].name;
            }
        }

        return result;
    }

    Component {
        id: placeFields
        Item {
            focus:true
            height: col.height + 10
            Column {
                id: col
                Text { text: '<b>Name: </b> ' + result.place.name; font.pixelSize: 16 }
                Text { text: '<b>Street: </b> ' + result.place.location.address.street; font.pixelSize: 16 }
                Text { text: '<b>Latitude: </b> ' + result.place.location.coordinate.latitude; font.pixelSize: 16 }
                Text { text: '<b>Longitude: </b> ' + result.place.location.coordinate.longitude; font.pixelSize: 16 }
                Text { text: '<b>Categories: </b> ' + categoryNames(result.place.categories); font.pixelSize: 16 }
                Text { text: '<b>Media count: </b> ' + result.place.mediaModel.totalCount; font.pixelSize: 16 }
                Text { text: '<b>Descriptions count: </b> ' + result.place.descriptions.length; font.pixelSize: 16 }
                Text { text: '<b>Review count: </b> ' + result.place.reviewModel.totalCount; font.pixelSize: 16 }
                Text { text: '<b>Tags: </b> ' + result.place.tags; font.pixelSize: 16 }
                //Text { text: '<b>Suppliers: </b> ' + JSON.stringify(place.suppliers); font.pixelSize: 16 }
                Text { id: detailsFetched; text:'<b>Details Fetched: </b> ' + result.place.detailsFetched; font.pixelSize: 16 }
                Text { id: paymentMethods; font.pixelSize: 16 }
            }

            state: 'place-core'
            states: [
                State {
                    name: "place-core"
                },
                State {
                    name: "place-details"
                    PropertyChanges { target: gradStop; color:"lightskyblue" }
                    PropertyChanges { target: paymentMethods; text: '<b>Payment methods: </b> ' + result.place.businessInformation.paymentMethods}
                }
            ]
        }
    }

    Component {
        id: didYouMeanField
        Item {
            height: didYouMeanField.height
            Text { id:didYouMeanField; text:'<b>Did you mean ' + result.didYouMeanSuggestion + '?</b>'; font.pixelSize: 16 }
            state: 'didYouMean'
            states: [
                State {
                    name: 'didYouMean'
                    PropertyChanges { target:gradStop; color: 'palegreen'}
                }
            ]
        }
    }

    Loader {
        id: textFields
        sourceComponent: (result.type == SearchResult.Place) ? placeFields : didYouMeanField
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (textFields.item.state == 'place-core') {
                textFields.item.state = 'place-details'
                if (!result.place.detailsFetched)
                    placeManager.getPlaceDetails(result.place)
            } else if (textFields.item.state == 'place-details') {
                textFields.item.state = 'place-core'
            }
        }
        onPressAndHold: {
            if (textFields.item.state != 'didYouMean') {
                placesList.model = recommendationModel
                recommendationModel.placeId = result.place.placeId
                recommendationModel.executeQuery()
            }
        }
    }
}
