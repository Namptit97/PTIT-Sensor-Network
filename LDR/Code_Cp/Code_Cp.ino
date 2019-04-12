#include <ESP8266WiFi.h>

const char* ssid = "TP-LINK_EA597A";
const char* password = "05175499";

const int LED = D3; // led connected to D0
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
  if(request.indexOf("/LED=ON") >= 0 )
  {
    digitalWrite(LED, HIGH); // Turn ON LED
    value = HIGH;
  }
  if(request.indexOf("/LED=OFF") >= 0)
  {
    digitalWrite(LED, LOW); // Turn OFF LED
    value = LOW;
  }

  for (int i = 0 ; i < 256 ; i ++)
  {
      char a[100],b[100];
      sprintf(a , "Value /9/%d/pwm", i);
      sprintf(b , "Value /10/%d/pwm", i);
      if( request.indexOf(a) >=0) {

        Serial.print("led Get ");
        Serial.println(i);
        analogWrite(LED , i);
     
        }  
//      if( request.indexOf(b) >=0) {
//        Serial.print("coi Get ");
//        Serial.println(i);
//        analogWrite(output4 , i);
//       
//        
//        }
   }

/*------------------HTML Page Creation---------------------*/

  client.println("HTTP/1.1 200 OK"); // standalone web server with an ESP8266
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
//  client.println("<body background=\"/home/namphc/Desktop/LDR/LEDControlwithWEB/iot.png\">");
//  client.print("<div style = 'margin: 35px auto; background-image:url(iot.png)'>");
  client.println("<body><h1>PHAM HUY NAM B15DCDT137</h1>");
  client.print("<h1>LED: ");
 
  if(value == HIGH)
  {
    client.println("<div <p><a href=\"/LED=ON\"\"><button style='cursor:pointer; width:100px,hight:200px; font-size:50px'>ON</button></a></p> </div>");
//    client.print("ON</h1>");
  }
  else
  {
    client.println("<div <p><a href=\"/LED=OFF\"\"><button style='cursor:pointer;width:100px,hight:200px; font-size:50px'>OFF</button></a></p></div>");  
//    client.print("OFF</h1>");
  }
//  client.println("<br>");
//client.println("<a href=\"/LED=ON\"\"><button style='cursor:pointer; width:100px,hight:200px; font-size:50px'>ON</button></a>");
//  client.println("<a href=\"/LED=OFF\"\"><button style='cursor:pointer;width:100px,hight:200px; font-size:50px'>OFF</button></a>");
  client.println("<br>"); // Go to the next line.
//  client.println("<input type=\"range\" name=\"value\" min=\"0\" max=\"255\" value=\"128\" style=\"width:30%\" />");
  client.println("<div> <input type=\"range\" min=\"0\" max=\"255\" value=\"255\" class=\"led_slider\" id=\"led_Range\">");
  client.println("<p>LED9 Value: <span id=\"led\"></span></p></div>");

  client.println("<div> <input type=\"range\" min=\"0\" max=\"255\" value=\"255\" class=\"coi_slider\" id=\"coi_Range\">");
  client.println("<p>coi Value: <span id=\"coi\"></span></p></div>");
            
//  client.println("<input type=\"range\" min=\"0\" max=\"255\" value=\"255\" style=\"width:30%\"id=\"myRange\" />");
//  client.println("<p>Value: <span id=\"demo\"></span></p>");
  client.println("<script>var led_slider = document.getElementById(\"Led_Range\");");
  client.println("var led_output = document.getElementById(\"led\");");

  client.println("var coi_slider = document.getElementById(\"coi_Range\");");
  client.println("var coi_output = document.getElementById(\"coi\");");

  client.println("var xhr = new XMLHttpRequest();");
  client.println("led_output.innerHTML = led_slider.value;");
  client.println("coi_output.innerHTML = coi_slider.value;");

  client.println("led_slider.oninput = function() { led_output.innerHTML = this.value;");       
  client.println("xhr.open('Value', \"9/\" + led_output.innerHTML+\"/pwm\", true);");
  client.println("xhr.send();}");
  client.println("coi_slider.oninput = function() { coi_output.innerHTML = this.value;");       
  client.println("xhr.open('Value', \"10/\" + coi_output.innerHTML+\"/pwm\", true);");

  client.println("xhr.send();} </script>");
//  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  client.stop();
  Serial.println("Client disonnected");
  Serial.println("");
}
