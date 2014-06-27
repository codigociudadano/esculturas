/**
 * Created by alejandro on 23/06/14.
 */
jQuery(document).ready( function($){
    var container_esculturas = document.querySelector('.view-esculturas .view-content');
    var container_autores = document.querySelector('.view-autores .view-content');

    var msnry2 = new Masonry( container_autores, {
        // options
        columnWidth: 270,
        itemSelector: '.views-row'
    });

    var msnry1 = new Masonry( container_esculturas, {
        // options
        columnWidth: 270,
        itemSelector: '.views-row'
    });

    $('.my-slideshow').bjqs({
        'height': 600,
        'width': 1140,
        'responsive' : true,
        'animduration' : 450, // how fast the animation are
        'animspeed' : 4000, // the delay between each slide
        'automatic' : true, // automatic
        'showcontrols' : true, // show next and prev controls
        'centercontrols' : true, // center controls verically
        'nexttext' : '<i class="fa fa-chevron-right fa-2x"></i>', // Text for 'next' button (can use HTML)
        'prevtext' : '<i class="fa fa-chevron-left fa-2x"></i>', // Text for 'previous' button (can use HTML)
        'hoverpause' : true, // pause the slider on hover
        'usecaptions' : true,

    });

    !function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0];
        if(!d.getElementById(id)){js=d.createElement(s);
            js.id=id;js.src="https://platform.twitter.com/widgets.js";
            fjs.parentNode.insertBefore(js,fjs);
        }}(document,"script","twitter-wjs");

});
