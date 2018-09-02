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

//! Локальные макроопределения
#define BRIGHTNESS  64
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define UPDATES_PER_SECOND 100

//! Локальные данные
CFastLED led_pixels_1;
CFastLED led_pixels_2;
CFastLED led_pixels_3;
CFastLED led_pixels_4;

CRGB leds_1[LED_1_NUMBER_PIXELS];
CRGB leds_2[LED_2_NUMBER_PIXELS];
CRGB leds_3[LED_3_NUMBER_PIXELS];
CRGB leds_4[LED_4_NUMBER_PIXELS];

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
CFastLED get_leds(led_id_t led_id)
{
  CFastLED result;
  
  switch(led_id)
  {
    case LED_1:
      result = led_pixels_1;
      break;

    case LED_2:
      result = led_pixels_1;
      break;

    case LED_3:
      result = led_pixels_1;
      break;

    case LED_4:
      result = led_pixels_1;
      break;
  }
  return result;
}

// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette) 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds-1) - pixelnumber;
    
    nblend( ledarray[pixelnumber], newcolor, 128);
  }
}

CRGB Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait, CFastLED leds_class, led_id_t led_id, int led_num) 
{
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<led_num; i++) 
    {
      if (led_id == LED_1)
        leds_1[i] = Wheel((i+j) & 255);
      else if (led_id == LED_2)
        leds_2[i] = Wheel((i+j) & 255);
      else if (led_id == LED_3)
        leds_3[i] = Wheel((i+j) & 255);
      else if (led_id == LED_4)
        leds_4[i] = Wheel((i+j) & 255);
    }
    leds_class.show();
    delay(wait);
  }
}

void fire_programm(CFastLED leds_class, led_id_t led_id, int led_num) 
{
  int r = 255;
  int g = 96;
  int b = 12;
  
  for(int x = 0; x <led_num; x++)
  {
    int flicker = random(0,60);
    int r1 = r-flicker;
    int g1 = g-flicker;
    int b1 = b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    if (led_id == LED_1)
      leds_1[x] = CRGB(r1, g1, b1);
    else if (led_id == LED_2)
      leds_2[x] = CRGB(r1, g1, b1);
    else if (led_id == LED_3)
      leds_3[x] = CRGB(r1, g1, b1);
    else if (led_id == LED_4)
      leds_4[x] = CRGB(r1, g1, b1);
  }
  leds_class.show();
  delay(random(60,150));
}


//! Глобальные функции
void init_leds()
{
  int address_cursor = 0;
  
  EEPROM.begin(EEPROM_SIZE);
  led_pixels_1.addLeds<CHIPSET, LED_IN_PIN_1, COLOR_ORDER>(leds_1, LED_1_NUMBER_PIXELS).setCorrection( TypicalLEDStrip );
  led_pixels_1.setBrightness( BRIGHTNESS );
  led_pixels_2.addLeds<CHIPSET, LED_IN_PIN_2, COLOR_ORDER>(leds_2, LED_2_NUMBER_PIXELS).setCorrection( TypicalLEDStrip );
  led_pixels_2.setBrightness( BRIGHTNESS );
  led_pixels_3.addLeds<CHIPSET, LED_IN_PIN_3, COLOR_ORDER>(leds_3, LED_3_NUMBER_PIXELS).setCorrection( TypicalLEDStrip );
  led_pixels_3.setBrightness( BRIGHTNESS );
  led_pixels_4.addLeds<CHIPSET, LED_IN_PIN_4, COLOR_ORDER>(leds_4, LED_4_NUMBER_PIXELS).setCorrection( TypicalLEDStrip );
  led_pixels_4.setBrightness( BRIGHTNESS );
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

  led_1_programm = 0;//EEPROM.read(LED_1_PROGRAMM);
  led_2_programm = 0;//EEPROM.read(LED_2_PROGRAMM);
  led_3_programm = 0;//EEPROM.read(LED_3_PROGRAMM);
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
        led_pixels_1.showColor(CRGB(led_1_colors[i][RED_COLOR], led_1_colors[i][GREEN_COLOR], led_1_colors[i][BLUE_COLOR]), led_1_brightness);
        delay(1);
      }
      break;

    case LED_2:
      for (int i = 0; i < LED_2_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №2 цвета: ") + String(led_2_colors[i][RED_COLOR])  + String("|") +  String(led_2_colors[i][GREEN_COLOR])  + String("|") +  String(led_2_colors[i][BLUE_COLOR]));
        led_pixels_2.showColor(CRGB(led_2_colors[i][RED_COLOR], led_2_colors[i][GREEN_COLOR], led_2_colors[i][BLUE_COLOR]), led_2_brightness);
        delay(1);
      }
      break;

    case LED_3:
      for (int i = 0; i < LED_3_NUMBER_PIXELS; i++)
      {
        INFO("Установка свеодиода " + String(i) + String(" ленты №3 цвета: ") + String(led_3_colors[i][RED_COLOR])  + String("|") +  String(led_3_colors[i][GREEN_COLOR])  + String("|") +  String(led_3_colors[i][BLUE_COLOR]));
        led_pixels_3.showColor(CRGB(led_3_colors[i][RED_COLOR], led_3_colors[i][GREEN_COLOR], led_3_colors[i][BLUE_COLOR]), led_3_brightness);
        delay(1);
      }
      break;

    case LED_4:
      if (led_4_programm == 0)
      {
        for (int i = 0; i < LED_4_NUMBER_PIXELS; i++)
        {
          INFO("Установка свеодиода " + String(i) + String(" ленты №4 цвета: ") + String(led_4_colors[i][RED_COLOR]) + String("|") + String(led_4_colors[i][GREEN_COLOR]) + String("|") + String(led_4_colors[i][BLUE_COLOR]));
          led_pixels_4.showColor(CRGB(led_4_colors[i][RED_COLOR], led_4_colors[i][GREEN_COLOR], led_4_colors[i][BLUE_COLOR]), led_4_brightness);
          delay(1);
        }
      }
      break;
  }
}

void do_programm()
{
  int8_t led_i = 0;
  int8_t programm = 0;
  int8_t leds_num = 0;
  CFastLED leds_class;
  led_id_t led_id;
  if (led_1_programm == 0 && led_2_programm == 0 && led_3_programm == 0 && led_4_programm == 0)
  {
    return;
  }
  
  if (led_1_programm != 0)
  {
    leds_class = get_leds(LED_1);
    programm = led_1_programm;
    leds_num = LED_1_NUMBER_PIXELS;
    led_id = LED_1;
  }
  else if (led_2_programm != 0)
  {
    leds_class = get_leds(LED_2);
    programm = led_2_programm;
    leds_num = LED_2_NUMBER_PIXELS;
    led_id = LED_2;
  }
  else if (led_3_programm != 0)
  {
    leds_class = get_leds(LED_3);
    programm = led_3_programm;
    leds_num = LED_3_NUMBER_PIXELS;
    led_id = LED_3;
  }
  else if (led_4_programm != 0)
  {
    leds_class = get_leds(LED_4);
    programm = led_4_programm;
    leds_num = LED_4_NUMBER_PIXELS;
    led_id = LED_4;
  }
  else
  {
    return;
  }

  DEBUG("Выполняем программу");
  DEBUG(programm);
  switch(programm)
  {
    case 1: //FIRE
      fire_programm(leds_class, led_id, leds_num);
      break;

    case 2:
      rainbow(20, leds_class, led_id, leds_num);
      break;

    default:
      break;
  }
}

// Gradient Color Palette definitions for 33 different cpt-city color palettes.
//    956 bytes of PROGMEM for all of the palettes together,
//   +618 bytes of PROGMEM for gradient palette code (AVR).
//  1,494 bytes total for all 34 color palettes and associated code.

// Gradient palette "ib_jul01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib_jul01_gp ) {
    0, 194,  1,  1,
   94,   1, 29, 18,
  132,  57,131, 28,
  255, 113,  1,  1};

// Gradient palette "es_vintage_57_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_57.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_vintage_57_gp ) {
    0,   2,  1,  1,
   53,  18,  1,  0,
  104,  69, 29,  1,
  153, 167,135, 10,
  255,  46, 56,  4};

// Gradient palette "es_vintage_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_vintage_01_gp ) {
    0,   4,  1,  1,
   51,  16,  0,  1,
   76,  97,104,  3,
  101, 255,131, 19,
  127,  67,  9,  4,
  153,  16,  0,  1,
  229,   4,  1,  1,
  255,   4,  1,  1};

// Gradient palette "es_rivendell_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/rivendell/tn/es_rivendell_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_rivendell_15_gp ) {
    0,   1, 14,  5,
  101,  16, 36, 14,
  165,  56, 68, 30,
  242, 150,156, 99,
  255, 150,156, 99};

// Gradient palette "rgi_15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE( rgi_15_gp ) {
    0,   4,  1, 31,
   31,  55,  1, 16,
   63, 197,  3,  7,
   95,  59,  2, 17,
  127,   6,  2, 34,
  159,  39,  6, 33,
  191, 112, 13, 32,
  223,  56,  9, 35,
  255,  22,  6, 38};

// Gradient palette "retro2_16_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/retro2/tn/retro2_16.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( retro2_16_gp ) {
    0, 188,135,  1,
  255,  46,  7,  1};

// Gradient palette "Analogous_1_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/red/tn/Analogous_1.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( Analogous_1_gp ) {
    0,   3,  0,255,
   63,  23,  0,255,
  127,  67,  0,255,
  191, 142,  0, 45,
  255, 255,  0,  0};

// Gradient palette "es_pinksplash_08_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_pinksplash_08_gp ) {
    0, 126, 11,255,
  127, 197,  1, 22,
  175, 210,157,172,
  221, 157,  3,112,
  255, 157,  3,112};

// Gradient palette "es_pinksplash_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_pinksplash_07_gp ) {
    0, 229,  1,  1,
   61, 242,  4, 63,
  101, 255, 12,255,
  127, 249, 81,252,
  153, 255, 11,235,
  193, 244,  5, 68,
  255, 232,  1,  5};

// Gradient palette "Coral_reef_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/other/tn/Coral_reef.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( Coral_reef_gp ) {
    0,  40,199,197,
   50,  10,152,155,
   96,   1,111,120,
   96,  43,127,162,
  139,  10, 73,111,
  255,   1, 34, 71};

// Gradient palette "es_ocean_breeze_068_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_068.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_ocean_breeze_068_gp ) {
    0, 100,156,153,
   51,   1, 99,137,
  101,   1, 68, 84,
  104,  35,142,168,
  178,   0, 63,117,
  255,   1, 10, 10};

// Gradient palette "es_ocean_breeze_036_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_036.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_ocean_breeze_036_gp ) {
    0,   1,  6,  7,
   89,   1, 99,111,
  153, 144,209,255,
  255,   0, 73, 82};

// Gradient palette "departure_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/mjf/tn/departure.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 88 bytes of program space.

DEFINE_GRADIENT_PALETTE( departure_gp ) {
    0,   8,  3,  0,
   42,  23,  7,  0,
   63,  75, 38,  6,
   84, 169, 99, 38,
  106, 213,169,119,
  116, 255,255,255,
  138, 135,255,138,
  148,  22,255, 24,
  170,   0,255,  0,
  191,   0,136,  0,
  212,   0, 55,  0,
  255,   0, 55,  0};

// Gradient palette "es_landscape_64_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_64.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 36 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_landscape_64_gp ) {
    0,   0,  0,  0,
   37,   2, 25,  1,
   76,  15,115,  5,
  127,  79,213,  1,
  128, 126,211, 47,
  130, 188,209,247,
  153, 144,182,205,
  204,  59,117,250,
  255,   1, 37,192};

// Gradient palette "es_landscape_33_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_33.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_landscape_33_gp ) {
    0,   1,  5,  0,
   19,  32, 23,  1,
   38, 161, 55,  1,
   63, 229,144,  1,
   66,  39,142, 74,
  255,   1,  4,  1};

// Gradient palette "rainbowsherbet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/icecream/tn/rainbowsherbet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( rainbowsherbet_gp ) {
    0, 255, 33,  4,
   43, 255, 68, 25,
   86, 255,  7, 25,
  127, 255, 82,103,
  170, 255,255,242,
  209,  42,255, 22,
  255,  87,255, 65};

// Gradient palette "gr65_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr65_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( gr65_hult_gp ) {
    0, 247,176,247,
   48, 255,136,255,
   89, 220, 29,226,
  160,   7, 82,178,
  216,   1,124,109,
  255,   1,124,109};

// Gradient palette "gr64_hult_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr64_hult.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( gr64_hult_gp ) {
    0,   1,124,109,
   66,   1, 93, 79,
  104,  52, 65,  1,
  130, 115,127,  1,
  150,  52, 65,  1,
  201,   1, 86, 72,
  239,   0, 55, 45,
  255,   0, 55, 45};

// Gradient palette "GMT_drywet_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_drywet.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( GMT_drywet_gp ) {
    0,  47, 30,  2,
   42, 213,147, 24,
   84, 103,219, 52,
  127,   3,219,207,
  170,   1, 48,214,
  212,   1,  1,111,
  255,   1,  7, 33};

// Gradient palette "ib15_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general/tn/ib15.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib15_gp ) {
    0, 113, 91,147,
   72, 157, 88, 78,
   89, 208, 85, 33,
  107, 255, 29, 11,
  141, 137, 31, 39,
  255,  59, 33, 89};

// Gradient palette "Fuschia_7_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/fuschia/tn/Fuschia-7.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( Fuschia_7_gp ) {
    0,  43,  3,153,
   63, 100,  4,103,
  127, 188,  5, 66,
  191, 161, 11,115,
  255, 135, 20,182};

// Gradient palette "es_emerald_dragon_08_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/emerald_dragon/tn/es_emerald_dragon_08.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_emerald_dragon_08_gp ) {
    0,  97,255,  1,
  101,  47,133,  1,
  178,  13, 43,  1,
  255,   2, 10,  1};

// Gradient palette "lava_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/lava.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE( lava_gp ) {
    0,   0,  0,  0,
   46,  18,  0,  0,
   96, 113,  0,  0,
  108, 142,  3,  1,
  119, 175, 17,  1,
  146, 213, 44,  2,
  174, 255, 82,  4,
  188, 255,115,  4,
  202, 255,156,  4,
  218, 255,203,  4,
  234, 255,255,  4,
  244, 255,255, 71,
  255, 255,255,255};

// Gradient palette "fire_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/fire.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( fire_gp ) {
    0,   1,  1,  0,
   76,  32,  5,  0,
  146, 192, 24,  0,
  197, 220,105,  5,
  240, 252,255, 31,
  250, 252,255,111,
  255, 255,255,255};

// Gradient palette "Colorfull_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Colorfull.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE( Colorfull_gp ) {
    0,  10, 85,  5,
   25,  29,109, 18,
   60,  59,138, 42,
   93,  83, 99, 52,
  106, 110, 66, 64,
  109, 123, 49, 65,
  113, 139, 35, 66,
  116, 192,117, 98,
  124, 255,255,137,
  168, 100,180,155,
  255,  22,121,174};

// Gradient palette "Magenta_Evening_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Magenta_Evening.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( Magenta_Evening_gp ) {
    0,  71, 27, 39,
   31, 130, 11, 51,
   63, 213,  2, 64,
   70, 232,  1, 66,
   76, 252,  1, 69,
  108, 123,  2, 51,
  255,  46,  9, 35};

// Gradient palette "Pink_Purple_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Pink_Purple.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE( Pink_Purple_gp ) {
    0,  19,  2, 39,
   25,  26,  4, 45,
   51,  33,  6, 52,
   76,  68, 62,125,
  102, 118,187,240,
  109, 163,215,247,
  114, 217,244,255,
  122, 159,149,221,
  149, 113, 78,188,
  183, 128, 57,155,
  255, 146, 40,123};

// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160};

// Gradient palette "es_autumn_19_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/autumn/tn/es_autumn_19.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE( es_autumn_19_gp ) {
    0,  26,  1,  1,
   51,  67,  4,  1,
   84, 118, 14,  1,
  104, 137,152, 52,
  112, 113, 65,  1,
  122, 133,149, 59,
  124, 137,152, 52,
  135, 113, 65,  1,
  142, 139,154, 46,
  163, 113, 13,  1,
  204,  55,  3,  1,
  249,  17,  1,  1,
  255,  17,  1,  1};

// Gradient palette "BlacK_Blue_Magenta_White_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Blue_Magenta_White.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( BlacK_Blue_Magenta_White_gp ) {
    0,   0,  0,  0,
   42,   0,  0, 45,
   84,   0,  0,255,
  127,  42,  0,255,
  170, 255,  0,255,
  212, 255, 55,255,
  255, 255,255,255};

// Gradient palette "BlacK_Magenta_Red_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Magenta_Red.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( BlacK_Magenta_Red_gp ) {
    0,   0,  0,  0,
   63,  42,  0, 45,
  127, 255,  0,255,
  191, 255,  0, 45,
  255, 255,  0,  0};

// Gradient palette "BlacK_Red_Magenta_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Red_Magenta_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( BlacK_Red_Magenta_Yellow_gp ) {
    0,   0,  0,  0,
   42,  42,  0,  0,
   84, 255,  0,  0,
  127, 255,  0, 45,
  170, 255,  0,255,
  212, 255, 55, 45,
  255, 255,255,  0};

// Gradient palette "Blue_Cyan_Yellow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Blue_Cyan_Yellow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( Blue_Cyan_Yellow_gp ) {
    0,   0,  0,255,
   63,   0, 55,255,
  127,   0,255,255,
  191,  42,255, 45,
  255, 255,255,  0};

DEFINE_GRADIENT_PALETTE( fire ) {
    255,   0,  0,255,
   255,   128, 0,255,
  255,   255,0,255};


// Single array of defined cpt-city color palettes.
// This will let us programmatically choose one based on
// a number, rather than having to activate each explicitly 
// by name every time.
// Since it is const, this array could also be moved 
// into PROGMEM to save SRAM, but for simplicity of illustration
// we'll keep it in a regular SRAM array.
//
// This list of color palettes acts as a "playlist"; you can
// add or delete, or re-arrange as you wish.
const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
  BlacK_Red_Magenta_Yellow_gp};


// Count of how many cpt-city gradients are defined:
const uint8_t gGradientPaletteCount = 
  sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );

