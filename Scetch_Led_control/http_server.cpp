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
                   "    <p>Укажите цвет ленты 1: <input type=\"color\" name=\"color\" value=\"#ff0000\"> Интенсивность: <input type=\"text\" name=\"brightness\" value=\"255\">" \
                   "    <input type=\"submit\" value=\"Выбрать\"></p>" \ 
                   "   </form>" \ 
                   "  <form action=\"set_color_2\">" \
                   "    <p>Укажите цвет ленты 2: <input type=\"color\" name=\"color\" value=\"#ff0000\"> Интенсивность: <input type=\"text\" name=\"brightness\" value=\"255\">" \
                   "    <input type=\"submit\" value=\"Выбрать\"></p>" \ 
                   "   </form>" \
                    "  <form action=\"set_color_3\">" \
                   "    <p>Укажите цвет ленты 3: <input type=\"color\" name=\"color\" value=\"#ff0000\"> Интенсивность: <input type=\"text\" name=\"brightness\" value=\"255\">" \
                   "    <input type=\"submit\" value=\"Выбрать\"></p>" \ 
                   "   </form>" \
                   "  <form action=\"set_color_4\">" \
                   "    <p>Укажите цвет ленты 4: <input type=\"color\" name=\"color\" value=\"#ff0000\"> Интенсивность: <input type=\"text\" name=\"brightness\" value=\"255\"> Программа: <input type=\"text\" name=\"programm\" value=\"0\">" \
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

void handle_set_color_1()
{
  INFO("Получен запрос от клиента");
  INFO(server.uri());
  String color_str = server.arg("color");
  String col = "0x" + String(color_str.c_str()[1]) + String(color_str.c_str()[2]);
  int red = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[3]) + String(color_str.c_str()[4]);
  int green = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[5]) + String(color_str.c_str()[6]);
  int blue = strtol(col.c_str(),NULL,0);
  INFO("Получен цвет");
  INFO(col);
  INFO(String(red) + String(" ") + String(green) + String(" ") + String(blue));
  set_leds_colors(LED_1, red, green, blue);
  set_brightness(LED_1, server.arg("brightness").toInt());
  update_leds_colors(LED_1);
  server.send(200, "text/html", main_page);
}

void handle_set_color_2()
{
  INFO("Получен запрос от клиента");
  INFO(server.uri());
  String color_str = server.arg("color");
  String col = "0x" + String(color_str.c_str()[1]) + String(color_str.c_str()[2]);
  int red = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[3]) + String(color_str.c_str()[4]);
  int green = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[5]) + String(color_str.c_str()[6]);
  int blue = strtol(col.c_str(),NULL,0);
  INFO("Получен цвет");
  INFO(col);
  INFO(String(red) + String(" ") + String(green) + String(" ") + String(blue));
  set_leds_colors(LED_2, red, green, blue);
  set_brightness(LED_2, server.arg("brightness").toInt());
  update_leds_colors(LED_2);
  server.send(200, "text/html", main_page);
}

void handle_set_color_3()
{
  INFO("Получен запрос от клиента");
  INFO(server.uri());
  String color_str = server.arg("color");
  String col = "0x" + String(color_str.c_str()[1]) + String(color_str.c_str()[2]);
  int red = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[3]) + String(color_str.c_str()[4]);
  int green = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[5]) + String(color_str.c_str()[6]);
  int blue = strtol(col.c_str(),NULL,0);
  INFO("Получен цвет");
  INFO(col);
  INFO(String(red) + String(" ") + String(green) + String(" ") + String(blue));
  set_leds_colors(LED_3, red, green, blue);
  set_brightness(LED_3, server.arg("brightness").toInt());
  update_leds_colors(LED_3);
  server.send(200, "text/html", main_page);
}

void handle_set_color_4()
{
  INFO("Получен запрос от клиента");
  INFO(server.uri());
  String color_str = server.arg("color");
  String col = "0x" + String(color_str.c_str()[1]) + String(color_str.c_str()[2]);
  int red = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[3]) + String(color_str.c_str()[4]);
  int green = strtol(col.c_str(),NULL,0);
  col = "0x" + String(color_str.c_str()[5]) + String(color_str.c_str()[6]);
  int blue = strtol(col.c_str(),NULL,0);
  INFO("Получен цвет");
  INFO(col);
  INFO(String(red) + String(" ") + String(green) + String(" ") + String(blue));
  set_leds_colors(LED_4, red, green, blue);
  set_brightness(LED_4, server.arg("brightness").toInt());
  set_programm(server.arg("programm").toInt());
  update_leds_colors(LED_4);
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
  server.on("/set_color_1", handle_set_color_1);
  server.on("/set_color_2", handle_set_color_2);
  server.on("/set_color_3", handle_set_color_3);
  server.on("/set_color_4", handle_set_color_4);
  server.begin();
  INFO("HTTP сервер запущен");
}
 
void check_clinets()
{
  server.handleClient();
}

