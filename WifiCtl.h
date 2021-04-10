/* WifiCtl.h - library for remote control over HTTP using esp32 wifi capabilities
 * 
 */

#ifndef WIFICTL_H_
#define WIFICTL_H_

#define CTL_MOVE_FWD    0x01
#define CTL_MOVE_LEFT   0x02
#define CTL_MOVE_RIGHT  0x03

#include <WiFi.h>
#include <analogWrite.h>

class WifiCtl {
 public:
  WifiCtl();
  void begin(int server_port, int test_pin);
  void checkClient();

 private:
  void formResponse(WiFiClient client, bool ok);
  void writePin(int value);

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
            if (header.indexOf("GET /") >= 0) {
                client.println("HTTP/1.1 200 OK"
                   "Content-type:text/html"
                   "Connection: close"
                   ""
                   "<!DOCTYPE html><html>"
                   "<body>"
                   "<iframe src=\"localhost:80/\" width=\"800px\" height=\"800px\">"
                   "<script>"
                   "function sendRequest(uri) {"
                   "  var xmlHttp = new XMLHttpRequest();"
                   "  xmlHttp.open(\"GET\", uri, true);"
                   "  xmlHttp.send(null);"
                   "}"
                   "document.addEventListener(\"keydown\", (e) => {"
                   "  if (e.code == \"ArrowUp\") {"
                   "    sendRequest(\"/move_forward\");"
                   "  } else if (e.code == \"ArrowLeft\") {"
                   "    sendRequest(\"/move_left\");"
                   "  } else if (e.code == \"ArrowRight\") {"
                   "    sendRequest(\"/move_right\");"
                   "  } else if (e.code == \"ArrowDown\") {"
                   "    sendRequest(\"/move_forward\");"
                   "  }"
                   "});"
                   "</script>"
                   "</body>"
                   "</html>");
              break;
            } else if (header.indexOf("GET /move_forward") >= 0) {
              Serial.println("[WifiCtl] /move_forward"); // DEBUG
              this->writePin(CTL_MOVE_FWD);              
              request_ok = true;
            } else if (header.indexOf("GET /move_left") >= 0) {
              Serial.println("[WifiCtl] /move_forward"); // DEBUG
              this->writePin(CTL_MOVE_LEFT);
              request_ok = true;
            } else if (header.indexOf("GET /move_right") >= 0) {
              Serial.println("[WifiCtl] /move_right"); // DEBUG
              this->writePin(CTL_MOVE_RIGHT);
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
    client.println("HTTP/1.1 200 OK"
                   "Content-type:text/html"
                   "Connection: close"
                   ""
                   "<!DOCTYPE html><html>"
                   "<body><h1>OK</h1></body>"
                   "</html>");
  } else {
    client.println("HTTP/1.1 404 Not Found"
                   "Content-type:text/html"
                   "Connection: close"
                   ""
                   "<!DOCTYPE html><html>"
                   "<body><h1>404 Not Found</h1><p>No such uri on the server.</p></body>"
                   "</html>");
  }
}

void WifiCtl::writePin(int value) {
  analogWrite(this->pin_, value);
}

#endif
