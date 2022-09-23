
#ifndef __CONNECTIVITY_H
#define __CONNECTIVITY_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported functions prototypes ---------------------------------------------*/

/*向respberry发送指令*/
HAL_StatusTypeDef sendCommand(message_t newMsg);

/*接收到uart2传来的指令后的处理*/
status_t receiveCommand(message_t newMsg);

/* Private defines -----------------------------------------------------------*/

#define __CONNECTIVITY

#ifdef __cplusplus
}
#endif

#endif
