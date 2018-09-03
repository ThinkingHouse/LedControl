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
#ifdef ESP8266
extern "C" {
#include "user_interface.h"
}
#endif
//! Локальные данные
const char *ap_ssid = "LedControl";
String st_ssid;
String st_password;

bool is_at_mode = true;
bool is_st_mode = false;

//! Локальные Макроопределения
#define PIN_INDICATION     D4
#define WIFI_SSID              400
#define WIFI_PASSWORD          450

//! Локальные функции
void get_wifi_from_eeprom()
{
  EEPROM.begin(EEPROM_SIZE);
  st_ssid = "";
  st_password = "";
  INFO("Get SSID from eeprom");
  for(int i = 0; i < 32; i++)
  {
    if (EEPROM.read(WIFI_SSID + i) == 255)
    {
      //st_ssid += "";
      break;
    }
    else
    {
      st_ssid += String((char)EEPROM.read(WIFI_SSID + i));
      INFO(EEPROM.read(WIFI_SSID + i));
    }
  }
  INFO(st_ssid);

  INFO("Get Password from eeprom");
  for(int i = 0; i < 32; i++)
  {
    if (EEPROM.read(WIFI_PASSWORD + i) == 255)
    {
      //st_password += "";
      break;
    }
    st_password += String((char)EEPROM.read(WIFI_PASSWORD + i));
  }
  INFO(String(st_password));
  if (st_ssid.length() == 0 || st_password.length() == 0)
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

void wifi_event_handler_cb(System_Event_t * event)
{
  EEPROM.begin(EEPROM_SIZE);   
    switch (event->event)
    {
        case EVENT_STAMODE_CONNECTED:
            break;
        case EVENT_STAMODE_DISCONNECTED:
          INFO("WiFi is lost");
          for(int i = 0; i < 32; i++)
          {
            EEPROM.write(WIFI_SSID + i, 255);
          }
          ESP.deepSleep(1000, WAKE_RF_DEFAULT);
            break;
        case EVENT_STAMODE_AUTHMODE_CHANGE:
            break;
        case EVENT_STAMODE_GOT_IP:
            break;
        case EVENT_SOFTAPMODE_STACONNECTED:
        case EVENT_SOFTAPMODE_STADISCONNECTED:
            break;
    }
    EEPROM.end();
}

bool check_wifi()
{
  bool result = false;
  INFO("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  INFO("scan done");
  if (n == 0)
  {
    INFO("no networks found");
    result = true;
  }
  else
  {
    INFO(String(n) + String(" networks found"));
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
      if (String(WiFi.SSID(i)).equals(st_ssid))
      {
        result = true;
        INFO("WiFi Точка найдена");
        return result;
      }
    }
    INFO("WiFi Точка не найдена");
    for(int i = 0; i < 32; i++)
    {
      EEPROM.write(WIFI_SSID + i, 255);
    }
    for(int i = 0; i < 32; i++)
    {
      EEPROM.write(WIFI_PASSWORD + i, 255);
    }
    ESP.deepSleep(1000, WAKE_RF_DEFAULT);
  }
  return result;
}

//! Глобальные функции
void init_wifi()
{
  bool is_wifi = false; 
  int exit_wifi_connect = 0;
  bool led_indicator_status = false;
  pinMode(PIN_INDICATION, OUTPUT);
  get_wifi_from_eeprom();

  if (is_st_mode)
    is_wifi = check_wifi();
  INFO("WiFi Init");
  if (is_at_mode && !is_wifi)
  {
    INFO("AP INIT");
    WiFi.softAP(ap_ssid);
    INFO("AP IP address: ");
    INFO(WiFi.softAPIP());
  }
  if (is_st_mode && is_wifi)
  {
    INFO("Connecting to ");
    INFO(String(st_ssid));
  
    WiFi.begin(st_ssid.c_str(), st_password.c_str());
    while (WiFi.status() != WL_CONNECTED && exit_wifi_connect < 60) 
    {
      delay(500);
      Serial.print(".");
      digitalWrite(PIN_INDICATION, led_indicator_status);
      led_indicator_status = !led_indicator_status;
      exit_wifi_connect++;
    }
    Serial.println("");
    digitalWrite(PIN_INDICATION, HIGH);
    INFO("WiFi connected");
    wifi_set_event_handler_cb(wifi_event_handler_cb);
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
    if ( i < ssid.length())
      EEPROM.write(WIFI_SSID + i, ssid.c_str()[i]);
    else
      EEPROM.write(WIFI_SSID + i, 255);
  }
  INFO(String(st_ssid));

  INFO("Set Password from eeprom");
  for(i = 0; i < 32; i++)
  {
    st_password = password;
    if ( i < st_password.length())
      EEPROM.write(WIFI_PASSWORD + i, st_password.c_str()[i]);
    else
      EEPROM.write(WIFI_PASSWORD + i, 255);
  }
  INFO(String(st_password));
  EEPROM.end();
}

