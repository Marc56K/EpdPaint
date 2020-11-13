# include "images.h"
# include <pgmspace.h>

const uint8_t IMG_bat_100_data[] PROGMEM = 
{
	0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x40, //  ####################################   
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x50, // ######################################  
	0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, // ##                                  ##  
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x50, // ##  ######  ######  ######  ######  ##  
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x50, // ##  ######  ######  ######  ######  ##  
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x50, // ##  ######  ######  ######  ######  ##  
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, // ##  ######  ######  ######  ######  ####
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x50, // ##  ######  ######  ######  ######  ##  
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x50, // ##  ######  ######  ######  ######  ##  
	0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x55, 0x50, 0x50, // ##  ######  ######  ######  ######  ##  
	0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, // ##                                  ##  
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x50, // ######################################  
	0x15, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x40, //  ####################################   
};

sIMAGE IMG_bat_100 = {
  IMG_bat_100_data,
  40, /* Width */
  20, /* Height */
};
