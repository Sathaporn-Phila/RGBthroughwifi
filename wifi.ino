#include <ESP8266WiFi.h>
#define LED 13
const char* ssid = "ST-APARTMENT 3";
const char* password = "0988549374";
unsigned char status_led = 0;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while (!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  client.flush();
  if (req.indexOf("/red") != -1)
  {
    
    Serial.print("255,0,0");
  }
  else if (req.indexOf("/blue") != -1)
  {
    Serial.print("0,0,255");
  }
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r \n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1 style='text-align: center'>LED through Wifi</h1>\r\n";
  web += "<p>\r\n";
  web += "<a href=\"/red\">\r\n";
  web += "<button style='font-size:50px;left:50%'>red</button>\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  web += "<a href=\"/blue\">\r\n";
  web += "<button style='font-size:50px;left:50%'>blue</button>\r\n";
  web += "</a>\r\n";
  web += "</body>\r\n";
  web += "</html>\r\n";
  client.print(web);
}
