/*
  Put the BME280 into low power mode (aka Forced Read)
  Nathan Seidle @ SparkFun Electronics
  March 23, 2018

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14348 - Qwiic Combo Board
  https://www.sparkfun.com/products/13676 - BME280 Breakout Board

  This example shows how used the 'Forced Mode' to obtain a reading then put the
  sensor to sleep between readings.
*/

#include <Wire.h>

#include "SparkFunBME280.h"
BME280 mySensor;
float humidity;
float temperature;
String temperature_string;
String Humidity_string;
//website

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "JakChok"
#define APPSK  "password"
#endif

/*Web Server*/
//const char index_html[] PROGMEM={"<!DOCTYPE html>\n<html>\n<head>\n\t<title>ESP8266 TEST</title>\n\t<meta http-equiv=\"refresh\" content=\"5\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" >\n\n\n</head>\n<body>\n\t<div class=\"title\">\n\t\t<h1>Testing The Esp8266</h1>\n\t</div>\n\t<div class=\"container\">\n\t\t<div class=\"temp infobox\">\n\t\t\t<h2>Temperature</h2>\n\t\t\t<p>30 C</p>\n\t\t</div>\n\n\t\t<div class=\"humid infobox\">\n\t\t\t<h2>Humidity</h2>\n\t\t\t<p>46%</p>\n\t\t</div>\n\t</div>\n\n\n\t<script type=\"text/javascript\">\n\t\t//Variables\n\t\tvar humidity= \"25%\"; //the value should be a variable that stores the output of a sensor\n\t\tvar temperature= \"47C\" //the value should be a variable that stores the output of a sensor\n\n\n\t\t//selecting the temperature & humidity\n\n\t\t//temperature\n\t\tvar temp = document.querySelector(\".temp p\");\n\n\n\t\t//humidity\n\t\tvar humid = document.querySelector(\".humid p\");\n\n\n\n\t\t//changing the variable\n\t\ttemp.textContent = temperature;\n\n\t\thumid.textContent = humidity;\n\t</script>\n\n</body>\n</html>"};





const char first[]{"<!DOCTYPE html>\n<html>\n<head>\n\t<title>ESP8266 TEST</title>\n\t<meta http-equiv=\"refresh\" content=\"5\">\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\t<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" >\n\n\n</head>\n<body>\n\t<div class=\"title\">\n\t\t<h1>Testing The Esp8266</h1>\n\t</div>\n\t<div class=\"container\">\n\t\t<div class=\"temp infobox\">\n\t\t\t<h2>Temperature(C)</h2>\n\t\t\t<p>30</p>\n\t\t</div>\n\n\t\t<div class=\"humid infobox\">\n\t\t\t<h2>Humidity(%)</h2>\n\t\t\t<p>46%</p>\n\t\t</div>\n\t</div>\n\n\n\t<script type=\"text/javascript\">\n\t\t//Variables\n\t\tvar humidity="};

const char between[]{";//the value should be a variable that stores the output of a sensor\n\t\tvar temperature="};


const char last[]{";//the value should be a variable that stores the output of a sensor\n\n\n\t\t//selecting the temperature & humidity\n\n\t\t//temperature\n\t\tvar temp = document.querySelector(\".temp p\");\n\n\n\t\t//humidity\n\t\tvar humid = document.querySelector(\".humid p\");\n\n\n\n\t\t//changing the variable\n\t\ttemp.textContent = temperature;\n\n\t\thumid.textContent = humidity;\n\t</script>\n\n</body>\n</html>"};
/* Set these to your desired credentials. */


const char style_css[]{"*{\n\tmargin: 0;\n\tpadding: 0;\n\ttext-align: center;\n}\n\n.title{\n\tpadding: 30px;\n}\n\n\n\n\n.container{\n\tpadding: 50px 0;\n\tbackground-color: lightgray;\n}\n\n\n\n.infobox{\n\twidth: 300px;\n\tdisplay: inline-block;\n\tbackground-color: lightblue;\n\tmargin: 0 60px;\n\theight: 250px;\n\tposition: relative;\n}\n\n.infobox h2{\n\tpadding: 15px;\n\tfont-size: 40px;\n}\n\n.infobox p{\n\tfont-size: 70px;\n\tposition: absolute;\n\tleft: 50%;\n\ttop: 50%;\n\ttransform: translate(-50%,-50%);\n}\n\n\n\n@media screen and (max-width: 850px) {\n \n\t.infobox{\n\t\t\t\twidth: 300px;\n\t\t\t\tdisplay: inline-block;\n\t\t\t\tbackground-color: lightblue;\n\t\t\t\tmargin: 30px;\n\t\t\t\theight: 250px;\n\t\t\t\tposition: relative;\n\t\t\t}\n\n\n\n\n}\n\n\n@media screen and (max-width: 450px) {\n \n\t.infobox{\n\t\t\t\twidth: 70%;\n\t\t\t\tdisplay: inline-block;\n\t\t\t\tbackground-color: lightblue;\n\t\t\t\tmargin: 30px;\n\t\t\t\theight: 250px;\n\t\t\t\tposition: relative;\n\t\t\t}\n\n\t.infobox h2{\n\t\t\t\t\tpadding: 30px 15px 15px 15px;\n\t\t\t\t\tfont-size: 30px;\n\t\t\t\t}\n\n\t.infobox p{\n\t\t\t\t\tfont-size: 60px;\n\t\t\t\t\tposition: absolute;\n\t\t\t\t\tleft: 50%;\n\t\t\t\t\ttop: 50%;\n\t\t\t\t\ttransform: translate(-50%,0%);\n\t\t\t}\n\n\n}"};


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
  temperature_string = ""+String((float)temperature,1);
  Humidity_string = ""+String((float)humidity,1);
  String index_html = first+ Humidity_string + between + temperature_string + last;


 
// Length (with one extra character for the null terminator)
int str_len = index_html.length() + 1; 
 
// Prepare the character array (the buffer) 
char char_array[str_len];
 
// Copy it over 
index_html.toCharArray(char_array, str_len);




  
  server.send_P(200, "text/html",char_array);
}

void handleCss() {
  server.send_P(200, "text/css", style_css);
}
//website end



void setup()
{
  Serial.begin(9600);

  //Sensor
  Wire.begin();
  Wire.setClock(400000);
  mySensor.setI2CAddress(0x76);
  mySensor.beginI2C();
  mySensor.setMode(MODE_SLEEP);




  //website
  WiFi.softAPConfig(local_IP, gateway, subnet);
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/style.css", handleCss);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{

  //Sensor
  mySensor.setMode(MODE_FORCED);
  Serial.print(" Humidity: ");
  humidity = mySensor.readFloatHumidity();
  Serial.print(humidity, 0);
  Serial.print(" Temperature: ");
  temperature = mySensor.readTempC();
  Serial.print(temperature, 2);
  Serial.println();

  server.handleClient();

  delay(5000);
  //website
}
