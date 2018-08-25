/*!
 *  \file      common.h
 *
 *  \brief     Базовые функции
 *
 *  \detailed  
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru>
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */
#ifndef _COMMON_H_
#define _COMMON_H_

//! Подключение заголовочных файлов
#include "Arduino.h"
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

//! Типы
typedef enum
{
  INFO,
  DEBUG,
  TRACE
}log_levels_t;

//! Макроопределения
#define HTTP_SERVER_PORT    80
#define EEPROM_SIZE         512

#define INFO(a)     print_log(a, INFO);
#define DEBUG(a)    print_log(a, DEBUG);
#define TRACE(a)    print_log(a, TRACE);

//! Глобальные функции
/*!
 *  \brief         Инициализация дебага
 *  
 */
void init_debug(void);

void print_log(String text, log_levels_t level);
void print_log(IPAddress text, log_levels_t level);
void set_main_delay(String delay_s);
int16_t get_main_delay(void);
#endif
