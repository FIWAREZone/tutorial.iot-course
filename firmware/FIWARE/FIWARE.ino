#include <FS.h>                   //this needs to be first, or it all crashes and burns...

//ESP8266 Native libraries
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

//External libraries
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

//#include "settings.h"

ESP8266WebServer server(80);            //Web server
WiFiManager wifiManager;                //Wifi Manager to setup WIFI SSID
ESP8266HTTPUpdateServer httpUpdater;    //For HTTP OTA Update
HTTPClient http;                        //Declare object of class HTTPClient




/*************** Global Variables ***************/
//FIWARE Variables
String FIWARE_ID = "Sensor123CMD";
String FIWARE_server = "195.235.93.235";
String FIWARE_port = "8085";
String FIWARE_token = "t3ftmt5e1pj9cdws5hzlalpky";
//String FIWARE_token = "REEMPLAZAR_APIKEY";
const char* WiFi_SoftAP_Name = "FIWAREZone_IoT";
const char* WiFi_SoftAP_WiFi_Name = "FIWAREZone_IoT_Wifi";


//OTA
const char* update_path = "/webota";
const char* update_username = "admin";
const char* update_password = "admin";

char dev_hostname[30];


//serial
int transmisionStatus = 0;
char rxBuf[64];
int rxBufIndex;





void setup() {
  //serial Port setup
  Serial.begin(9600);
  Serial.println();

  //Setup Hostname
  (String("SC-") + ESP.getChipId()).toCharArray(dev_hostname, 30);
  Serial.print("Dev-name: ");
  Serial.println(dev_hostname);


  //reset settings - for testing
  //wifiManager.resetSettings();

  wifiManager.setTimeout(5);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here FIWAREWifi and goes into a blocking loop awaiting configuration
  
  if (!wifiManager.autoConnect(WiFi_SoftAP_Name, "")) {
    Serial.println("failed to connect and hit timeout");
    
    //Start Soft AP
    WiFi.softAP(WiFi_SoftAP_Name, "");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  }
  else {

    //if you get here you have connected to the WiFi
    Serial.println("Connected!");

    // Set up mDNS responder:
    if (!MDNS.begin(dev_hostname)) {
      Serial.println("Error setting up MDNS responder!");
      while (1) {
        delay(1000);
      }
    }
    Serial.println("mDNS responder started");

    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);

  }

  //Start OTA updater
  httpUpdater.setup(&server, update_path, update_username, update_password);

  // Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");

  //Bind Webserver URL functions
  server.on ( "/", handleRoot );
  server.on ( "/wrst", handleWrst );
  server.on ( "/wifi", handleWifi );
  server.on ( "/webota", handleWebota );
  server.on ( "/help", handleHelp );
  server.on ( "/postul2", handlePostUL2 );
  server.on ( "/postul2data", handlePostUL2data );

}



void loop() {
  //WebServer task
  server.handleClient();
}





int ultralightSend (String URL, String port, String Token, String ID, String Body) {
  int httpCode = 0;
  
  Serial.println("http://" + URL + ":" + port + "/iot/d?k=" + Token + "&i=" + ID + "&getCmd=1");        
  http.begin("http://" + URL + ":" + port + "/iot/d?k=" + Token + "&i=" + ID + "&getCmd=1");            //Specify request destination

  http.addHeader("Content-Type", "text/plain");       	//Specify content-type header

  httpCode = http.POST(Body);           				//Send the Body
  String payload = http.getString();                    //Get the response payload

  Serial.println("Request Done");
  Serial.print("Return code: ");
  Serial.println(httpCode);   							//Print HTTP return code
  Serial.print("Response payload: ");
  Serial.println(payload);    							//Print request response payload

  http.end();  											//Close connection
  return httpCode;
}



