
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

/*检测冰壶条形码指令*/
void detectCmd(void);
/*机械臂上升或者下降指令*/
void raiseArmCmd(status_t newDir, uint8_t distance);
/*发送原始uint8_t型的指令，跳过了message_t的封装过程*/
__DEBUG HAL_StatusTypeDef sendCommadbyRaw(command_t newCmd,uint8_t arg1=0,uint8_t arg2=0);

/* Private defines -----------------------------------------------------------*/

#define __CONNECTIVITY

#ifdef __cplusplus
}
#endif

#endif
