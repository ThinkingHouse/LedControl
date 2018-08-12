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

String main_page = "<!DOCTYPE html>" \
                   "<html>" \
                   "<head>"
                   "  <meta charset=\"utf-8\">" \
                   "  <title>Цвет</title>" \
                   "</head>" \
                   "<body>" \   
                   "  <form action=\"set_color_1\">" \
                   "    <p>Укажите цвет ленты 1: <input type=\"color\" name=\"color\" value=\"#ff0000\">" \
                   "    <input type=\"submit\" value=\"Выбрать\"></p>" \ 
                   "   </form>" \ 
                   "</body>" \ 
                   " </html>";

//! Локальные Макроопределения

//! Локальные функции
void handle_main() 
{
  server.send(200, "text/html", main_page);
}

void handle_set_color()
{
  INFO("Получен запрос от клиента");
  INFO(server.uri());
  String color_str = server.arg("color");
  const char *hexstring = color_str.substring(1).c_str();
  int number = (int)strtol(hexstring, NULL, 16);
  INFO("Получен цвет клиента");
  INFO(String(number));
  server.send(200, "text/html", main_page);
}


//! Глобальные функции
void init_server()
{
  INFO("Старт настройки сервера");
  WiFi.softAP(ap_ssid);

  INFO("AP IP address: ");
  INFO(WiFi.softAPIP());
  server.on("/", handle_main);
  server.on("/set_color_1", handle_set_color);
  server.begin();
  INFO("HTTP сервер запущен");
}
 
void check_clinets()
{
  server.handleClient();
}

