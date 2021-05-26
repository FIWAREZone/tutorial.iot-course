# Introducción

Este curso tiene el objetivo de ayudar a los desarrolladores a integrar un dispositivo IoT en la plataforma FIWARE. En este caso se usarán los módulos de FIWARE IoT Agent, que gestionan la comunicación con dispositivos Hardware, así como otra serie de características (aprovisionamiento de dispositivos, traducción de protocolo o parámetros, etc.). En este caso concreto emplearemos el protocolo Ultralight 2.0 tanto en el dispositvo como en el IoT Agent.

La placa de desarrollo empleada será una placa NodeMCU basada en el SoC ESP8266, el cual dado su coste, capacidades y su comunidad, lo hace idóneo para este curso. 

This tutorial has an [English Version](README.en.md) 

## Conocimientos previos

Para la realización del curso es conveniente disponer de los siguientes conocimientos:
* C/C++ - Para la programación del microcontrolador.
* HTML - Para la interfaz creada por el microcontrolador.
* API REST / HTTP - Para la comunicación con el servidor.
* Electrónica básica - Para entender los conceptos y posibilidades de la placa.


## ESP8266

Para la realización del curso se empleará una placa de desarrollo NodeMCU basada en el SoC ESP8266, que incluye un microcontrolador ARM de 32 bits así como la parte de radio WiFi.



| Tables           | Are           |
| -----------------|--------------:|
| RAM              | 128KB         |
| ROM              | 4MB*          |
| Número de pines  | 13            |
| Alimentación     | 3.3V          |

*La ROM es externa, por lo que depende en concreto de la que tenga instalada la placa de desarrollo. En el caso de la placa NodeMCU es de 4MB.

![image alt text](doc/files/image_0.png)

El módulo dispone de un regulador interno de 5V a 3.3V, por lo que se puede alimentar directamente del USB. En algunos casos es conveniente emplear un adaptador externo de corriente, dado que la corriente que da un PC por el puerto USB se encuentra limitada a 500mA.

También dispone de un conversor de USB a USART a 3.3V, empleado para comunicarnos con el módulo y para cargar el firmware a través del bootloader que dispone.

## FIWARE

El objetivo de este workshop es integrar un dispositivo físico en la plataforma FIWARE. Para ello haremos uso del protocolo Ultralight 2.0 y del IoT Agent correspondiente en el lado del servidor.

Los IoT Agents son módulos que adaptan el protocolo concreto que utiliza el dispositivo (Ultralight 2.0, MQTT, etc.) con el protocolo que habla el Context Broker de FIWARE (NGSI).

# Configuración del entorno

En esta sección repasaremos como instalar y configurar los programas necesarios para desarrollar el curso. Será necesario tener instalados y configurados correctamente los siguientes elementos:
* Entorno de desarrollo Arduino y las librerías necesarias.
* Postman y la colección de peticiones de este repositorio.
* Drivers USB de la placa de desarrollo.


## Instalación y configuración de Arduino

Antes de nada, es necesario disponer del IDE de arduino. En caso que no se disponga ya, se puede descargar e instalar desde el siguiente enlace:

[https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software)

### Instalar ESP8266 en arduino

Lo primero que tenemos que añadir al repositorio de placas de desarrollo compatibles es el repositorio GitHub donde se encuentra todo el entorno de ESP8266. Para ello, hay que abrir las preferencias (Archivo -> Preferencias) y añadir una nueva URL al gestor de tarjetas tal y como se ve en la siguiente imagen:

[http://arduino.esp8266.com/stable/package_esp8266com_index.json](http://arduino.esp8266.com/stable/package_esp8266com_index.json)

![image alt text](doc/files/image_4.png)

Una vez añadida le damos a OK y vamos al gestor de tarjetas (Herramientas -> placa-> Gestor de tarjetas). Allí deberemos buscar la nueva tarjeta o placa que hemos añadido, en este caso la ESP8266. Seleccionamos la versión `2.4.0` y le damos a instalar. Esto llevará unos minutos mientras se descargan todas las utilidades y librerías.

![image alt text](doc/files/image_5.png)

Ya sólo nos queda seleccionar la nueva tarjeta, en este caso la placa **NodeMCU V1.0** para que el sistema nos detecte la placa.

Además, deberemos configurar el puerto serie que está empleando el sistema. En el caso de Windows, deberemos seleccionar el puerto COM correspondiente (el que aparece en la sección de instalación del driver). En el caso de MacOS y Linux, deberemos seleccionar el dispositivo correspondiente con el formato /dev/* (dependiendo del sistema operativo)

Antes de continuar, vamos a instalar unas librerías que van a facilitar el uso de la placa (buscar en Programa -> Incluir Librería -> Gestor de Librerías):

1. ArduinoJson.h          - https://github.com/bblanchon/ArduinoJson
2. WiFiManager.h (opcional) [Versión 0.14.0]        - https://github.com/tzapu/WiFiManager
3. Adafruit_BMP085 (opcional) [Version 1.0.0]        - https://github.com/adafruit/Adafruit-BMP085-Library

## Instalación de Postman

Para hacer pruebas con la API de FIWARE será necesario disponer de una herramienta que permita hacer peticiones HTTP e interactuar con ésta. En este caso, nosotros recomendamos la herramienta Postman, que permite gestionar las colecciones de peticiones, por lo que será muy sencillo realizar las operaciones necesarias con la colección predefinida que podréis descargar en este mismo repositorio.

[Descargar](https://www.getpostman.com)

[Configuración de postman](https://github.com/FIWAREZone/IoT_Course/tree/master/postman)

## Instalación drivers USB

Es necesario instalar los drivers para el convertidor de USB a USART a 3.3V incluido en la placa de desarrollo. En el mercado existen distintos fabricantes de esta placa que pueden integrar distintos circuitos integrados que realizan esta función. En este caso, deberemos instalar el driver correspondiente. En cualquier caso, no existe ningún tipo de incompatibilidad entre ellos, puduiendose instalar ámbos al unísono. Para probar que todo funciona de forma correcta y asegurarno que driver instalar, lo ideal es esperar a que se disponga de la placa.


En la imagen a continuación podemos diferenciar los dos modelos más extendidos que de convertidor de USB a USART en las placas NodeMCU, que son el CH430G y el CP2102/3
![image alt text](doc/files/image_6.png)

En el caso del chip CP2102/3, del fabricante SiLabs, podremos descargar los drivers para los distintos sistemas operativos desde la página web del fabricante:

[https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

En el caso del chip CH430G, podremos descargar los driver desde la siguiente página web:

[Windows](http://www.wch.cn/downloads/CH341SER_ZIP.html)

[MacOS](http://www.wch.cn/downloads/CH341SER_MAC_ZIP.html)

[Linux](http://www.wch.cn/download/CH341SER_LINUX_ZIP.html)


### MAC OSX

Para identificar que tenemos instalado correctamente los drivers del dispositivo, podremos ver en el informe del sistema (acerca de este mac) el dispositivo USB CP2102 USB to UART Bridge Controller o el correspondiente al CH430G

![image alt text](doc/files/image_1.png)

Otra forma adicional de saber si tenemos el driver instalado es abriendo un terminal y ejecutando `ls /dev/tty.*`. En este caso nos debería aparecer algún disposivo del tipo `/dev/tty.usbserial-XXXX` o `/dev/tty.SLAB_USBtoUART`

En las últimas versiones de macOS es necesario habilitar el driver en el panel de control para que se ejecute. Para ello hay que ir a la sección de seguridad y privacidad y permitir la ejecución del software.

![image alt text](doc/files/image_2.png)

### Windows

Tras descargar y ejecutar el instalador del driver provisto por el fabricante y, si fuera necesario, tras reiniciar el equipo nos debe aparecer algo similar a la siguiente imagen en el administrador de dispositivos (depende del controlador USB a UART):

![image alt text](doc/files/image_3.png)

Una vez identificado, habrá que recordar el puerto COM para configurarlo en la aplicación arduino.

### Linux

Generalmente, las últimas versiones del kernel de linux traen soporte nativo para este dispositivo. En caso contrario, seguir las instrucciones del fabricante para la distribución en concreto.