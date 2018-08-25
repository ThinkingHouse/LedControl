/*!
 *  \file      common.cpp
 *
 *  \brief     Реализация функций для отладочных целей
 *
 *  \detailed   
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru>
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */

//! Подключение заголовочных файлов
#include "common.h"

//! Локальные данные
int32_t cpu_freq;
int16_t main_delay = 10;
//! Локальные Макроопределения

//! Локальные функции
float get_time()
{
  float result = 0;
  result = (float)ESP.getCycleCount() / (float)cpu_freq;
  return result;
}

//! Глобальные функции
void init_debug()
{
  Serial.begin(115200);
  cpu_freq = ESP.getCpuFreqMHz() * 1000000;
  EEPROM.begin(EEPROM_SIZE);
  main_delay = EEPROM.read(500);
  EEPROM.end();
  INFO("Debug is ready.");
  INFO("Частота процессора " + String(cpu_freq));
}
 
void print_log(String text, log_levels_t level)
{
  Serial.print(get_time());Serial.print(" :: ");
  switch(level)
  {
    case INFO:
      Serial.print(" INFO ");Serial.print(" :: ");
      break;
    case DEBUG:
      Serial.print(" DEBUG ");Serial.print(" :: ");
      break;
    case TRACE:
      Serial.print(" TRACE ");Serial.print(" :: ");
      break;
  }
  Serial.println(text);
}

void print_log(IPAddress text, log_levels_t level)
{
    Serial.print(get_time());Serial.print(" :: ");
  switch(level)
  {
    case INFO:
      Serial.print(" INFO ");Serial.print(" :: ");
      break;
    case DEBUG:
      Serial.print(" DEBUG ");Serial.print(" :: ");
      break;
    case TRACE:
      Serial.print(" TRACE ");Serial.print(" :: ");
      break;
  }
  Serial.println(text);
}

void set_main_delay(String delay_s)
{
  main_delay = delay_s.toInt();
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.write(500, main_delay);
  EEPROM.end();
}
int16_t get_main_delay()
{
  return main_delay;
}

