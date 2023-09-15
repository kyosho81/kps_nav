
#include "CRC.h"
#include <stdio.h>
#include <string.h>

unsigned short Utils_get_crc(unsigned char *puchMsg , unsigned short usDataLen)
{
	unsigned char uchCRCHi = 0xFF ; /* high unsigned char of CRC initialized */ 
	unsigned char uchCRCLo = 0xFF ; /* low unsigned char of CRC initialized */ 
	unsigned uIndex ; /* will index into CRC lookup table */ 
	while (usDataLen--)/* pass through message buffer */ 
	{ 
		uIndex = uchCRCHi ^ *puchMsg++ ; /* calculate the CRC */ 
		uchCRCHi = uchCRCLo ^ crc16_tableHi[uIndex]; 
		uchCRCLo = crc16_tableLo[uIndex] ; 
	} 
	return (uchCRCHi << 8 | uchCRCLo) ; 
}

bool Utils_is_crc_good( unsigned char *pushMsg, int usDataLen )
{
	return ( (pushMsg[ usDataLen ] << 8 | pushMsg[ usDataLen + 1]) == Utils_get_crc( pushMsg, usDataLen ) );
}
void Utils_Add_crc(unsigned char *pData,unsigned short shLen)
{
	unsigned short shCRC = Utils_get_crc(pData,shLen);
	pData[shLen] = (shCRC & 0xFF00) >> 8;
	pData[shLen+1] = shCRC & 0xFF;

}

