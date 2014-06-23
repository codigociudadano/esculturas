/**
 * Created by alejandro on 23/06/14.
 */
jQuery(document).ready( function(){
    var container = document.querySelector('.view-esculturas .view-content');
    var msnry = new Masonry( container, {
        // options
        columnWidth: 260,
        itemSelector: '.views-row'
    });

});

