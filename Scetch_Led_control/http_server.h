/*!
 *  \file      http_server.h
 *
 *  \brief     Функции http сервера
 *
 *  \detailed   
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */
 
#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_
//! Подключение заголовочных файлов
#include "common.h"

//! Глобальные данные

//! Макроопределения

//! Типы

//! Глобальные функции
/*!
 *  \brief         Инициализация сервера
 *  
 */
 void init_server(void);
 
/*!
 *  \brief         Проверка запросов
 *  
 */
void check_clinets(void);

#endif
