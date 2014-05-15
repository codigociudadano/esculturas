# [Esculturas](https://github.com/codigociudadano/esculturas)

Catálogo de las esculturas que se pueden encontrar en la ciudad de Resistencia. Este catálogo provee una API abierta de datos para que cualquiera pueda aprovechar dicha información en la aplicación que necesite sin coste alguno.

## Tabla de contenido

 - [Requerimientos](#requerimientos)
 - [Instalacion](#instalacion)
 - [Bugs y peticiones de nuevas features](#Bugs-y-peticiones-de-nuevas-features)
 - [Documentacion](#documentacion)
 - [Contribuir](#contribuir)
 - [Comunidad](#comunidad)

## Requerimientos

Para que puedas ayudarnos en este proyecto se requiere tener instalado:
 - Los requerimientos mínimos de Drupal: https://drupal.org/requirements
 - Drush (interfaz de linea de comandos para Drupal)
   - En Ubuntu: sudo apt-get install drush
   - Otros Sist. Op: ver https://drupal.org/node/1791676

## Instalacion

1) Clonar el repositorio:  `git clone https://github.com/codigociudadano/esculturas.git`.

2) Configurar un Virtual Host de Apache para que apunte a src/ donde el servername sea local.esculturas. 
   Un ejemplo: 
   ```
    <VirtualHost *:80>      
      DocumentRoot {DocumentRoot de Apache}/esculturas/src
      ServerName local.esculturas
      RewriteEngine On
      RewriteOptions inherit
      CustomLog /var/log/apache2/esculturas.log combined
      <Directory {DocumentRoot de Apache}/esculturas/src>
        Options +FollowSymLinks Indexes
        AllowOverride All
        order allow,deny
        allow from all
      </Directory>
    </VirtualHost>
   ```

3) Añadir local.esculturas a la tabla de hosts (/etc/hosts).

4) Crear una base de datos MYSQL llamada esculturas.

5) Crear un usuario esculturas en MYSQL con la password esculturas y que tenga accesso full en la base esculturas.

6) Bajar la ultima base de datos para development desde [aqui](http://www.codigociudadano.co/downloads/esculturas/esculturasdb-latest.tar.gz).

7) Importar el dump de la base de datos de prueba.

8) Desde `src/` correr con drush: `bash scripts/adjust-db-to-site.sh`

9) Entrar con el browser a http://local.esculturas.

## Bugs y peticiones de nuevas features

Si encontraste un bug, tenés un error o querés pedir una feature nueva? Podés agregarlo a la [lista de issues](https://github.com/codigociudadano/esculturas/issues). Te pedimos por favor, antes de agregar tu idea o problema, revisá si no hay un pedido similar que fué hecho anteriormente.

## Documentacion

Por el momento, la documentación del sitio está disponible en este [doc](https://github.com/codigociudadano/esculturas)

## Contribuir

El sitio esta hecho en su mayoría con varias tecnologías, principalmente en Drupal. En esta sección podés encontrar links útiles que te pueden ser de ayuda:

### PHP ####
 
 - [Manual de PHP](http://www.php.net/manual/es/)

### Drupal ###
 - [Documentación oficial Drupal](https://drupal.org/documentation)
 - [Foro oficial](https://drupal.org/forum)
 - [Drupal Answers](http://drupal.stackexchange.com/) (pertence a la red Stack Exchange)

### HTML/CSS/Javascript

 - (General) [Mozilla Developer Network español](https://developer.mozilla.org/es/)
 - (Javascript) [Eloquent Javascript](http://eloquentjavascript.net/contents.html)
 - (jQuery) [jQuery API Documentation](http://api.jquery.com/)
 - (jQuery) [jQuery enlightment](http://jqueryenlightenment.com/jquery_enlightenment.pdf)

### Google Map

 - Google developers - [Google Map API](https://developers.google.com/maps/)

## Comunidad

 Seguí las ultimas noticias de Esculturas y mas sobre Código Ciudadano en:
 - El sitio oficial: [Link](http://www.codigociudadano.com.ar/)
 - Seguinos en Facebook[CiudadanosC](https://www.facebook.com/CiudadanosC)
 - Seguinos en Twitter: [@CiudadanoCo](https://twitter.com/CiudadanoCo)
