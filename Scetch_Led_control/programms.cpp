#include "programms.h"

int8_t programm_1[5][4] = { {121,   2,   1,   1},   
                            { 55,  18,   1,   1},  
                            {131,  69,  29,   1},  
                            {100, 167, 135,  10},
                            {100,  46,  56,   4} };

int8_t programm_2[5][4] = { { 31,  55,   1,   16},   
                            { 63, 197,   3,    7},  
                            { 95,  59,   2,   17},  
                            {127,   6,   2,   34},
                            {159,  39,   6,   33} };

int8_t programm_3[5][4] = { {121,   3,   0,  255},   
                            { 63,  23,   0,  255},  
                            {127,  67,   0,  255},  
                            {191, 142,   0,   45},
                            {155, 255,   0,    0} };

int8_t programm_4[5][4] = { {121,   126,   11,   255},   
                            {127,  197,   1,   22},  
                            {175,  210,  157,   172},  
                            {221, 157, 3,  112},
                            {255,  157,  3,   112} };

int8_t programm_5[5][4] = { {61,   242,   4,   63},   
                            { 101,  255,   12,   255},  
                            {127,  249,  81,   252},  
                            {153, 255, 11,  235},
                            {255,  232,  1,   5} };

int8_t programm_6[5][4] = { {64,   242,   4,   63},   
                            { 128,  242,   4,   63},  
                            {254,  242,  4,   63},  
                            {128, 242, 4,  63},
                            {64,  242,  4,   63} };

int8_t get_programm(int8_t programm, int8_t x, int8_t y)
{
  switch(programm)
  {
    case 1:
      return programm_1[x][y];

    case 2:
      return programm_2[x][y];

    case 3:
      return programm_3[x][y];

    case 4:
      return programm_4[x][y];

    case 5:
      return programm_5[x][y];

    case 6:
      return programm_6[x][y];

    default:
      return 255;
  }
}

