/*
 * FreeModbus Libary: BARE Demo Application
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "main.h"
/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START 1
#define REG_INPUT_NREGS 2
#define REG_HOLDING_START 1
#define REG_HOLDING_NREGS 2

/* ----------------------- Static variables ---------------------------------*/
static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];

static USHORT   usRegHoldingStart = REG_HOLDING_START;
static USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];

uint8_t RS485_Get_Address()
{
	uint8_t Address = 0x00;
	
	Address = Address | (( HAL_GPIO_ReadPin(X1_GPIO_Port, X1_Pin)) << 4)  \
										| (( HAL_GPIO_ReadPin(X2_GPIO_Port, X2_Pin)) << 5 ) \
										| (( HAL_GPIO_ReadPin(X3_GPIO_Port, X3_Pin)) << 6 ) \
										| (( HAL_GPIO_ReadPin(X4_GPIO_Port, X4_Pin)) << 7 ) \
										| (( HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)) << 0 ) \
										| (( HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)) << 1 ) \
										| (( HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)) << 2 ) \
										| (( HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)) << 3 );
	return ~Address;
}
void cmd_control()
{
	if(usRegHoldingBuf[0] != 0x0000)
	{
		switch(usRegHoldingBuf[0])
		{
			case 1:
				HAL_GPIO_WritePin(LOCK_1_GPIO_Port, LOCK_1_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(LOCK_1_GPIO_Port, LOCK_1_Pin, GPIO_PIN_RESET);
				break;
			case 2:
				HAL_GPIO_WritePin(LOCK_2_GPIO_Port, LOCK_2_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(LOCK_2_GPIO_Port, LOCK_2_Pin, GPIO_PIN_RESET);
				break;
			case 3:
				HAL_GPIO_WritePin(LOCK_3_GPIO_Port, LOCK_3_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(LOCK_3_GPIO_Port, LOCK_3_Pin, GPIO_PIN_RESET);
				break;
			case 4:
				HAL_GPIO_WritePin(LOCK_4_GPIO_Port, LOCK_4_Pin, GPIO_PIN_SET);
				HAL_Delay(200);
				HAL_GPIO_WritePin(LOCK_4_GPIO_Port, LOCK_4_Pin, GPIO_PIN_RESET);
				break;
			case 5:
				HAL_GPIO_WritePin(LOCK_5_GPIO_Port, LOCK_5_Pin, GPIO_PIN_SET);
				break;
			case 0x06:
				HAL_GPIO_WritePin(LOCK_5_GPIO_Port, LOCK_5_Pin, GPIO_PIN_RESET);
				break;
		}
		usRegHoldingBuf[0] = 0;
	}
}
void cmd_FeedBack()
{
	uint16_t state = 0x00;
	
	state = state | (( HAL_GPIO_ReadPin(FB_1_GPIO_Port, FB_1_Pin)) << 0)  \
								| (( HAL_GPIO_ReadPin(FB_2_GPIO_Port, FB_2_Pin)) << 1 ) \
								| (( HAL_GPIO_ReadPin(FB_3_GPIO_Port, FB_3_Pin)) << 2 ) \
								| (( HAL_GPIO_ReadPin(FB_4_GPIO_Port, FB_4_Pin)) << 3 ) \
								| (( HAL_GPIO_ReadPin(FB_5_GPIO_Port, FB_5_Pin)) << 4 );
	
	usRegInputBuf[0] = state;
}

eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
       eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_HOLDING_START ) &&
        ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegHoldingStart );
        switch ( eMode )
        {
            /* Pass current register values to the protocol stack. */
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
                *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
                *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            break;

            /* Update current register values with new values from the
             * protocol stack. */
        case MB_REG_WRITE:
            while( usNRegs > 0 )
            {
                usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                iRegIndex++;
                usNRegs--;
            }
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}


eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
