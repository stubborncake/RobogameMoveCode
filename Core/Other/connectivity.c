/**
 * @file connectivity.c
 * @author team_BlackStar
 * @brief 通信相关函数
 * @version 0.2
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * @warning message_t的封装目前有点小问题，目前使用裸发送uint8_t型字符串的函数
 */
#include "connectivity.h"

HAL_StatusTypeDef sendCommand(message_t &newCmd, const uint8_t argCount)
{
	uint8_t newMsg[argCountMax+2]={0};
	newMsg[0] = (uint8_t)newCmd.command;
	for (uint8_t i = 0; i < argCount; i++)
	{
		newMsg[i + 1] = newCmd.argList[i];
	}
	newMsg[argCount + 1] = 0;
	return HAL_UART_Transmit(&huart2, newMsg, argCount + 2, timeoutDefault);
}

status_t receiveCommand(message_t newMsg)
{
	status_t flag = 1;
	switch (newMsg.command){
	case errorCmd:
	{
		// errorCmd handler
		flag = 0;
		break;
	}
	case detectCodeAns:
	{
		//检测到了正确的条形码，需要进行取壶操作
#ifndef __DEBUG
		uint8_t newInfor[] = "Code Detected\t";
		printMsg(newInfor);
		if(newMsg.argList[0]==1){
			flagDetectCode=1;
		}
#else
		flagDetectCode=1;
#endif
		break;
	}
	case reservedCmd:{
		//接收到了预留的指令，可以用来作为确认指令
		break;
	}
	default:{
		// unknown cmd handler
		//其余指令主机均不需要收到
		flag = 0;
		break;
	}
	}
	return flag;
}

void detectCurlingCmd(void){
	sendCommadbyRaw(detectCodeCmd,0);
}

void raiseArmCmd(status_t newDir, uint8_t distance){
	sendCommadbyRaw(armRaiseCmd, newDir, distance);
}

HAL_StatusTypeDef sendCommadbyRaw(command_t newCmd,uint8_t arg1,uint8_t arg2){
	/*backup plan for communication with respberry: send raw uint8_t*/
	uint8_t newMsg[3]={(uint8_t)newCmd,arg1,arg2};
	HAL_StatusTypeDef flag=HAL_ERROR;
	static const uint8_t attemptTime=5;
	static const uint32_t retryInterval=100;

	/*如果uart没有返回成功标志，则多次尝试发送*/
	for(uint8_t i=0;i<attemptTime;i++){
		flag=HAL_UART_Transmit(&huart2, newMsg, 3, retryInterval);
		if(flag==HAL_OK){
			break;
		}else{
			HAL_Delay(retryInterval);
		}
	}
	return flag;
}
