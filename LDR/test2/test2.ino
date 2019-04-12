#include <ESP8266WiFi.h>

const char* ssid = "Ptit Team";
const char* password = "1mot2hai3ba";

int LED = 0; // led connected to D0
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  server.begin();  // Starts the Server
  Serial.println("Server started");

  Serial.print("IP Address of network: "); // Prints IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("Waiting for new client");
  while(!client.available())
  {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value = LOW;
  if(request.indexOf("/LED=ON") != -1)
  {
    digitalWrite(LED, HIGH); // Turn ON LED
    value = HIGH;
  }
  if(request.indexOf("/LED=OFF") != -1)
  {
    digitalWrite(LED, LOW); // Turn OFF LED
    value = LOW;
  }

/*------------------HTML Page Creation---------------------*/

  client.println("HTTP/1.1 200 OK"); // standalone web server with an ESP8266
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<style>html { font-family: Cairo; display: inline; margin: 0px auto; text-align: center; background-color: #ccffb3;}");
  client.print("<h1>LED: ");
 
  if(value == HIGH)
  {
    client.print("ON</h1>");
  }
  else
  {
    client.print("OFF</h1>");
  }
  client.println("<br>");
  client.println(".button { background-color: #006699; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 35px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  client.println("<svg width=\"300\" height=\"80\"><text fill=\"#00bfbf\" font-family=\"serif\" font-size=\"24\" id=\"svg_1\" stroke=\"#000000\" text-anchor=\"middle\" transform=\"matrix(1.35388 0 0 1.42308 -6.66283 -8.67308)\" x=\"86.5\" xml:space=\"preserve\" y=\"41.5\">WELCOME TO MY WEBSITE</text></svg>");
  client.println("<a href=\"/LED=ON\"\"><button style='cursor:pointer; width:100px,hight:200px; font-size:50px'>ON</button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button style='cursor:pointer;width:100px,hight:200px; font-size:50px'>OFF</button></a>");
  client.println("<br>"); // Go to the next line.
  client.println("<body><h1>Welcome to THCS</h1>");
   
//  client.println("<input type=\"range\" name=\"value\" min=\"0\" max=\"255\" value=\"128\" style=\"width:30%\" />");
  client.println("<input type=\"range\" min=\"0\" max=\"255\" value=\"255\" style=\"width:30%\"id=\"myRange\" />");
  client.println("<p>Value: <span id=\"demo\"></span></p>");
  client.println("<script>var slider = document.getElementById(\"myRange\");var output = document.getElementById(\"demo\");output.innerHTML = slider.value;slider.oninput = function() {output.innerHTML = this.value;}</script>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
