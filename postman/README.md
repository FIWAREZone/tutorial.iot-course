# Introducción

Para hacer pruebas con la API de FIWARE será necesario disponer de una herramienta que permita hacer peticiones HTTP e interactuar con esta. En este caso, nosotros recomendamos la herramienta Postman, que permite gestionar las colecciones de peticiones, por lo que será muy sencillo realizar las operaciones necesarias.

Postman permite definir un catálogo de peticiones (Collection) y exportar/importar para facilitar el uso por otras personas. 

# Instalación y configuración de Postman

1. Descargar [Postman](https://www.getpostman.com/) e instalar

2. Descargar el [Collection](ThinkingCities%20APIs.postman_collection.json) de peticiones que se van a utilizar en la práctica. O botón derecho-> Guardar enlace como... [Descargar](https://github.com/FIWAREZone/IoT_Course/raw/master/postman/ThinkingCities%20APIs.postman_collection.json)

3. Descargar el [environment](../ThinkingCities%20Enviroment%20Template.postman_environment.json) de variable de entorno necesarias para que funcione el "Collection". [Descargar](https://github.com/FIWAREZone/IoT_Course/raw/master/postman/ThinkingCities%20Enviroment%20Template.postman_environment.json)

4. En este punto debemos tener Postman instalado y dos ficheros con extensión ".json" en nuestro PC

5. Abrir Postman

6. Importar la colección "ThinkingCities APIs.postman_collection.json"

![Importar Collection](https://github.com/danvilmot/IoT_Course/blob/master/postman/files/import_collection.jpg)

7. Importar el environment "ThinkingCities Enviroment Template.postman_environment.json"

![Importar Environment](https://github.com/danvilmot/IoT_Course/blob/master/postman/files/import_environment.jpg)

8. Configurar las credenciales: user, password, service y subservice (Service Path) que se darán en cada sesión.



## Variables de entorno

Una vez hayamos importado tanto la colección de peticiones como el entorno (los dos ficheros descargados en el punto anterior) 

Las variables de entorno contienen parámetros que se aplican a todas las colecciones pero, que para facilitar cambiarlas todas a las vez, se han hecho variables de entorno, como por ejemplo la URL del servidor. Es necesario modificar las variables de entorno con los parámetros correspondientes:

| Parametro         |descripción   												|
| :-----------------|:--------------											|
| user              | Usuario con permisos de acceso							|
| password          | Contraseña del Usuario 									|
| service   		| Servicio del contex broker (Header Fiware-Service) 		|
| subservice      	| Subservicio del context broker (Header Fiware-ServicePath) |
| token 			| Token de autenticación de usuario dinámico 				|
| host 				| URL del servidor, es decir, del Orion Context Broker 		|
| host_iota 				| URL del servicio IoT Agent 		|
| iota_port 				| URL del servicio IoT Agent		|
| UL_apikey 				| Apikey para el envío de datos por IoTA con protocolo ultralight 		|
| JSON_apikey 			| Apikey para el envío de datos por IoTA con protocolo JSON 		|
| device_ID 				| Identificador de dispositivo		|

