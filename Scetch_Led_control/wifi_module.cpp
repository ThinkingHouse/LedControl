/*!
 *  \file      wifi_module.cpp
 *
 *  \brief     Реализация функций для настройки wifi
 *
 *  \detailed   
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru>
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */

//! Подключение заголовочных файлов
#include "wifi_module.h"

//! Локальные данные
const char *ap_ssid = "ASUS_Home";
const char *ap_password = "1300703DronVip";
//! Локальные Макроопределения

//! Локальные функции


//! Глобальные функции
void init_wifi()
{
  if (IS_AP_MODE)
  {
    WiFi.softAP(ap_ssid);
    INFO("AP IP address: ");
    INFO(WiFi.softAPIP());
  }
  else
  {
    INFO("Connecting to ");
    INFO(String(ap_ssid));
  
    WiFi.begin(ap_ssid, ap_password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    INFO("WiFi connected");
    INFO(WiFi.localIP());
  }
}
 
