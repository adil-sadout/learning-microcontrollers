/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

/* Set these to your desired credentials. */

const char index_html[] PROGMEM={"<!DOCTYPE html>\n<html>\n<head>\n\t<title>ESP8266 TEST</title>\n\t<meta http-equiv=\"refresh\" content=\"6\" >\n\t<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\" >\n</head>\n<body>\n\t<div class=\"title\">\n\t\t<h1>Testing The Esp8266</h1>\n\t</div>\n\t<div class=\"container\">\n\t\t<div class=\"temp infobox\">\n\t\t\t<h2>Temperature</h2>\n\t\t\t<p>30 C</p>\n\t\t</div>\n\n\t\t<div class=\"humid infobox\">\n\t\t\t<h2>Humidity</h2>\n\t\t\t<p>46%</p>\n\t\t</div>\n\t</div>\n\n</body>\n</html>"};
const char style_css[] PROGMEM={"*{\n\tmargin: 0;\n\tpadding: 0;\n\ttext-align: center;\n}\n\n.title{\n\tpadding: 30px;\n}\n\n\n\n\n.container{\n\tpadding: 50px 0;\n\tbackground-color: lightgray;\n}\n\n\n\n.infobox{\n\twidth: 300px;\n\tdisplay: inline-block;\n\tbackground-color: lightblue;\n\tmargin: 0 60px;\n\theight: 250px;\n\tposition: relative;\n}\n\n.infobox h2{\n\tpadding: 15px;\n\tfont-size: 40px;\n}\n\n.infobox p{\n\tfont-size: 70px;\n\tposition: absolute;\n\tleft: 50%;\n\ttop: 50%;\n\ttransform: translate(-50%,-50%);\n}"};
//const char style_css[] PROGMEM={};



const char *ssid = APSSID;
const char *password = APPSK;



IPAddress local_IP(192,168,100,1);
IPAddress gateway(192,168,100,1);
IPAddress subnet(255,255,255,0);



ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send_P(200, "text/html", index_html);
  server.send_P(200, "text/css", style_css);
}

void handleCss() {
  server.send_P(200, "text/css", style_css);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/style.css", handleCss);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
