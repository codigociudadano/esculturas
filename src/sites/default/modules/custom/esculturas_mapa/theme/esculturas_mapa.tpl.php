<script type="text/javascript">
       esculturas = <?php echo json_encode($esculturas); ?>;
</script>

<style>
    #map-canvas {
        max-width: none;
        width: auto;
        display:inline;
    }
    
    .hr{
    border: 0;
    height: 0px;
    background-image: -webkit-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
    background-image:    -moz-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
    background-image:     -ms-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
    background-image:      -o-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
  }
}
</style>

<div id="map_canvas" style="width:100%; height:500px;"></div>
