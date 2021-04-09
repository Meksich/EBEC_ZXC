/* WifiCtl.h - library for remote control over HTTP using esp32 wifi capabilities
 * 
 */

#ifndef WIFICTL_H_
#define WIFICTL_H_

#include <WiFi.h>

class WifiCtl {
 public:
  WifiCtl();
  void begin(int server_port, int test_pin);
  void checkClient();

 private:
  void formResponse(WiFiClient client, bool ok);

 private:
  WiFiServer server_;
  int port_;
  int pin_;
};

WifiCtl::WifiCtl() {}

void WifiCtl::begin(int server_port, int test_pin) {
  this->port_ = server_port;
  this->pin_ = test_pin; 

  pinMode(this->pin_, OUTPUT);
  digitalWrite(this->pin_, LOW);

  this->server_ = WiFiServer(server_port);
  this->server_.begin(this->port_);

  Serial.println("[WifiCtl] Server address: ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(this->port_);
}

void WifiCtl::checkClient() {
  WiFiClient client = this->server_.available();
  if (client) {
    Serial.println("[WifiCtl] Client has connected.");
    String current_line = "";
    String header = "";
    bool request_ok = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // DEBUG
        header += c;
        if (c == '\n') {
          if (current_line.length() == 0) {
            if (header.indexOf("GET /pin") >= 0) {
              // Pin
              digitalWrite(this->pin_, HIGH);
              delay(200);
              digitalWrite(this->pin_, LOW);
              
              request_ok = true;
            } else {
              request_ok = false;
            }
            
            this->formResponse(client, request_ok);
            break;
          } else {
            current_line = "";
          }
        } else if (c != '\r') {
          current_line += c;
        }
      }
    }
    client.stop();
    Serial.println("[WifiCtl] Client has disconnected.");
  }
}

void WifiCtl::formResponse(WiFiClient client, bool ok) {
  if (ok) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE html><html>");
    client.println("<body><h1>OK</h1></body>");
    client.println("</html>");
    client.println();
  } else {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE html><html>");
    client.println("<body><h1>404 Not Found</h1><p>No such uri on the server.</p></body>");
    client.println("</html>");
    client.println();
  }
}

#endif
