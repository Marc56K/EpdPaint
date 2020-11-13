# include "images.h"
# include <pgmspace.h>

const uint8_t IMG_power_in_data[] PROGMEM = 
{
	0x00, 0xAA, 0xAA, 0x00, //     ++++++++  
	0x02, 0x95, 0x56, 0x00, //    ++######+  
	0x0A, 0x5A, 0xA6, 0xA0, //   ++##++++#+++
	0xA9, 0x6A, 0xA5, 0x60, // +++##+++++###+
	0x55, 0xAA, 0xA6, 0xA0, // ####++++++#+++
	0xA9, 0x6A, 0xA5, 0x60, // +++##+++++###+
	0x0A, 0x5A, 0xA6, 0xA0, //   ++##++++#+++
	0x02, 0x95, 0x56, 0x00, //    ++######+  
	0x00, 0xAA, 0xAA, 0x00, //     ++++++++  
};

sIMAGE IMG_power_in = {
  IMG_power_in_data,
  14, /* Width */
  9, /* Height */
};
