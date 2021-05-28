/*********************************************
 *      Variables definition
 ********************************************/
#define _WIFI_NETWORK "myNetwokr"
#define _WIFI_PASSWORD "myPassword"

#define _FIWARE_device_ID "SENSOR_ID"
#define _FIWARE_server "iota-int.iotplatform.telefonica.com"
#define _FIWARE_port "8085"
#define _FIWARE_apikey "APIKEY"

#define _SENDING_INTERVAL_MS 15000
/********************************************/

// Libraries
#include <FS.h>                   //this needs to be first, or it all crashes and burns...

//ESP8266 Native libraries
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

//External libraries
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

// Function definitios
void dataSenderCallback();

/*************** Global Variables ***************/
// Timing Variables
unsigned long previousMillis=0;
unsigned long deltaMillis=_SENDING_INTERVAL_MS;

//ESP8266 objects
ESP8266HTTPUpdateServer httpUpdater;    //For HTTP OTA Update
HTTPClient http;                        //Declare object of class HTTPClient

//FIWARE Variables
String FIWARE_device_ID   = _FIWARE_device_ID;
String FIWARE_server      = _FIWARE_server;
String FIWARE_port        = _FIWARE_port;
String FIWARE_apikey      = _FIWARE_apikey;

//Other Variables
int transmisionStatus = 0;
char rxBuf[64];
int rxBufIndex;
char dev_hostname[30];



/*********************************************
 *                Setup Code
 ********************************************/
void setup() {
  //serial Port setup
  Serial.begin(9600);
  Serial.println("\r\n\n\n\n\r***********************\n\rFIWARE Zone IoT Device");

  //Setup Hostname
  (String("SC-") + ESP.getChipId()).toCharArray(dev_hostname, 30);
  Serial.print("Dev-name: ");
  Serial.println(dev_hostname);

//Configuring WIFI
  WiFi.begin(_WIFI_NETWORK, _WIFI_PASSWORD);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

}



/*********************************************
 *                Loop Code
 ********************************************/

void loop() {

  if (millis()>previousMillis+_SENDING_INTERVAL_MS){
    previousMillis=millis();
    //Execute task
    dataSenderCallback();
  }
}





int ultralightSend (String URL, String port, String Token, String ID, String Body) {
  int httpCode = 0;
  
  Serial.println("\nSENDING DATA TO IoTAgent - Ultralight");
  Serial.println("   http://" + URL + ":" + port + "/iot/d?k=" + Token + "&i=" + ID + "&getCmd=1");
  
  // Configure URL and headers
  http.begin("http://" + URL + ":" + port + "/iot/d?k=" + Token + "&i=" + ID + "&getCmd=1");
  http.addHeader("Content-Type", "text/plain");

  // Execute request and get response payload 
  httpCode = http.POST(Body);
  String payload = http.getString();

  //Print HTTP response
  Serial.print("   Request executed.Return code: ");
  Serial.print(httpCode);
  Serial.print(". Response payload: ");
  Serial.println(payload);

  //Close connection
  http.end();  											                  
  return httpCode;
}



String dataReaderSensor(){

    String t_meas;
    String p_meas;
    String a_meas;

    t_meas = random(0,40);
    p_meas = random(100000,102000);
    a_meas = random(0,3000);

    Serial.println("\nReading data from sensors:");
    Serial.println(" - T=" + t_meas + " *C");
    Serial.println(" - P=" + p_meas + " Pa");
    Serial.println(" - A=" + a_meas + " m");

    String r = "t|"+ t_meas +"|p|"+ p_meas +"|a|"+ a_meas;

  return r;
}



void dataSenderCallback(){
  int returnCode = ultralightSend(FIWARE_server,FIWARE_port,FIWARE_apikey,FIWARE_device_ID,dataReaderSensor());
   if (returnCode ==200){
      Serial.println("Data sent successfully to FIWARE\n\n");
    }
    else{
      Serial.println("Failure sending data to FIWARE\n\n");
    }
}
