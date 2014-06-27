<?php

/**
 * @file
 * Default theme implementation for google map fields.
 *
 * Available variables:
 * - $name: the display name of the map
 * - $map_id: a unique ID for the map.
 *   to identify the map container.
 */

?>
<div class="google-map-field">
  <div class="google-map-field-label">
    <?php print $name; ?>
  </div>
  <div id="google_map_field_<?php print $map_id; ?>" class="google_map_field_display"></div>
</div>
