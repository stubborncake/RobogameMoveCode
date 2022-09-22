/*复制到main.h里面，也可以新建一个connectivity.h,然后复制到这里面*/

/* USER CODE BEGIN ET */
#include "main.h"
#include "usart.h"




HAL_StatusTypeDef sendCommand(message_t newMsg);
void receiveCmd(message_t newMsg);
void Delay_us(uint16_t us);
/* USER CODE END ET */
