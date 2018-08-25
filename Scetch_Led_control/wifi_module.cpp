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
const char *ap_ssid = "LedControl";
String st_ssid;
String st_password;

bool is_at_mode = true;
bool is_st_mode = false;

//! Локальные Макроопределения
#define WIFI_SSID              400
#define WIFI_PASSWORD          450

//! Локальные функции
void get_wifi_from_eeprom()
{
  EEPROM.begin(EEPROM_SIZE);
  INFO("Get SSID from eeprom");
  for(int i = 0; i < 32; i++)
  {
    if (EEPROM.read(WIFI_SSID + i) == 255)
    {
      st_ssid += "";
      if (i < 5)
      {
        is_st_mode = false;
        is_at_mode = true;
      }
      else
      {
        is_st_mode = true;
        is_at_mode = false;
      }
      break;
    }
    st_ssid += String(EEPROM.read(WIFI_SSID + i));
  }
  INFO(st_ssid);

  INFO("Get Password from eeprom");
  for(int i = 0; i < 32; i++)
  {
    if (EEPROM.read(WIFI_PASSWORD + i) == 255)
    {
      st_password += "";
      break;
    }
    st_password += EEPROM.read(WIFI_PASSWORD + i);
  }
  INFO(String(st_password));
  if (st_ssid.length() < 5 && st_password.length() < 5)
  {
    is_st_mode = false;
    is_at_mode = true;
  }
  else
  {
    is_st_mode = true;
    is_at_mode = false;
  }
  
  EEPROM.end();
}

//! Глобальные функции
void init_wifi()
{
  get_wifi_from_eeprom();
  INFO("WiFi Init");
  if (is_at_mode)
  {
    INFO("AP INIT");
    WiFi.softAP(ap_ssid);
    INFO("AP IP address: ");
    INFO(WiFi.softAPIP());
  }
  if (is_st_mode)
  {
    INFO("Connecting to ");
    INFO(String(ap_ssid));
  
    WiFi.begin(st_ssid.c_str(), st_password.c_str());
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    INFO("WiFi connected");
    INFO(WiFi.localIP());
  }
}

void set_wifi_data(String ssid, String password)
{
  int i = 0;
  EEPROM.begin(EEPROM_SIZE);
  INFO("Set SSID from eeprom");
  INFO(ssid);
  INFO(password);
  for(i = 0; i < 32; i++)
  {
    st_ssid = ssid;
    EEPROM.write(WIFI_SSID + i, ssid.c_str()[i]);
  }
  INFO(String(st_ssid));

  INFO("Set Password from eeprom");
  for(i = 0; i < 32; i++)
  {
    st_password = password;
    EEPROM.write(WIFI_PASSWORD + i, ssid.c_str()[i]);
  }
  INFO(String(st_password));
  EEPROM.end();
}

