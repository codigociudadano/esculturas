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
                        contentString = '<div>'+                                            
                            '<h1>'+e[0].titulo+'</h1>'+
                            '<div id="bodyContent">'+
                            '<div class="scrollWrapper">'+
                            '<table style="width: 280px;">'+
                                '<tr>'+
                                    '<td style="width: 140px;">'+                                                    
                                        '<h5> Autor: </h5>'+e[0].autor+'<div class="hr"><hr></div>'+
                                        '<h5> Evento: </h5>'+e[0].evento+
                                    '</td>'+                            
                                    '<td>'+
                                        '<img border="0" style="width: 140px; height: 150px;" align="left" src="'+e[3].uri+'">'+
                                    '</td>'+
                                '</tr>'+
                                '<tr>'+
                                    '<td colspan="2">'+
                                        '<div class="hr"><hr></div>'+
                                        '<h5> Ubicación: </h5>'+e[0].ubicacion+
                                    '</td>'+
                                '</tr>'+
                            '</table>'+
                            '</div>'+
                            '<p>'+
                            '<div align="right">Saber más sobre <a href="'+e[2].url+'">'+''+e[0].titulo+'</a>.</div>'+                                                                                                
                            '</div>'+
                            '</div>';

                        marker.setAnimation(google.maps.Animation.BOUNCE);
                        setTimeout(function(){ marker.setAnimation(null); }, 2998);
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