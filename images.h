#pragma once

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef struct _tIMAGE
{    
  const uint8_t *Data;
  uint16_t Width;
  uint16_t Height;
  
} sIMAGE;

extern sIMAGE IMG_bat_0;
extern sIMAGE IMG_bat_100;
extern sIMAGE IMG_bat_25;
extern sIMAGE IMG_bat_50;
extern sIMAGE IMG_bat_75;
extern sIMAGE IMG_offline;
extern sIMAGE IMG_online;
extern sIMAGE IMG_power_in;
extern sIMAGE IMG_standby;
extern sIMAGE IMG_spinner_0;
extern sIMAGE IMG_spinner_1;
extern sIMAGE IMG_spinner_2;
extern sIMAGE IMG_spinner_3;
extern sIMAGE IMG_spinner_4;
extern sIMAGE IMG_spinner_5;

#ifdef __cplusplus
}
#endif