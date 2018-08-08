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
const char *ap_ssid = "Led_control";
ESP8266WebServer server(80);

//! Локальные Макроопределения

//! Локальные функции
void handle_main() 
{
  server.send(200, "text/html", "<h1>You are connected</h1>");
}



//! Глобальные функции
void init_server()
{
  INFO("Старт настройки сервера");
  WiFi.softAP(ap_ssid);

  INFO("AP IP address: ");
  INFO(WiFi.softAPIP());
  server.on("/", handle_main);
  server.begin();
  INFO("HTTP сервер запущен");
}
 
void check_clinets()
{
  server.handleClient();
}

