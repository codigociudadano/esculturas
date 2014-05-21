(function($) {
  Drupal.behaviors.rsb = {
    attach: function(context, settings) {
      var pageTitle = document.title; //HTML page title
      var pageUrl = location.href; //Location of the page      
      
      //var animateSpeed = Drupal.settings.responsive_share_buttons.animateSpeed;
      //user hovers on the share button	
      $('#share-wrapper li').hover(function() {
        var hoverEl = $(this); //get element
        //browsers with width > 699 get button slide effect
        if($(window).width() > 699) { 
          if (hoverEl.hasClass('visible')){
            hoverEl.animate({"margin-left":"-117px"}, "fast").removeClass('visible');
          } else {
            hoverEl.animate({"margin-left":"0px"}, "fast").addClass('visible');
          }
        }
      });
      
      $('.button-wrap').click(function(event) {
          var shareName = $(this).attr('class').split(' ')[0]; //get the first class name of clicked element
          
          switch (shareName) //switch to different links based on different social name
          {
              case 'facebook':
                  var openLink = 'https://www.facebook.com/sharer/sharer.php?u=' + encodeURIComponent(pageUrl) + '&amp;title=' + encodeURIComponent(pageTitle);
                  break;
              case 'twitter':
                  var openLink = 'http://twitter.com/home?status=' + encodeURIComponent(pageTitle + ' ' + pageUrl);
                  break;
              case 'digg':
                  var openLink = 'http://www.digg.com/submit?phase=2&amp;url=' + encodeURIComponent(pageUrl) + '&amp;title=' + encodeURIComponent(pageTitle);
                  break;
              case 'stumbleupon':
                  var openLink = 'http://www.stumbleupon.com/submit?url=' + encodeURIComponent(pageUrl) + '&amp;title=' + encodeURIComponent(pageTitle);
                  break;
              case 'delicious':
                  var openLink = 'http://del.icio.us/post?url=' + encodeURIComponent(pageUrl) + '&amp;title=' + encodeURIComponent(pageTitle);
                  break;
              case 'google':
                  var openLink = 'https://plus.google.com/share?url=' + encodeURIComponent(pageUrl) + '&amp;title=' + encodeURIComponent(pageTitle);
                  break;
          }
        
        //Parameters for the Popup window
        winWidth 	= 650;	
        winHeight	= 450;
        winLeft   	= ($(window).width()  - winWidth)  / 2,
        winTop    	= ($(window).height() - winHeight) / 2,	
        winOptions   = 'width='  + winWidth  + ',height=' + winHeight + ',top='    + winTop    + ',left='   + winLeft;
        
        //open Popup window and redirect user to share website.
        window.open(openLink,'Share This Link',winOptions);
        return false;
      }); 
    }, 
  }
})(jQuery);