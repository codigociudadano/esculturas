/** Javscripts aca **/

(function($, document){
    var mapOptions = {
        center: new google.maps.LatLng(-27.4531453,-58.9862608), // seteas la coordenada
        div: '#map_canvas',
        zoom: 13, //seteas altura del zoom
        zoomControl: true,
        //Determina el tamaño del control de zoom
        mapTypeId: 'roadmap'
    };

    var map = null;    
    var i = 0;
    var marker = null;
    var infoWindow = null;

    function initialize() {
        map = new google.maps.Map(document.getElementById("map_canvas"),
            mapOptions);

        //recorro las esculturas    
        esculturas.forEach( function(escultura){
            var e = new Array(escultura[0], escultura[1], escultura[2], escultura[3]);
            
            //instanciar un popup                                                            
            infoWindow = new google.maps.InfoWindow({maxWidth: 300 }), marker, i;

            //posicion del marker
            marker = new google.maps.Marker({            
            position: new google.maps.LatLng(e[1].lat, e[1].lon),
                map: map
            });
                //evento del marker
                google.maps.event.addListener(marker, 'click', (function(marker, i) {
                    return function() {
                        var contentString = null;
                        contentString = '<div style="overflow:hidden">'+                                            
                            '<h1>'+e[0].titulo+'</h1>'+
                            '<div id="bodyContent">'+
                            '<table>'+'<tr>'+'<td style="width:75%">'+                                                    
                            '<h5> Autor: </h5>'+e[0].autor+'<div class="hr"><hr></div>'+
                            '<h5> Evento: </h5>'+e[0].evento+'<div class="hr"><hr></div>'+
                            '<h5> Ubicación: </h5>'+e[0].ubicacion+'</td>'+                            
                            '<td>'+'<img border="0" align="left" src="'+e[3].uri+'">'+
                            '</td>'+'</tr>'+'</table>'+
                            'Saber más sobre <a href="'+e[2].url+'">'+''+e[0].titulo+'</a>.'+                                                                                                
                            '</div>'+
                            '</div>';

                        infoWindow.setContent(contentString);
                        infoWindow.open(map, marker);
                    }
                })(marker, i));                
            i++;
        });        
    }

    $(document).ready(function(){
        initialize();
    });

})(jQuery, document);