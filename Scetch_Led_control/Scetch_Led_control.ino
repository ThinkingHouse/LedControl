/*!
 *  \file      Scetch_Led_control.ino
 *
 *  \brief     Главный исполняемый файл
 *
 *  \detailed  Содержит точку входа  
 *
 *  \author    Андрей Алексеев <andrey@thinking-house.ru
 *
 *  \copyright Лаборатория Умного Дома (ИП Алексеев А.П.), 2018. Все права защищены.
 */

//! Подключение заголовочных файлов
#include "http_server.h"

//! Глобальные данные

//! Макроопределения

//! Типы

//! Локальные функции

//! Глобальные функции

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
  init_server();
}

void loop() 
{
	check_clinets();
}
