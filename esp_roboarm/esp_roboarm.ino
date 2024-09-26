#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#define GREEN_LED 16
#define RED_LED 4
#define BLUE_LED 2
#define YELLOW_LED 12

const char* ssid = "Tenda_1A5A60";
const char* password = "balaur20";

WiFiServer server(80);

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  server.begin();
  Serial.println("Server started");
  
  if (MDNS.begin("robot")) { // Set the mDNS name to "robotic-arm"
    Serial.println("mDNS responder started");
  }
}

void loop() {
  WiFiClient client = server.available();
  MDNS.update(); // Update the mDNS service

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // HTML page with buttons to control the robotic arm
    if (request.indexOf("GET /") != -1) {
      client.print(
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!DOCTYPE html><html lang=\"en\"><head>"
        "<meta name=\"viewport\" content=\"width=device-width,"
        "initial-scale=1, shrink-to-fit=no\">"
        "<meta charset=\"utf-8\"><title>Mini Robotic Arm</title>"
        "<style>body {display: flex; justify-content: center;"
        "align-items: center; height: 100vh; margin: 0;"
        "flex-direction: column; background-color: #f1f1f1;}"
        "h1 {text-align: center; margin-bottom: 20px;}"
        ".ctrl-pnl {display: flex; justify-content: center; align-items: center;}"
        ".ctrl-btn {width: 100px; height: 100px;"
        "border-radius: 50%; margin: 10px; background-color: #06D001;"
        "color: black; font-weight: bold; border: none;"
        "justify-content: center; align-items: center; cursor: pointer;"
        "transition: background-color 0.1s;}"
        ".ctrl-btn:hover {background-color: #059212;}"
        ".ctrl-btn:active {background-color: #9BEC00;}</style>"
        "</head><body><h1>Robotic Arm Control</h1>"
        "<div class=\"ctrl-pnl\"><table>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('rotate_left_on')\" "
        "onmouseup=\"sendCommand('rotate_left_off')\">"
        "Rotate Left</button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('rotate_right_on')\" "
        "onmouseup=\"sendCommand('rotate_right_off')\">"
        "Rotate Right</button></td></tr>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('shoulder_fwd_on')\" "
        "onmouseup=\"sendCommand('shoulder_fwd_off')\">"
        "Shoulder Fwd</button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('shoulder_bkd_on')\" "
        "onmouseup=\"sendCommand('shoulder_bkd_off')\">"
        "Shoulder Bkd</button></td></tr>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('elbow_up_on')\" "
        "onmouseup=\"sendCommand('elbow_up_off')\">"
        "Elbow Up</button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('elbow_down_on')\" "
        "onmouseup=\"sendCommand('elbow_down_off')\">"
        "Elbow Down</button></td></tr>"
        "<tr><td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('open_claw_on')\" "
        "onmouseup=\"sendCommand('open_claw_off')\">"
        "Open Claw</button></td>"
        "<td><button class=\"ctrl-btn\""
        "onmousedown=\"sendCommand('close_claw_on')\" "
        "onmouseup=\"sendCommand('close_claw_off')\">"
        "Close Claw</button></td></tr>"
        "</table></div>"
        "<script>"
        "function sendCommand(action) {"
        "var xhr = new XMLHttpRequest();"
        "xhr.open('GET', '/' + action, true);"
        "xhr.send();"
        "}"
        "</script></body></html>"
      );
    }

    // While the robotic arm isn't assembled, test the code with LEDs
    if (request.indexOf("/rotate_left_on") != -1) {
      digitalWrite(GREEN_LED, HIGH); // Turn LED ON while pressed
    }
    if (request.indexOf("/rotate_left_off") != -1) {
      digitalWrite(GREEN_LED, LOW); // Turn LED OFF when released
    }
    
    if (request.indexOf("/rotate_right_on") != -1) {
      digitalWrite(GREEN_LED, HIGH);
    }
    if (request.indexOf("/rotate_right_off") != -1) {
      digitalWrite(GREEN_LED, LOW);
    }

    if (request.indexOf("/shoulder_fwd_on") != -1) {
      digitalWrite(RED_LED, HIGH);
    }
    if (request.indexOf("/shoulder_fwd_off") != -1) {
      digitalWrite(RED_LED, LOW);
    }

    if (request.indexOf("/shoulder_bkd_on") != -1) {
      digitalWrite(RED_LED, HIGH);
    }
    if (request.indexOf("/shoulder_bkd_off") != -1) {
      digitalWrite(RED_LED, LOW);
    }

    if (request.indexOf("/elbow_up_on") != -1) {
      digitalWrite(BLUE_LED, HIGH);
    }
    if (request.indexOf("/elbow_up_off") != -1) {
      digitalWrite(BLUE_LED, LOW);
    }

    if (request.indexOf("/elbow_down_on") != -1) {
      digitalWrite(BLUE_LED, HIGH);
    }
    if (request.indexOf("/elbow_down_off") != -1) {
      digitalWrite(BLUE_LED, LOW);
    }

    if (request.indexOf("/open_claw_on") != -1) {
      digitalWrite(YELLOW_LED, HIGH);
    }
    if (request.indexOf("/open_claw_off") != -1) {
      digitalWrite(YELLOW_LED, LOW);
    }

    if (request.indexOf("/close_claw_on") != -1) {
      digitalWrite(YELLOW_LED, HIGH);
    }
    if (request.indexOf("/close_claw_off") != -1) {
      digitalWrite(YELLOW_LED, LOW);
    }
  }
}
