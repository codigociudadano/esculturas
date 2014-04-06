
/**
 * @file
 * This file contains the javascript functions used by the google map field
 * widget.
 */

/**
 * Declare global variable by which to identify the map.
 */
var google_map_field_map;

/**
 * Add code to generate the map on page load.
 */
(function ($) {
  Drupal.behaviors.google_map_field = {
    attach: function (context) {
      // Get the settings for the map from the Drupal.settings object.
      var fname = Drupal.settings.gmf_widget_form['fname'];
      var lat = $("#edit-"+fname+"-und-0-lat").val();
      var lon = $("#edit-"+fname+"-und-0-lon").val();
      var zoom = $("#edit-"+fname+"-und-0-zoom").val();
      var latlng = new google.maps.LatLng(lat, lon);
      // Create the map and drop a marker on it at the specified position.
      var mapOptions = {
        zoom: parseInt(zoom),
        center: latlng,
        streetViewControl: false,
        mapTypeId: google.maps.MapTypeId.ROADMAP
      };
      google_map_field_map = new google.maps.Map(document.getElementById("google_map_picker"), mapOptions);
      marker = new google.maps.Marker({
        position: latlng,
        optimized: false,
        map: google_map_field_map
      });
      // Add a click listener to the map.
      google.maps.event.addListener(google_map_field_map, "click", function(event) {
        getCoords(event.latLng);
      });
      // Add an event function to catch zoom in/zoom out.
      google.maps.event.addListener(google_map_field_map, "zoom_changed", function(event) {
        document.getElementById("edit-"+fname+"-und-0-zoom").value = google_map_field_map.getZoom();
      });
    }
  };
})(jQuery);

/**
 * This function is called by the map click listener to get the position
 * (lat/long) of the click on the map.  It then sets the map centre at that
 * point and put the lat/long values in the associated display fields.
 */
function getCoords(latlng) {
  var fname = Drupal.settings.gmf_widget_form['fname'];
  marker.setPosition(latlng);
  google_map_field_map.setCenter(latlng);
  document.getElementById("edit-"+fname+"-und-0-lat").value = latlng.lat();
  document.getElementById("edit-"+fname+"-und-0-lon").value = latlng.lng();
}

/**
 * This function takes the value in the center on field and centers the map
 * at that point.
 */
function google_map_field_doCenter() {
  var geocoder = new google.maps.Geocoder();
  var fname = Drupal.settings.gmf_widget_form['fname'];
  var location = document.getElementById("edit-"+fname+"-und-0-center-on").value;
  geocoder.geocode( { 'address': location}, function (result, status) {
    if (status == 'OK') {
      var latlng = new google.maps.LatLng(result[0].geometry.location.lat(), result[0].geometry.location.lng());
      google_map_field_map.panTo(latlng);
      marker.setPosition(latlng);
      getCoords(latlng);
    } else {
      alert('Could not find location.');
    }
    return false;
  });
  return false;
}
