# Arquitectura del Catalogo

El sitio web esta desarrollador con Drupal, este sitio cuenta con los siguientes content types (o entidades).

 * Esculturas
 * Autores
 * Eventos

La idea de esculturas es obvia, toda la info importante de la obra.

La idea de autores es poder filtrar por autor, tener información del autor y sus obras.

La idea de evento es poder filtrar por evento, ver que obras surgieron de ese evento.

Las esculturas son nuestra entidad principal. 

Las esculturas pueden tener un autor y pueden pertenecer a un evento.

A su vez, la esculturas:

  * Tienen un tipo
  * Tiene un Material
  * Tienen tags (keywords) para catalogarla
  * Tags, Material y Tipo son en Drupal Taxonomias.

# Fields

##Esculturas tiene

* Titulo
* Autor
* Tipo
* Material
* Ubicación
* Ubicación Mapa (Coordenadas para el Google Maps).
* Año de elaboracion
* Evento
* Premios
* Descripcion
* Fotos
* Tags

## Autores tiene

* Nombre
* Bio
* Nacionalidad (Taxonomía, referencia a otra entidad).
* Fotos
* Links

## Eventos tiene

* Nombre del evento
* Información del Evento
* Año del Evento
* Participantes (Referencia a Authores, Muchos autores pudieron haber participado en un evento).

# API

Para poder acceder a estos datos vamos a usar nuestra API rest, esta API esta generada por medio
de un modulo de drupal llamado services, asi que pueden ver info relacionada a este modulo para tirarnos
ideas si necesitan algo.

https://drupal.org/project/services

La API es solo lectura, asi que que van a necesitar solo GET. Devuelve Jsons.

NOTA : Desarrollen sus Apps sabiendo que el dominio base va a cambiar en un futuro, haganlo variable y facil de cambiar, posiblemente como configuracion. El path en la url de los enpoints no va debería cambiar, "debería".

Algunos ejemplos de Endpoints que les pueden ir sirviendo.

## Traer 20 nodos

http://esculturas.codigociudadano.com.ar/api/v1/node

## Treaer los proximos 20 nodos

http://esculturas.codigociudadano.com.ar/api/v1/node?page=2

## Limitar las fields para traer

http://esculturas.codigociudadano.com.ar/api/v1/node?page=1&fields=nid,title

  Notar parámetro fields
  
  Nota, nid es el ID del contenido
  
## Traer solo Esculturas

http://esculturas.codigociudadano.com.ar/api/v1/node?parameters[type]=escultura

## Traer solo Autores

http://esculturas.codigociudadano.com.ar/api/v1/node?parameters[type]=autores

## Traer solo Eventos

http://esculturas.codigociudadano.com.ar/api/v1/node?parameters[type]=eventos

## Traer mas de 20 item

http://esculturas.codigociudadano.com.ar/api/v1/node?pagesize=50

  Nota no abusar de page size sino va a matar al server, Cachear el total de nodos puede ser una buena opción.
 
## Traer info de un nid

http://esculturas.codigociudadano.com.ar/api/v1/node/1457

  nid = 1457
  
## Traer imagenes de una escultura

http://esculturas.codigociudadano.com.ar/api/v1/file/828

  828 = fid que pueden sacar al traer la info de esculturas
  
## Traer las Taxonomias

http://esculturas.codigociudadano.com.ar/api/v1/taxonomy_vocabulary

Aca van a tener que tener en cuenta los vids que son los ids de taxonomias

## Traer los terminos de una Taxonomia

 http://esculturas.codigociudadano.com.ar/api/v1/taxonomy_term?parameter[vid]=4
 
## Traer un Termino puntual con su TID (term id).

http://esculturas.codigociudadano.com.ar/api/v1/taxonomy_term/21

## Traer las Esculturas de un termino

TBD (To be done), no tengo esto todavía :S

## Trear las N esculturas próximas a una coordenada lat/long

http://esculturas.codigociudadano.com.ar/api/v1/closest_nodes_by_coord?lat=-27.454528&lon=-58.976896

Opcionalmente se puede indicar el nro de items qty_nodes=5
Opcionalmente se puede indicar la distancia a cubrir dist=50
