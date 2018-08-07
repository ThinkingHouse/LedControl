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

//! Макроопределения
#define HTTP_SERVER_PORT    80

//! Глобальные функции
void print_log(String text);
#endif
