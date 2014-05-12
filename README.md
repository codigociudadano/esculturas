# [Esculturas](https://github.com/codigociudadano/esculturas)

Catálogo de las esculturas que se pueden encontrar en la ciudad de Resistencia. Este catálogo provee una API abierta de datos para que cualquiera pueda aprovechar dicha información en la aplicación que necesite sin coste alguno.

## Tabla de contenido

 - [Instalación](#instalacion)
 - [Bugs y peticiones de nuevas features](#Bugs-y-peticiones-de-nuevas-features)
 - [Documentación](#documentacion)
 - [Contribuir](#contribuir)
 - [Comunidad](#comunidad)

## Instalación

Clonar el repositorio:  `git clone https://github.com/codigociudadano/esculturas.git`.

Configurar un Virtual Host de Apache para que apunte a src/ donde el servername sea local.esculturas.

Añadir local.esculturas a la tabla de hosts (/etc/hosts).

Crear una base de datos MYSQL llamada esculturas.

Crear un usuario esculturas en MYSQL con la password esculturas y que tenga accesso full en la base esculturas.

Importar el dump de la base de datos de prueba.

Limpiar las Caches de Drupal con drush.

Entrar con el browser a local.esculturas.


## Bugs y peticiones de nuevas features

Si encontraste un bug, tenés un error o querés pedir una feature nueva? Podés agregarlo a la [lista de issues](https://github.com/codigociudadano/esculturas/issues). Te pedimos por favor, antes de agregar tu idea o problema, revisá si no hay un pedido similar que fué hecho anteriormente.

## Documentación

Por el momento, la documentación del sitio está disponible en este [doc](https://github.com/codigociudadano/esculturas)

## Contribuir

El sitio esta hecho en su mayoría con varias tecnologías, principalmente en Drupal. En esta sección podés encontrar links útiles que te pueden ser de ayuda:

### PHP ####
 
 - Manual de PHP: [Link](http://www.php.net/manual/es/)

### Drupal ###
 - Documentación oficial: [Link](https://drupal.org/documentation)
 - Foro oficial: [Link](https://drupal.org/forum)
 - Drupal Answers : [Link](http://drupal.stackexchange.com/)

### HTML/CSS/Javascript

 - (General) Mozilla Developer Network español: [Link](https://developer.mozilla.org/es/)
 - (Javascript) Eloquent Javascript: [Link](http://eloquentjavascript.net/contents.html)
 - (jQuery) jQuery API Documentation: [Link](http://api.jquery.com/)
 - (jQuery) jQuery enlightment: [Link](http://jqueryenlightenment.com/jquery_enlightenment.pdf)

### Google Map

 - Google developers - Google Map API: [Link](https://developers.google.com/maps/)

## Comunidad

 Seguí las ultimas noticias de Esculturas y mas sobre Código Ciudadano en:
 - El sitio oficial: [Link](http://www.codigociudadano.com.ar/)
 - Seguí a [@CiudadanoCo en Twitter](https://twitter.com/CiudadanoCo)
