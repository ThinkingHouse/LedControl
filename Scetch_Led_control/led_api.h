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
#include <EEPROM.h>

//! Глобальные данные

//! Макроопределения
#define LED_IN_PIN_1    D1
#define LED_IN_PIN_2    D2
#define LED_IN_PIN_3    D3
#define LED_IN_PIN_4    D4

#define LED_1_NUMBER_PIXELS      16
#define LED_2_NUMBER_PIXELS      16
#define LED_3_NUMBER_PIXELS      16
#define LED_4_NUMBER_PIXELS      16

#define LED_1_ADDRESS_START    0
#define LED_2_ADDRESS_START    96
#define LED_3_ADDRESS_START    192
#define LED_4_ADDRESS_START    288

//! Типы
typedef enum
{
  LED_1,
  LED_2,
  LED_3,
  LED_4
}led_id_t;

//! Глобальные функции
/*!
 *  \brief         Инициализация светодиодных лент
 *  
 */
void init_leds(void);

/*!
 *  \brief         Задать цвет светодода на ленте 
 *  
 */
void set_leds_colors(led_id_t led_id, int8_t red, int8_t green, int8_t blue);

void set_brightness(led_id_t led_id, int8_t value);

/*!
 *  \brief         Обновить цвет светодода на ленте 
 *  
 */
void update_leds_colors(led_id_t led_id);

#endif
