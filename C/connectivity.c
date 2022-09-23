#include "connectivity.h"

HAL_StatusTypeDef sendCommand(message_t &newCmd,const uint8_t argCount){
	uint8_t *newMsg=new uint8_t[argCount+2];
	newMsg[0]=(uint8_t)newCmd.command;
	for(uint8_t i=0;i<argCount;i++){
		newMsg[i+1]=newCmd.argList[i];
	}
	newMsg[argCount+1]=0;
	return HAL_UART_Transmit(&huart2,newMsg,argCount+2,timeoutDefault);
}

status_t receiveCommand(message_t newMsg){
	status_t flag=1;
	switch (newMsg.command)
	{
	case errorCmd:{
		//errorCmd handler
		flag=0;
		break;
		}
	case detectCodeAns:{
		//检测到了正确的条形码，需要进行取壶操作
		/*TODO:检测到正确冰壶信息后的取壶操作*/
		uint8_t newMsg[]="Code Detected\t";
		printMsg(newMsg);

		break;
		}
	default:{
		//unknown cmd handler
		//其余指令主机均不需要收到
		flag=0;
		break;
		}
	}
	return flag;
}
