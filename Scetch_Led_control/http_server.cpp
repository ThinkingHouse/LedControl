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
  //char* temp_ssid;
  //sprintf(temp_ssid, "%s%d", "LedControl_", ESP.getChipId());
  //ssid = (const char*) temp_ssid;
  WiFi.softAP(ap_ssid);

  INFO("AP IP address: ");
  INFO(WiFi.softAPIP());
  server.on("/", handleRoot);
  server.begin();
  INFO("HTTP server started");
}
 
/*!
 *  \brief         Проверка запросов
 *  
 */
void check_clinets()
{
  server.handleClient();
}

