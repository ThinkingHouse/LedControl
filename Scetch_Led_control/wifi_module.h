/*!
 *  \file      wifi_module.h
 *
 *  \brief     Модуль для конфигурирования wifi
 *
 *  \detailed   
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru>
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */
#ifndef _WIFI_MODULE_H_
#define _WIFI_MODULE_H_

//! Подключение заголовочных файлов
#include "common.h"
#include <EEPROM.h>

//! Глобальные данные

//! Макроопределения

//! Типы

//! Глобальные данные

//! Глобальные функции
void init_wifi(void);

void set_wifi_data(String ssid, String password);

#endif
