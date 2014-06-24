/**
 * Created by alejandro on 23/06/14.
 */
jQuery(document).ready( function(){
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
});