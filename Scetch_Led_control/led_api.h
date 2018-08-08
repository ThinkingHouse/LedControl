/*!
 *  \file      led_api.h
 *
 *  \brief     Функции Управления светодиодными лентами
 *
 *  \detailed   
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru>
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */
 
#ifndef _LED_API_H_
#define _LED_API_H_
//! Подключение заголовочных файлов
#include "common.h"
#include <Adafruit_NeoPixel.h>

//! Глобальные данные

//! Макроопределения
#define LED_IN_PIN_1    D0
#define LED_IN_PIN_2    D1
#define LED_IN_PIN_3    D3
#define LED_IN_PIN_4    D4

#define LED_1_NUMBER_PIXELS      16
#define LED_2_NUMBER_PIXELS      16
#define LED_3_NUMBER_PIXELS      16
#define LED_4_NUMBER_PIXELS      16

//! Типы

//! Глобальные функции
/*!
 *  \brief         Инициализация светодиодных лент
 *  
 */
void init_leds(void);

#endif
