/*!
 *  \file      http_server.cpp
 *
 *  \brief     Реализация функций http сервера
 *
 *  \detailed   
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */

//! Подключение заголовочных файлов
#include "http_server.h"

//! Локальные данные
const char *ssid = "ESPap";
const char *password = "thereisnospoon";
ESP8266WebServer server(80);

//! Локальные Макроопределения

//! Локальные функции
void handleRoot() 
{
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

//! Глобальные функции
/*!
 *  \brief         Инициализация сервера
 *  
 */
void init_server()
{
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}
 
/*!
 *  \brief         Проверка запросов
 *  
 */
void check_clinets()
{
  server.handleClient();
}

