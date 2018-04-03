



//const char HTTP_MAIN_FORM[] PROGMEM  = "<form action=\"/test\" method=\"get\"><button>Test</button></form><br/><form action=\"/wifi\" method=\"get\"><button>Setup Wifi</button></form><br/><form action=\"/wrst\" method=\"get\"><button>Clear wifi setup</button></form><br/><form action=\"/webota\" method=\"get\"><button>Update</button></form><br/><form action=\"/postul2\" method=\"get\"><button>POST UL2</button></form><br/><form action=\"/help\" method=\"get\"><button>Help</button></form><br/>";
const char HTTP_MAIN_FORM[] PROGMEM  = "<form action=\"/wifi\" method=\"get\"><button>Setup Wifi</button></form><br/><form action=\"/wrst\" method=\"get\"><button>Clear wifi setup</button></form><br/><form action=\"/webota\" method=\"get\"><button>Update</button></form><br/><form action=\"/postul2\" method=\"get\"><button>POST UL2</button></form><br/><form action=\"/help\" method=\"get\"><button>Help</button></form><br/>";
const char HTTP_BACK_BUTTON[] PROGMEM  = "<br/><br/><form action=\"/\" method=\"get\"><button>Back</button></form><br/>";
const char HTTP_REDIRECT_5S[] PROGMEM  = "<meta http-equiv='refresh' content='5;url=/' />";





void handleRoot() {

  String page = FPSTR(HTTP_HEAD);
  page.replace("{v}", "FIWARE_Zone_IoT");
  page += FPSTR(HTTP_STYLE);
  page += FPSTR(HTTP_HEAD_END);
  page += F("<h1>FIWARE IoT Device</h1>");
  page += F("<h3>Menu</h3>");
  page += FPSTR(HTTP_MAIN_FORM);
  page += String("hostname:");
  page += String(dev_hostname);
  page += String(".local");
  //page += F("Module will reset in a few seconds.");
  page += FPSTR(HTTP_END);
  server.send(200, "text/html", page);

}


void handleWifi() {
  String page = FPSTR(HTTP_HEAD);
  page.replace("{v}", "Info");
  page += FPSTR(HTTP_SCRIPT);
  page += FPSTR(HTTP_STYLE);
  page += FPSTR(HTTP_HEAD_END);
  page += FPSTR(HTTP_REDIRECT_5S);
  page += F("<h1>FIWARE-WiFi</h1>");
  page += F("<h3>Redirigiendo al panel de configuracion Wifi.</h3>");
  page += F("Espere por favor a que se abra el panel de configuracion de redes wifi");
  page += FPSTR(HTTP_END);
  server.send(200, "text/html", page);


    server.stop();
    Serial.println("CONFIG WIFI");


    wifiManager.setTimeout(120);
    WiFiManager wifiManager;
    wifiManager.startConfigPortal(WiFi_SoftAP_WiFi_Name);
    Serial.println("Connected.");
    Serial.println("local ip:");
    Serial.println(WiFi.localIP());
    server.begin();    
}



void handleWrst() {
  String page = FPSTR(HTTP_HEAD);
  page.replace("{v}", "Info");
  page += FPSTR(HTTP_SCRIPT);
  page += FPSTR(HTTP_STYLE);
  page += FPSTR(HTTP_HEAD_END);
  page += FPSTR(HTTP_REDIRECT_5S);
  page += F("<h1>FIWARE-WiFi</h1>");
  page += F("<h3>Borrando la configuracion wifi.</h3>");
  page += F("El dispositivo se desconectara de la red, por favor conectese al la red creada por BasculaWifi para su configuracion.");
  page += FPSTR(HTTP_END);
  server.send(200, "text/html", page);
    
    
    Serial.println("RESET SSID DATA");
     
    //server.send(statusCode, "text/html", content);
   
    //reset and try again, or maybe put it to deep sleep
    delay(3000);
    wifiManager.resetSettings();
    delay(5000);
    ESP.reset();
    delay(5000);
}



void handleWebota(){
 String page = FPSTR(HTTP_HEAD);
  page.replace("{v}", "Info");
  page += FPSTR(HTTP_SCRIPT);
  page += FPSTR(HTTP_STYLE);
  page += FPSTR(HTTP_HEAD_END);
  page += F("<h1>FIWARE-WiFi</h1>");
  page += F("<h3>Help</h3>");
  page += F("Aqui aparece la informacion que puede ser de ayuda.");
  page += FPSTR(HTTP_BACK_BUTTON);
  page += FPSTR(HTTP_END);
  server.send(200, "text/html", page);

}


void handleHelp(){
 String page = FPSTR(HTTP_HEAD);
  page.replace("{v}", "Info");
  page += FPSTR(HTTP_SCRIPT);
  page += FPSTR(HTTP_STYLE);
  page += FPSTR(HTTP_HEAD_END);
  page += F("<h1>FIWARE-WiFi</h1>");
  page += F("<h3>Help</h3>");
  page += F("Aqui aparece la informacion que puede ser de ayuda.");
  page += FPSTR(HTTP_BACK_BUTTON);
  page += FPSTR(HTTP_END);
  server.send(200, "text/html", page);

}

void handlePostUL2(){
  String page = FPSTR(HTTP_HEAD);
  page.replace("{v}", "Info");
  page += FPSTR(HTTP_SCRIPT);
  page += FPSTR(HTTP_STYLE);
  page += FPSTR(HTTP_HEAD_END);
  page += F("<h1>Enviar datos a FIWARE</h1>");
  page += F("<form action=\"/postul2data\" method=\"post\">  Temperature: <input type=\"number\" name=\"tmp\" min=\"-273\" max=\"999\"><br>  Relative Humidity: <input type=\"number\" name=\"rh\" min=\"0\" max=\"100\"><br> <button type=\"submit\" value=\"Submit\">Submit</button> </form>");
  
  page += FPSTR(HTTP_BACK_BUTTON);
  page += FPSTR(HTTP_END);
  server.send(200, "text/html", page);
}



void handlePostUL2data(){

      //Search form post values  
      String tmp, rh;
        if (server.args() > 0 ) {
            for ( uint8_t i = 0; i < server.args(); i++ ) {
              if (server.argName(i) == "tmp") {
                 // do something here with value from server.arg(i);
                 tmp = server.arg(i);
              }
              else if(server.argName(i) == "rh"){
                rh = server.arg(i);
              }
           }
        }
    

      //POST Data      
      String page = FPSTR(HTTP_HEAD);
      page.replace("{v}", "Info");
      page += FPSTR(HTTP_SCRIPT);
      page += FPSTR(HTTP_STYLE);
      page += FPSTR(HTTP_HEAD_END);
      page += F("<h1>Enviando datos a FIWARE</h1>");

      //Parse response
      int returnCode = ultralightSend(FIWARE_server,FIWARE_port,FIWARE_token,FIWARE_ID,"temp|"+tmp+"#hr|"+rh);
      if (returnCode ==200){
          page += F("<h3>Resultado</h3>");
          page += F("La peticion se ha ejecutado correctamente");
      }
      else{
          page += F("<h3>Resultado</h3>");
          page += F("Ha habido un error en la peticion");
          page += String(returnCode);
      }
  
      //End page
      page += FPSTR(HTTP_BACK_BUTTON);
      page += FPSTR(HTTP_END);
      server.send(200, "text/html", page);
    
}








