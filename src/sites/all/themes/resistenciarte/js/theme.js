/**
 * Created by alejandro on 23/06/14.
 */
jQuery(document).ready( function(){
    var container = document.querySelector('.view-esculturas .view-content');
    var msnry = new Masonry( container, {
        // options
        columnWidth: 275,
        itemSelector: '.views-row'
    });
});

//view-id-autores
jQuery(document).ready( function(){
    var container = document.querySelector('.view-id-autores .view-content');
    var msnry = new Masonry( container, {
        // options
        columnWidth: 275,
        itemSelector: '.views-row'
    });
});

