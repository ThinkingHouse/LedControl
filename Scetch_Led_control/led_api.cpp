/*!
 *  \file      led_api.cpp
 *
 *  \brief     Реализация функций светодиодных лент
 *
 *  \detailed   
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru>
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */

//! Подключение заголовочных файлов
#include "led_api.h"

//! Локальные данные
Adafruit_NeoPixel led_pixels_1 = Adafruit_NeoPixel(LED_1_NUMBER_PIXELS, LED_IN_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_pixels_2 = Adafruit_NeoPixel(LED_2_NUMBER_PIXELS, LED_IN_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_pixels_3 = Adafruit_NeoPixel(LED_3_NUMBER_PIXELS, LED_IN_PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_pixels_4 = Adafruit_NeoPixel(LED_4_NUMBER_PIXELS, LED_IN_PIN_4, NEO_GRB + NEO_KHZ800);

int8_t led_1_colors[LED_1_NUMBER_PIXELS][3];
int8_t led_2_colors[LED_2_NUMBER_PIXELS][3];
int8_t led_3_colors[LED_3_NUMBER_PIXELS][3];
int8_t led_4_colors[LED_4_NUMBER_PIXELS][3];

//! Локальные Макроопределения

//! Локальные функции

//! Глобальные функции
void init_leds()
{
  led_pixels_1.begin();
  led_pixels_2.begin();
  led_pixels_3.begin();
  led_pixels_4.begin();
  INFO("Инициализация светодиодных лент завершена");
}

void set_leds_colors(led_id_t led_id, int8_t red, int8_t green, int8_t blue)
{
  
}


