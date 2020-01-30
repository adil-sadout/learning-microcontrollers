

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/*Web Server*/

const char index_html[] PROGMEM={"<!DOCTYPE html>\n<html>\n<head>\n\t<title>ESP8266 TEST</title>\n\t<meta http-equiv=\"refresh\" content=\"5\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" >\n\n\n</head>\n<body>\n\t<div class=\"title\">\n\t\t<h1>Testing The Esp8266</h1>\n\t</div>\n\t<div class=\"container\">\n\t\t<div class=\"temp infobox\">\n\t\t\t<h2>Temperature</h2>\n\t\t\t<p>30 C</p>\n\t\t</div>\n\n\t\t<div class=\"humid infobox\">\n\t\t\t<h2>Humidity</h2>\n\t\t\t<p>46%</p>\n\t\t</div>\n\t</div>\n\n\n\t<script type=\"text/javascript\">\n\t\t//Variables\n\t\tvar humidity= \"25%\"; //the value should be a variable that stores the output of a sensor\n\t\tvar temperature= \"47C\" //the value should be a variable that stores the output of a sensor\n\n\n\t\t//selecting the temperature & humidity\n\n\t\t//temperature\n\t\tvar temp = document.querySelector(\".temp p\");\n\n\n\t\t//humidity\n\t\tvar humid = document.querySelector(\".humid p\");\n\n\n\n\t\t//changing the variable\n\t\ttemp.textContent = temperature;\n\n\t\thumid.textContent = humidity;\n\t</script>\n\n</body>\n</html>"};
const char style_css[] PROGMEM={"*{\n\tmargin: 0;\n\tpadding: 0;\n\ttext-align: center;\n}\n\n.title{\n\tpadding: 30px;\n}\n\n\n\n\n.container{\n\tpadding: 50px 0;\n\tbackground-color: lightgray;\n}\n\n\n\n.infobox{\n\twidth: 300px;\n\tdisplay: inline-block;\n\tbackground-color: lightblue;\n\tmargin: 0 60px;\n\theight: 250px;\n\tposition: relative;\n}\n\n.infobox h2{\n\tpadding: 15px;\n\tfont-size: 40px;\n}\n\n.infobox p{\n\tfont-size: 70px;\n\tposition: absolute;\n\tleft: 50%;\n\ttop: 50%;\n\ttransform: translate(-50%,-50%);\n}"};
//const char script_js[] PROGMEM={"//Variables\nvar humidity= \"25%\"; //the value should be a variable that stores the output of a sensor\nvar temperature= \"47C\" //the value should be a variable that stores the output of a sensor\n\n\n//selecting the temperature & humidity\n\n//temperature\nvar temp = document.querySelector(\".temp p\");\n\n\n//humidity\nvar humid = document.querySelector(\".humid p\");\n\n\n\n//changing the variable\ntemp.textContent = temperature;\n\nhumid.textContent = humidity;"};

/* Set these to your desired credentials. */

const char *ssid = APSSID;
const char *password = APPSK;



IPAddress local_IP(192,168,100,1);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);



ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.100.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send_P(200, "text/html", index_html);
}

void handleCss() {
  server.send_P(200, "text/css", style_css);
}
/*
void handleJs(){
  server.send_P(200, "text/javascript", script_js);
}*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/style.css", handleCss);
  /*server.on("/script.js", handleJs);*/
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
