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
#include "programms.h"

//! Локальные данные
Adafruit_NeoPixel led_pixels_1 = Adafruit_NeoPixel(LED_1_NUMBER_PIXELS, LED_IN_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_pixels_2 = Adafruit_NeoPixel(LED_2_NUMBER_PIXELS, LED_IN_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_pixels_3 = Adafruit_NeoPixel(LED_3_NUMBER_PIXELS, LED_IN_PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_pixels_4 = Adafruit_NeoPixel(LED_4_NUMBER_PIXELS, LED_IN_PIN_4, NEO_GRB + NEO_KHZ800);

int16_t led_1_colors[LED_1_NUMBER_PIXELS][3];
int16_t led_2_colors[LED_2_NUMBER_PIXELS][3];
int16_t led_3_colors[LED_3_NUMBER_PIXELS][3];
int16_t led_4_colors[LED_4_NUMBER_PIXELS][3];
int16_t led_1_brightness = 255;
int16_t led_2_brightness = 255;
int16_t led_3_brightness = 255;
int16_t led_4_brightness = 255;

int8_t led_1_programm = 0;
int8_t led_2_programm = 0;
int8_t led_3_programm = 0;
int8_t led_4_programm = 0;
int8_t programm_head = 0;

//! Локальные Макроопределения
#define RED_COLOR    0
#define GREEN_COLOR  1
#define BLUE_COLOR   2

//! Локальные функции
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return led_pixels_4.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return led_pixels_4.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return led_pixels_4.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<led_pixels_4.numPixels(); i++) 
    {
      led_pixels_4.setPixelColor(i, Wheel((i+j) & 255));
    }
    led_pixels_4.show();
    delay(wait);
  }
}


//! Глобальные функции
void init_leds()
{
  int address_cursor = 0;
  
  EEPROM.begin(EEPROM_SIZE);
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

  led_1_brightness = EEPROM.read(LED_1_BRIGHTNESS);
  led_2_brightness = EEPROM.read(LED_2_BRIGHTNESS);
  led_3_brightness = EEPROM.read(LED_3_BRIGHTNESS);
  led_4_brightness = EEPROM.read(LED_4_BRIGHTNESS);
  
  update_leds_colors(LED_1);
  update_leds_colors(LED_2);
  update_leds_colors(LED_3);
  update_leds_colors(LED_4);

  led_4_programm = EEPROM.read(LED_4_PROGRAMM);
  EEPROM.end();
  INFO("Инициализация светодиодных лент завершена");
}

void set_leds_colors(led_id_t led_id, int16_t red, int16_t green, int16_t blue)
{
  int address_cursor = 0;
  EEPROM.begin(EEPROM_SIZE);
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

void set_brightness(led_id_t led_id, int16_t value)
{
  EEPROM.begin(EEPROM_SIZE);
  switch(led_id)
  {
    case LED_1:
        EEPROM.write(LED_1_BRIGHTNESS, value);
        led_1_brightness = value;
      break;

    case LED_2:
        EEPROM.write(LED_2_BRIGHTNESS, value);
        led_2_brightness = value;
      break;

    case LED_3:
        EEPROM.write(LED_3_BRIGHTNESS, value);
        led_3_brightness = value;
      break;

    case LED_4:
        EEPROM.write(LED_4_BRIGHTNESS, value);
        led_4_brightness = value;
      break;
  }
  EEPROM.end();
}

void set_programm(int8_t value)
{
  EEPROM.begin(EEPROM_SIZE);
  led_4_programm = value;
  EEPROM.write(LED_4_PROGRAMM, value);
  EEPROM.end();
}

void update_leds_colors(led_id_t led_id)
{
  switch(led_id)
  {
    case LED_1:
      for (int i = 0; i < LED_1_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №1 цвета: ") + String(led_1_colors[i][RED_COLOR])  + String("|") +  String(led_1_colors[i][GREEN_COLOR])  + String("|") +  String(led_1_colors[i][BLUE_COLOR]));
        led_pixels_1.setPixelColor(i, led_pixels_1.Color(led_1_colors[i][RED_COLOR], led_1_colors[i][GREEN_COLOR], led_1_colors[i][BLUE_COLOR]));
        led_pixels_1.setBrightness(led_1_brightness);
        led_pixels_1.show();
        delay(1);
      }
      break;

    case LED_2:
      for (int i = 0; i < LED_2_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №2 цвета: ") + String(led_2_colors[i][RED_COLOR])  + String("|") +  String(led_2_colors[i][GREEN_COLOR])  + String("|") +  String(led_2_colors[i][BLUE_COLOR]));
        led_pixels_2.setPixelColor(i, led_pixels_2.Color(led_2_colors[i][RED_COLOR], led_2_colors[i][GREEN_COLOR], led_2_colors[i][BLUE_COLOR]));
        led_pixels_2.setBrightness(led_2_brightness);
        led_pixels_2.show();
        delay(1);
      }
      break;

    case LED_3:
      for (int i = 0; i < LED_3_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №3 цвета: ") + String(led_3_colors[i][RED_COLOR])  + String("|") +  String(led_3_colors[i][GREEN_COLOR])  + String("|") +  String(led_3_colors[i][BLUE_COLOR]));
        led_pixels_3.setPixelColor(i, led_pixels_3.Color(led_3_colors[i][RED_COLOR], led_3_colors[i][GREEN_COLOR], led_3_colors[i][BLUE_COLOR]));
        led_pixels_3.setBrightness(led_3_brightness);
        led_pixels_3.show();
        delay(1);
      }
      break;

    case LED_4:
      if (led_4_programm == 0)
      {
        for (int i = 0; i < LED_4_NUMBER_PIXELS; i++)
        {
          INFO("Установка свеодиода " + String(i) + String(" ленты №4 цвета: ") + String(led_4_colors[i][RED_COLOR]) + String("|") + String(led_4_colors[i][GREEN_COLOR]) + String("|") + String(led_4_colors[i][BLUE_COLOR]));
          led_pixels_4.setPixelColor(i, led_pixels_4.Color(led_4_colors[i][RED_COLOR], led_4_colors[i][GREEN_COLOR], led_4_colors[i][BLUE_COLOR]));
          led_pixels_4.setBrightness(led_4_brightness);
          led_pixels_4.show();
          delay(1);
        }
      }
      break;
  }
}

void do_programm()
{
  int8_t led_i = 0;
  if (led_4_programm == 0)
  {
    return;
  }

  if (led_4_programm == 7)
  {
    rainbow(5);
    return;
  }

  DEBUG("Выполняем программу");
  DEBUG(led_4_programm);
  led_i = programm_head;
  for (int8_t j = 0; j < LED_4_NUMBER_PIXELS; j++)
  {
    if (led_i == 5)
    {
      led_i = 0;
    }
    //INFO(led_i);
    led_pixels_4.setPixelColor(j, led_pixels_4.Color(get_programm(led_4_programm, led_i, 1), get_programm(led_4_programm, led_i, 2), get_programm(led_4_programm, led_i, 3)));
    led_pixels_4.setBrightness(get_programm(led_4_programm, led_i, 0));
    led_pixels_4.show();
    led_i++;
    delay(1);
  }
  programm_head++;
  if (programm_head == 5)
  {
    programm_head = 0;
  }
}

