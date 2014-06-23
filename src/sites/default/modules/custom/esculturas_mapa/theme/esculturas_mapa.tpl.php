<style>
    #map-canvas {
        max-width: none;
        width: auto;
        display:inline;
    }

    #map-optionbar-r{
        position: absolute;
        top: 125px;
        right: 5px;
        width: 230px;
        background-color: #F5F5F5;
        padding: 5px;
        font-size: 14px;
        border: 1px solid #232020;
        line-height: 16px;
    }
    
    .hr{
      border: 0;
      height: 1px;
      background-image: -webkit-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
      background-image:    -moz-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
      background-image:     -ms-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
      background-image:      -o-linear-gradient(left, rgba(0,0,0,0), rgba(0,0,0,0.75), rgba(0,0,0,0)); 
    }

   div.scrollWrapper{ 
      height:300px;
      width:300px;          
      overflow-y: hidden;  
    }

  div.scrollWrapper:hover {
      height:300px;
      width:300px;
      overflow-y: auto;
          
    }

    .scrollable{
        overflow-y: auto;
        width: 300; /* adjust this width depending to amount of text to display */
        height: 200px; /* adjust height depending on number of options to display */
    }
    .scrollable select{
        border: none;
    }

</style>
        <div id="row" align="center">
            <div id="mapa_control"><h4>Autor</h4>
              <select id="autores" name="autores" class="multiselect dropdown-toggle" data-toggle="dropdown" align="center">
                    <option>Todos</option>
                    <?php
                     $autores = $categorias[2];
                        foreach($autores as $a){
                            echo '<option>'.$a.'</option>';
                        }
                    ?>
              </select>
          </div>
        <div class="checkboxes">
            <div id="mapa_control"><h4>Materiales</h4>
               <select class="multiselect" multiple="multiple" align="center">
               <?php
                  $materiales = $categorias[0];
                  foreach($materiales as $m){
                      echo '<option value="'.$m.'">'.$m.'</option>';
                  }
                  ?>
               </select>
           </div>
            <div id="mapa_control"><h4>Tipos</h4>
               <select class="multiselect" multiple="multiple" align="center">
                <?php
                $tipos = $categorias[1];
                foreach($tipos as $t){
                    echo '<option value="'.$t.'">'.$t.'</option>';
                }
                ?>
               </select>
           </div>
        </div>
            <div id="mapa_control"><h4>Evento</h4>
                <select id="eventos" name="eventos" class="multiselect dropdown-toggle" data-toggle="dropdown" align="center">
                    <option>Todos</option>
                    <?php
                    $eventos = $categorias[3];
                    foreach($eventos as $e){
                        echo '<option>'.$e.'</option>';
                    }
                    ?>
                </select>
            </div>
            <div class="control-ubicame"><h4>Mi ubicación</h4>
                <input class="btn btn-danger" type="button" id="ubicame" value="Ubicame" align"center"/>
            </div>
            <div id="mapa_control">
                <h4 id="h4">Top 5 esculturas cercanas </h4>
                <input class="btn btn-danger" type="button" id="cercanas" value="Mostrar" align="center"/>
            </div>
    </div>

    <div id="row">
        <div id="map_canvas"></div>
    </div>
<script type="text/javascript">
    esculturas = <?php echo json_encode($esculturas); ?>;
    categorias = <?php echo json_encode($categorias); ?>;
</script>
<script type="text/javascript">
    jQuery('.multiselect').multiselect({
        templates: {
            button: '<button type="button" class="multiselect dropdown-toggle" data-toggle="dropdown"></button>',
            ul: '<ul class="multiselect-container dropdown-menu" style="max-height: 150px; overflow-y: auto; overflow-x: hidden;"></ul>',
            filter: '<div class="input-group"><span class="input-group-addon"><i class="glyphicon glyphicon-search"></i></span><input class="form-control multiselect-search" type="text"></div>',
            li: '<li><a href="javascript:void(0);"><label></label></a></li>'
        }
    });
</script>

