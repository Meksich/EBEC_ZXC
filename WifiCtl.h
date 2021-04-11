/* WifiCtl.h - library for remote control over HTTP using esp32's wifi capabilities
 * Created by maxrt, 10/04/2021
 *
 * For server debugging, define _ESP32_DEBUG_SERIAL
 * For requests debugging, define _ESP32_DEBUG_SERIAL_PRINT_REQUEST
 */

#ifndef WIFICTL_H_
#define WIFICTL_H_

#include <WiFi.h>
#include "HtmlContent.h"

#define CTL_SERIAL_SPEED  9600
#define CTL_SERIAL_TX     TX
#define CTL_SERIAL_RX     RX

class WifiCtl {
 public:
  WifiCtl();
  void begin(int port);
  void checkClient();

 private:
  void sendResponse(WiFiClient client, int code, String body);
  void send200(WiFiClient client, String response);
  void send404(WiFiClient client);

 private:
  WiFiServer server_;
  int port_;
};


WifiCtl::WifiCtl() {}

void WifiCtl::begin(int port) {
  this->port_ = port;

#ifndef _ESP32_DEBUG_SERIAL
  Serial2.begin(CTL_SERIAL_SPEED, SERIAL_8N1, CTL_SERIAL_RX, CTL_SERIAL_TX);
#endif

  this->server_ = WiFiServer(this->port_);
  this->server_.begin(this->port_);

#ifdef _ESP32_DEBUG_SERIAL
  Serial.print("[WifiCtl] Server address: ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(this->port_);
#endif
}

void WifiCtl::checkClient() {
  WiFiClient client = this->server_.available();
  if (client) {
#ifdef _ESP32_DEBUG_SERIAL
    Serial.println("[WifiCtl] Client has connected.");
#endif
    String current_line = "";
    String header = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
#ifdef _ESP32_DEBUG_SERIAL_PRINT_REQUEST
        Serial.write(c); // DEBUG
#endif
        header += c;
        if (c == '\n') {
          if (current_line.length() == 0) {
            if (header.indexOf("GET / ") >= 0) {
              this->send200(client, HTML_INDEX);
            } else if (header.indexOf("GET /move/fwd") >= 0) {
              Serial2.write('f');
            } else if (header.indexOf("GET /move/back") >= 0) {
              Serial2.write('b');
            } else if (header.indexOf("GET /move/left") >= 0) {
              Serial2.write('l');
            } else if (header.indexOf("GET /move/right") >= 0) {
              Serial2.write('r');
            } else if (header.indexOf("GET /crane/w") >= 0) {
              Serial2.write('w');
            } else if (header.indexOf("GET /crane/s") >= 0) {
              Serial2.write('s');
            } else if (header.indexOf("GET /crane/a") >= 0) {
              Serial2.write('a');
            } else if (header.indexOf("GET /crane/d") >= 0) {
              Serial2.write('d');
            } else if (header.indexOf("GET /crane/space") >= 0) {
              Serial2.write(' ');
            } else if (header.indexOf("GET /mission") >= 0) {
              Serial2.write('m');
            } else {
              this->send404(client);
            }
#ifdef _ESP32_DEBUG_SERIAL
            Serial.println("[WifiCtl] " + header); // DEBUG
#endif
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
#ifdef _ESP32_DEBUG_SERIAL
    Serial.println("[WifiCtl] Client has disconnected.");
#endif
  }
}

void WifiCtl::sendResponse(WiFiClient client, int code, String body) {
  String http_response = "HTTP/1.1 ";
  if (code == 200) {
    http_response += "200 OK\r\n";
  } else if (code == 404) {
    http_response += "404 Not Found\r\n";
  } else {
    http_response += "500 Internal Server Error\r\n";
  }

  http_response += "Connection: close\r\n";
  http_response += "Content-Type: text/html\r\n";
  http_response += "Content-Length: " + String(body.length());
  http_response += "\r\n\r\n" + body;

  client.println(http_response);
}

void WifiCtl::send200(WiFiClient client, String response) {
  this->sendResponse(client, 200, response);
}

void WifiCtl::send404(WiFiClient client) {
  this->sendResponse(client, 404, HTML_404);
}


#endif
