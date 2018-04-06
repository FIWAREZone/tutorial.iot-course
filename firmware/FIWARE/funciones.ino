//const char HTTP_MAIN_FORM[] PROGMEM  = "<form action=\"/wifi\" method=\"get\"><button>WiFi menu</button></form><br/></form><br/><form action=\"/sec\" method=\"get\"><button>SecuryCable</button></form><br/><form action=\"/test\" method=\"get\"><button>test</button></form><form action=\"/wrst\" method=\"get\"><button>Reset wifi conf</button></form><form action=\"/help\" method=\"get\"><button>Help</button></form>";




/** IP to String? */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}




