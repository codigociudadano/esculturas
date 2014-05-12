<script type="text/javascript">
       esculturas = <?php echo json_encode($esculturas); ?>;
       categorias = <?php echo json_encode($categorias); ?>;

</script>

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

</style>

<table>
    <tr><td>
<br><h2>Filtrar por:</h2>
    <h3>Autor</h3>
        <select id="autores" name="autores" style="overflow-y: auto; width: 300px;">
            <option>Todos</option>
            <option disabled>──────────</option>
            <?php
             $autores = $categorias[2];
                foreach($autores as $a){
                    echo '<option>'.$a.'</option>';
                }
            ?>
        </select>
        <div class="checkboxes">
      <span style="float: left; margin-right: 10px; "><h3>Material</h3>
          <?php
          $materiales = $categorias[0];
          foreach($materiales as $m){
              echo '<input type="checkbox" value="'.$m.'"/><label> '.$m.'</label><br />';
          }
          ?>
       </span>
        <span style="float: left;"><h3>Tipo</h3>
            <?php
            $tipos = $categorias[1];
            foreach($tipos as $t){
                echo '<input type="checkbox" value="'.$t.'"/><label> '.$t.'</label><br />';
            }
            ?></span>
        </div><h3>Evento</h3>
        <span style="float: left; margin-right: 10px;">
        <select id="eventos" name="eventos" style="overflow-y: auto;">
            <option>Todos</option>
            <option disabled>──────────</option>
            <?php
            $eventos = $categorias[3];
            foreach($eventos as $e){
                echo '<option>'.$e.'</option>';
            }
            ?>
        </select></span>
        <span style="float: left;"><button id="ubicame">Ubicame!</button></span>
        </td>
        <td>
            <div id="map_canvas" style="width:825px; height:600px;"></div>
        </td></tr>
        <!--<td style="width: 140px;">-->

</table>

