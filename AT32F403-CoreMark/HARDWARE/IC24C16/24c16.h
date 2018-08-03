#ifndef __24C16_H
#define __24C16_H
#include "sys.h"

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  

#define EE_TYPE AT24C16

#define EEPROM_PAGE_SIZE   16  /* 24xx16的页面大小 */
#define EEPROM_SIZE		   2048	/* 24xx16总容量 */
enum
{
	Fail = 0,    //失败
	Success, //成功
};

u8 AT24C16_Check(void);
u8 AT24C16_PageWrite(u8 *_pWriteBuf,u16 _usAddress,u16 _usSize);
u8 AT24C16_PageRead(u8 *_pReadBuf,u16 _usAddress, u16 _usSize);
#endif
