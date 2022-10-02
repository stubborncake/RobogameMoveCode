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
	switch (newMsg.command)
	{
	case errorCmd:
	{
		// errorCmd handler
		flag = 0;
		break;
	}
	case detectCodeAns:
	{
		//检测到了正确的条形码，需要进行取壶操作
		/*TODO:检测到正确冰壶信息后的取壶操作*/
#ifdef STATIC_DEBUG
		uint8_t newMsg[] = "Code Detected\t";
		printMsg(newMsg);
#endif
		flagDetectCode=1;
		break;
	}
	default:
	{
		// unknown cmd handler
		//其余指令主机均不需要收到
		flag = 0;
		break;
	}
	}
	return flag;
}

void detectCmd(void){
	message_t newCmd;
	newCmd.command=detectCodeCmd;
	newCmd.argList[0]=0;
	sendCommand(newCmd,0);
}

void raiseArmCmd(status_t newDir, uint8_t distance){
	message_t newCmd;
	newCmd.command=armRaiseCmd;
	newCmd.argList[0]=newDir;
	newCmd.argList[1]=distance;
	sendCommand(newCmd,2);
}

/*backup plan for communication with respberry: send raw uint8_t*/
__DEBUG HAL_StatusTypeDef sendCommadbyRaw(command_t newCmd,uint8_t arg1,uint8_t arg2){
	uint8_t newMsg[3]={(uint8_t)newCmd,arg1,arg2};
	return HAL_UART_Transmit(&huart2, newMsg, 3, timeoutDefault);;
}

