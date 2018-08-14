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
int8_t led_1_brightness = 255;
int8_t led_2_brightness = 255;
int8_t led_3_brightness = 255;
int8_t led_4_brightness = 255;

//! Локальные Макроопределения
#define RED_COLOR    0
#define GREEN_COLOR  1
#define BLUE_COLOR   2
//! Локальные функции

//! Глобальные функции
void init_leds()
{
  int address_cursor = 0;
  
  EEPROM.begin(512);
  led_pixels_1.begin();
  led_pixels_2.begin();
  led_pixels_3.begin();
  led_pixels_4.begin();
  for (int i = 0; i < LED_1_NUMBER_PIXELS; i++)
  {
    led_1_colors[i][RED_COLOR] = EEPROM.read(LED_1_ADDRESS_START + address_cursor);
    address_cursor++;
    led_1_colors[i][GREEN_COLOR] = EEPROM.read(LED_1_ADDRESS_START + address_cursor);
    address_cursor++;
    led_1_colors[i][BLUE_COLOR] = EEPROM.read(LED_1_ADDRESS_START + address_cursor);
    address_cursor++;
  }
  address_cursor = 0;
  for (int i = 0; i < LED_2_NUMBER_PIXELS; i++)
  {
    led_2_colors[i][RED_COLOR] = EEPROM.read(LED_2_ADDRESS_START + address_cursor);
    address_cursor++;
    led_2_colors[i][GREEN_COLOR] = EEPROM.read(LED_2_ADDRESS_START + address_cursor);
    address_cursor++;
    led_2_colors[i][BLUE_COLOR] = EEPROM.read(LED_2_ADDRESS_START + address_cursor);
    address_cursor++;
  }
  address_cursor = 0;
  for (int i = 0; i < LED_3_NUMBER_PIXELS; i++)
  {
    led_3_colors[i][RED_COLOR] = EEPROM.read(LED_3_ADDRESS_START + address_cursor);
    address_cursor++;
    led_3_colors[i][GREEN_COLOR] = EEPROM.read(LED_3_ADDRESS_START + address_cursor);
    address_cursor++;
    led_3_colors[i][BLUE_COLOR] = EEPROM.read(LED_3_ADDRESS_START + address_cursor);
    address_cursor++;
  }
  address_cursor = 0;
  for (int i = 0; i < LED_4_NUMBER_PIXELS; i++)
  {
    led_4_colors[i][RED_COLOR] = EEPROM.read(LED_4_ADDRESS_START + address_cursor);
    address_cursor++;
    led_4_colors[i][GREEN_COLOR] = EEPROM.read(LED_4_ADDRESS_START + address_cursor);
    address_cursor++;
    led_4_colors[i][BLUE_COLOR] = EEPROM.read(LED_4_ADDRESS_START + address_cursor);
    address_cursor++;
  }
  update_leds_colors(LED_1);
  update_leds_colors(LED_2);
  update_leds_colors(LED_3);
  update_leds_colors(LED_4);
  EEPROM.end();
  INFO("Инициализация светодиодных лент завершена");
}

void set_leds_colors(led_id_t led_id, int8_t red, int8_t green, int8_t blue)
{
  int address_cursor = 0;
  EEPROM.begin(512);
  switch(led_id)
  {
    case LED_1:
      for (int i = 0; i < LED_1_NUMBER_PIXELS; i++)
      {
        led_1_colors[i][RED_COLOR] = red;
        led_1_colors[i][GREEN_COLOR] = green;
        led_1_colors[i][BLUE_COLOR] = blue;
        EEPROM.write(LED_1_ADDRESS_START + address_cursor, red);
        address_cursor++;
        EEPROM.write(LED_1_ADDRESS_START + address_cursor, green);
        address_cursor++;
        EEPROM.write(LED_1_ADDRESS_START + address_cursor, blue);
        address_cursor++;
      }
      break;

    case LED_2:
      for (int i = 0; i < LED_2_NUMBER_PIXELS; i++)
      {
        led_2_colors[i][RED_COLOR] = red;
        led_2_colors[i][GREEN_COLOR] = green;
        led_2_colors[i][BLUE_COLOR] = blue;
        EEPROM.write(LED_2_ADDRESS_START + address_cursor, red);
        address_cursor++;
        EEPROM.write(LED_2_ADDRESS_START + address_cursor, green);
        address_cursor++;
        EEPROM.write(LED_2_ADDRESS_START + address_cursor, blue);
        address_cursor++;
      }
      break;

    case LED_3:
      for (int i = 0; i < LED_3_NUMBER_PIXELS; i++)
      {
        led_3_colors[i][RED_COLOR] = red;
        led_3_colors[i][GREEN_COLOR] = green;
        led_3_colors[i][BLUE_COLOR] = blue;
        EEPROM.write(LED_3_ADDRESS_START + address_cursor, red);
        address_cursor++;
        EEPROM.write(LED_3_ADDRESS_START + address_cursor, green);
        address_cursor++;
        EEPROM.write(LED_3_ADDRESS_START + address_cursor, blue);
        address_cursor++;
      }
      break;

    case LED_4:
      for (int i = 0; i < LED_4_NUMBER_PIXELS; i++)
      {
        led_4_colors[i][RED_COLOR] = red;
        led_4_colors[i][GREEN_COLOR] = green;
        led_4_colors[i][BLUE_COLOR] = blue;
        EEPROM.write(LED_4_ADDRESS_START + address_cursor, red);
        address_cursor++;
        EEPROM.write(LED_4_ADDRESS_START + address_cursor, green);
        address_cursor++;
        EEPROM.write(LED_4_ADDRESS_START + address_cursor, blue);
        address_cursor++;
      }
      break;
  }
  EEPROM.end();
}

void update_leds_colors(led_id_t led_id)
{
  switch(led_id)
  {
    case LED_1:
      for (int i = 0; i < LED_1_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №1 цвета: ") + String(led_1_colors[i][RED_COLOR]) + String(led_1_colors[i][GREEN_COLOR]) + String(led_1_colors[i][BLUE_COLOR]));
        led_pixels_1.setPixelColor(i, led_pixels_1.Color(led_1_colors[i][RED_COLOR], led_1_colors[i][GREEN_COLOR], led_1_colors[i][BLUE_COLOR]));
        led_pixels_1.show();
        delay(1);
      }
      break;

    case LED_2:
      for (int i = 0; i < LED_2_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №2 цвета: ") + String(led_2_colors[i][RED_COLOR]) + String(led_2_colors[i][GREEN_COLOR]) + String(led_2_colors[i][BLUE_COLOR]));
        led_pixels_2.setPixelColor(i, led_pixels_2.Color(led_2_colors[i][RED_COLOR], led_2_colors[i][GREEN_COLOR], led_2_colors[i][BLUE_COLOR]));
        led_pixels_2.show();
        delay(1);
      }
      break;

    case LED_3:
      for (int i = 0; i < LED_3_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №3 цвета: ") + String(led_3_colors[i][RED_COLOR]) + String(led_3_colors[i][GREEN_COLOR]) + String(led_3_colors[i][BLUE_COLOR]));
        led_pixels_3.setPixelColor(i, led_pixels_3.Color(led_3_colors[i][RED_COLOR], led_1_colors[i][GREEN_COLOR], led_3_colors[i][BLUE_COLOR]));
        led_pixels_3.show();
        delay(1);
      }
      break;

    case LED_4:
      for (int i = 0; i < LED_4_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №4 цвета: ") + String(led_4_colors[i][RED_COLOR]) + String(led_4_colors[i][GREEN_COLOR]) + String(led_4_colors[i][BLUE_COLOR]));
        led_pixels_4.setPixelColor(i, led_pixels_4.Color(led_1_colors[i][RED_COLOR], led_4_colors[i][GREEN_COLOR], led_4_colors[i][BLUE_COLOR]));
        led_pixels_4.show();
        delay(1);
      }
      break;
  }
}

