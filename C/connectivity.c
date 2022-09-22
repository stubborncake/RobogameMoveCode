#include "main.h"
#include "connectivity.h"
#include "usart.h"
#include "motor.h"

inline HAL_StatusTypeDef sendCommand(message_t newMsg)
{
  uint8_t newTX_buf[100]={0};
  HAL_StatusTypeDef flag=HAL_OK;
	uint8_t *tx_ptr=newTX_buf;
  uint8_t *msgList_ptr=newMsg.argList;
	uint16_t buffSize=newMsg.argCount+2;
	
  /*construct tx_buf*/
	*tx_ptr=(uint8_t)newMsg.command;
	tx_ptr++;
  *tx_ptr=newMsg.argCount;
  tx_ptr++;
	for(int i=0;i<newMsg.argCount;i++)
	{
		*tx_ptr=*msgList_ptr;
		tx_ptr++;
		msgList_ptr++;
	}
	*tx_ptr='\0';

	flag=HAL_UART_Transmit(&huart2,newTX_buf,buffSize,newMsg.timeout);
  //while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=RESET);
	return flag;

}

inline void receiveCmd(message_t newMsg)
{
	test=newMsg.argList[0];
  switch (newMsg.command)
  {
  case errorCmd:
    break;
  case testCmd:
    sendCommand(newMsg);
  break;
		
	case trimCmd:
	break;
				
	case moveCmd:		
	break;
	
	case rotateCmd:
	break;	
		
	case stopCmd:
	break;	
	
	case reservedCmd:
	break;

  default:
  break;
  }

}
inline __USED void Delay_us(uint16_t us)
{
  const uint16_t Delay_Factor_us = HAL_RCC_GetHCLKFreq() / 1000 / 1000; // ought to be defined in .h file
  uint32_t tmp;
  SysTick->LOAD = us * Delay_Factor_us;
  SysTick->VAL = 0x00;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
  do{
    tmp = SysTick->CTRL;
  } while (tmp & 0x01 && !(tmp & (1 << 16)));
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL = 0x00;
}

