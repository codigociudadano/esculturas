/** Javscripts aca **/

(function($, document){

    //opciones del mapa
    var mapOptions = {
        center: new google.maps.LatLng(-27.4531453,-58.9862608),
        div: '#map_canvas',
        zoom: 13, 
        zoomControl: true,    
        mapTypeId: 'roadmap'   

    };

    var flag_btn_cercanas;
    var map = null;
    var i = 0;
    var marker = null;
    var my_marker = null;
    var infoWindow = null;
    var my_infoWindow = null;
    var markers = new Array();
    var markers_cercanos = new Array();
    var iconSource = "https://www.craigslist.org/images/map/marker-icon.png";
    var my_iconSource = 'http://www.wicfy.com/images/newmarkers/home-marker.png';
    
    function initialize() {

        map = new google.maps.Map(document.getElementById("map_canvas"),
            mapOptions);

        ocultarBotonCercanas(true);

        esculturas.forEach( function(escultura){
            var e = [escultura[0], escultura[1], escultura[2], escultura[3]];

            //instanciar un popup
            infoWindow = new google.maps.InfoWindow({maxWidth: 300 }), marker, i;
            
            //posicion del marker
            marker = new google.maps.Marker({
                position: new google.maps.LatLng(e[1].lat, e[1].lon),
                map: map,
                icon: iconSource,
                title: e[0].titulo,
                tag: [e[0].autor, e[0].material, e[0].tipo, e[0].evento] //arreglo de tags para filtrar los markers
            });

            markers.push(marker);

//evento del marker que llama al popup

            google.maps.event.addListener(marker, 'click', (function(marker, i) {
                return function() {
                    var contentString = null;
                    contentString = '<div>'+
                        '<h1>'+e[0].titulo+'</h1>'+
                            '<div id="bodyContent">'+
                            '<div class="scrollWrapper">'+
                                '<table style="width: 280px;">'+
                                    '<tr>'+
                                        '<td style="width: 150px;">'+
                                            '<h5> Autor: </h5>'+e[0].autor+'<div class="hr"><hr></div>'+
                                            '<h5> Tipo: </h5>'+e[0].tipo+'<div class="hr"><hr></div>'+
                                            '<h5> Material: </h5>'+e[0].material+'<div class="hr"><hr></div>'+
                                            '<h5> Evento: </h5>'+e[0].evento+
                                        '</td>'+
                                        '<td>'+
                                            '<img border="0" style="width: 150px; height: 180px;" align="left" src="'+e[3].uri+'">'+
                                        '</td>'+
                                    '</tr>'+
                                '</table>'+
                            '</div>'+
                        '<div align="right">Saber más sobre <a href="'+e[2].url+'">'+''+e[0].titulo+'</a>.</div>'+
                        '</div>'+
                        '</div>';

                    marker.setAnimation(google.maps.Animation.BOUNCE); //animación del marker
                    setTimeout(function(){ marker.setAnimation(null); }, 2998); //tiempo de animación
                    infoWindow.setContent(contentString);
                    infoWindow.open(map, marker);
                }
            })(marker, i));
            i++;
        });

       //obtengo texto inicial de los select
       var autor = $("#autores").find(":selected").text(); 
       var evento = $("#eventos").find(":selected").text();
       var values = null;


//checkboxes Material, Tipo y Evento

        $('.checkboxes input').click(function(){            
            markers.forEach(function(marker){
                 infoWindow.close();
                 marker.setMap(null);
            });
            var count = 0;

            $("input:checkbox:checked").each(function(){
                infoWindow.close();

                var values = $(this).val();

                //si valor del select Autor y Evento no esta modificado a Todos
                if(autor !== 'Todos' && evento !== 'Todos'){
                    markers.forEach(function(marker){
                        if(marker.tag[0] === autor && marker.tag[3] === evento){ //verifica evento y autor con los tags
                            if(marker.tag[1]=== values || marker.tag[2] === values){ //verifica los checkboxes con los tags
                                marker.setMap(map);
                            }
                        }
                        count++;
                    });
                }else{ //caso contrario solo verifica los checkboxes con los tags
                    markers.forEach(function(marker){
                        if(marker.tag[1]=== values || marker.tag[2] === values){
                            marker.setMap(map);
                        }
                        count++;
                    });
                }
            });  
            //checkboxes sin marcar
            if(count === 0){
                markers.forEach(function(marker){
                    infoWindow.close();
                    marker.setMap(map);
                });
            }
        });

//VERÉ SI PUEDO ACORTAR CODIGO CON LOS SELECT, por el momento anda

//select de Autores

        $("#autores").change(function(){
            infoWindow.close();
            autor = $(this).find(":selected").text();
            //si select Autor y Evento estan modificados
            if(autor !== 'Todos' && evento !== 'Todos'){
                markers.forEach(function(marker){
                    if(marker.tag[0] === autor && marker.tag[3] === evento){ 
                        marker.setVisible(true);
                    }else{
                        marker.setVisible(false);
                    }
                });
            }else //si select Autor esta modificado y Evento no
                if(autor !== 'Todos' && evento ==='Todos'){
                    markers.forEach(function(marker){
                        if(marker.tag[0] === autor){
                            marker.setVisible(true);
                        }else{
                            marker.setVisible(false);
                        }
                });
            }else //si ningún checkbox esta marcado y Evento en Todos
                if(values===null && evento === 'Todos'){
                    markers.forEach(function(marker){
                        marker.setVisible(true);
                    });
                }else{//si select Evento esta modificado y Autor no
                    markers.forEach(function(marker){
                        if(marker.tag[3] === evento){
                            marker.setVisible(true);
                        }else{
                            marker.setVisible(false);
                        }
                    });
                }
        });

//select de Eventos (es lo mismo pero este tiene en cuenta el valor del select Autor)

        $("#eventos").change(function(){
            infoWindow.close();
            evento = $(this).find(":selected").text(); 
            if(evento !== 'Todos' && autor !=='Todos'){
                markers.forEach(function(marker){
                    if(marker.tag[3] === evento && marker.tag[0] === autor){
                        marker.setVisible(true);
                    }else{
                        marker.setVisible(false);
                    }
                });
            }else if(evento !== 'Todos' && autor ==='Todos'){
                markers.forEach(function(marker){
                    if(marker.tag[3] === evento){
                        marker.setVisible(true);
                    }else{
                        marker.setVisible(false);
                    }
                });
            }else
                if(values===null && autor==='Todos'){
                    markers.forEach(function(marker){
                        marker.setVisible(true);
                    });
                }else{
                    markers.forEach(function(marker){
                        if(marker.tag[0] === autor){
                            marker.setVisible(true);
                        }else{
                            marker.setVisible(false);
                        }
                    });
                }
        });

//geolocalización

        $("#ubicame").click(function (){
           //si ya existe el marker de mi posicion lo elimina y oculta el checkbox esculturas cercanas con su label
            if(my_marker){
                my_marker.setMap(null);
                my_marker = null;
               
               ocultarBotonCercanas(true);

                ocultarCheckboxes(false);

                markers.forEach(function(marker){
                    infoWindow.close();
                    marker.setMap(map);
                    map.setZoom(mapOptions.zoom);
                    map.setCenter(mapOptions.center);
                    ocultarCheckboxes(false);
                });

            //sino si el navegador es compatible con geolocalización
            }else if(navigator.geolocation && my_marker === null){                   

                   var my_String = '<h5>Aquí estas!</h5>';

                   navigator.geolocation.getCurrentPosition(function(position) {
                       var pos = new google.maps.LatLng(position.coords.latitude,
                           position.coords.longitude);

                       my_infoWindow = new google.maps.InfoWindow({
                                maxWidth: 200,
                                position: pos,
                                content: my_String
                            });

                       my_marker = new google.maps.Marker({
                                position: pos,
                                map: map,
                                title: 'Aquí estas!',
                                icon: my_iconSource,
                                animation: google.maps.Animation.BOUNCE
                            });

                       infoWindow.close();
                       my_infoWindow.open(map, my_marker);

                            google.maps.event.addListener(my_marker, 'click', function(){
                                my_infoWindow.setContent(my_String);
                                my_infoWindow.open(map, my_marker);
                            });

                            google.maps.event.addListener(my_marker, 'dblclick', function(){
                                my_infoWindow.close(map, my_marker);
                                my_marker.setMap(null);                                
                                ocultarBotonCercanas(true);
                                markers.forEach(function(marker){
                                    infoWindow.close();
                                    map.setZoom(mapOptions.zoom);
                                    map.setCenter(mapOptions.center);
                                    marker.setMap(map);
                                });
                            });

                       map.setCenter(pos);
                       map.setZoom(16);

                           ocultarBotonCercanas(false);

                   }, function() {
                       //si el servicio falla por x motivo
                       handleNoGeolocation(true);
                   });
               } else {
                   //si el browser no soporta geolocalización
                   handleNoGeolocation(false);
               }

                function handleNoGeolocation(errorFlag) {
                    ocultarBotonCercanas(false);
                    if (errorFlag) {
                        alert('Error: Este servicio ha fallado.');                        
                    } else {
                        alert('Error: Su navegador no soporta este servicio.');
                    }
                }
        });

//checkbox top 5 esculturas cercanas

        $('#cercanas').click(function (){

            if (!flag_btn_cercanas) {
                cambiarBotonCercanas(false);
                ocultarCheckboxes(true);

                var metros = new Array();

                if(my_marker){
                    var i = 0;

                    markers.forEach(function(marker){
                        //obtengo la distancia  en metros entre el marker y la posición actual
                        metros.push(google.maps.geometry.spherical.computeDistanceBetween(marker.position, my_marker.position));
                    });
                    //ordeno los metros de menor a mayor
                    metros.sort(function(a,b){ return a-b});

                    metros.forEach(function (metro){
                        if (i < 5){
                            markers.forEach(function(marker){
                                var distancia = google.maps.geometry.spherical.computeDistanceBetween(marker.position, my_marker.position);

                                if(distancia === metro){
                                  markers_cercanos.push(marker); //markers cercanos guardados
                                  i++;
                                }
                            });
                        }
                    });
                    //muestro los markers mas cercanos
                    markers.forEach(function(marker){
                        if(jQuery.inArray(marker, markers_cercanos) == -1){
                           marker.setMap(null);
                        }
                    });
                }

                flag_btn_cercanas = true;

            }else{
                flag_btn_cercanas = false;
                cambiarBotonCercanas(true);
                ocultarCheckboxes(false);
                markers.forEach(function(marker){
                    infoWindow.close();
                    marker.setMap(map);
                    ocultarCheckboxes(false);
                });
            }
       });

        function ocultarCheckboxes(flag){
            $('.checkboxes input').attr("disabled", flag);
            $('.checkboxes input').attr("checked", false);
            $("#autores").attr("disabled", flag);
            $("#eventos").attr("disabled", flag);
        }

        function cambiarBotonCercanas(flag){
            if(flag){
                $("#cercanas").attr('value', 'Mostrar');
            }else{
                $("#cercanas").attr('value', 'Todas');
            }
        }
        function ocultarBotonCercanas(flag){
            if(flag){
             $("#ubicame").attr('value', 'Ubicame');
             $('#cercanas').hide();
             $('h3[id="h3"]').hide();
            }else{
             $("#ubicame").attr('value', 'Quitar ubicación');
             $('#cercanas').show();
             $('h3[id="h3"]').show();
            } 
        }        
    }
    initialize();

    $(document).ready(function(){

    });

})(jQuery, document);

