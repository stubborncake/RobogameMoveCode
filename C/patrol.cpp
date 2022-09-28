
#include "patrol.h"
#include "tracer.h"
#include "chassis.h"

/* Exported macro ------------------------------------------------------------*/

selector_t tracerSelector;
patrol_t patrol;

/* Exported functions defines ---------------------------------------------*/

/* Private functions defines ---------------------------------------------*/

inline void setSelectorGPIO(GPIO_PinState outA,GPIO_PinState outB){
	HAL_GPIO_WritePin(SELECTOR0_GPIO_Port,SELECTOR0_Pin,outA);
	HAL_GPIO_WritePin(SELECTOR1_GPIO_Port,SELECTOR1_Pin,outB);

}

inline direction_t getRightDir(direction_t newDir){
	uint8_t rightDir=dirNowhere;
    switch (newDir)
    {
    case dirFront:
        rightDir=dirRight;
        break;
    case dirRight:
        rightDir=dirBack;
        break;
    case dirLeft:
        rightDir=dirFront;
        break;
    case dirBack:
        rightDir=dirLeft;
        break;
    default:
        rightDir=dirNowhere;
        break;
    }
    return (direction_t)rightDir;
}

/* Class functions defines ---------------------------------------------*/

/*Selector_t functions defines---------------------------------------------*/

selector_t::selector_t(){
	currDir=(uint8_t)dirFront;
}

selector_t::~selector_t(){

}

void selector_t::updateOutput(void)const{
	#define ON GPIO_PIN_SET
	#define OFF GPIO_PIN_RESET

	void setSelectorGPIO(GPIO_PinState outA,GPIO_PinState outB);

	/*NOTE:与理论返回逻辑值完全不同，可能是接线问题，
		最初的设计依次为fornt,right,back,left*/
	switch ((direction_t)currDir){
	case dirBack:
		setSelectorGPIO(OFF,OFF);
		break;
	case dirLeft:
		setSelectorGPIO(ON,OFF);
		break;
	case dirRight:
		setSelectorGPIO(OFF,ON);
		break;
	case dirFront:
		setSelectorGPIO(ON,ON);
		break;
	default:
		break;
	}

	#undef ON
	#undef OFF
}

void selector_t::setCurrDir(direction_t newDir){
	currDir=(uint8_t)newDir;
	updateOutput();
}

direction_t selector_t::update(void){
	if(currDir<dirBack){
		currDir++;
	}else{
		currDir=dirFront;
	}
	updateOutput();
	return (direction_t)currDir;
}

void updateSelector(selector_t &selector){
	selector.update();
}

/*patrol_t functions defines---------------------------------------------*/
patrol_t::patrol_t(){
	currPlainNode=nowhere;
	preKeyNode=startLine;
	updateOn=tracer_nsp::off;
}

patrol_t::~patrol_t(){
	currPlainNode=nowhere;
	preKeyNode=startLine;
	updateOn=tracer_nsp::off;
}

void patrol_t::updatePlainNode(void){
	/*原先算法，代码量过大，用于校对
	PLAIN_NODE_SET(0,0,0,0,nowhere);
	PLAIN_NODE_SET(1,0,0,0,frontOnly);
	PLAIN_NODE_SET(0,0,1,0,backOnly);
	PLAIN_NODE_SET(0,1,0,0,rightOnly);
	PLAIN_NODE_SET(0,0,0,1,leftOnly);
	PLAIN_NODE_SET(1,0,1,0,straightLine);
	PLAIN_NODE_SET(0,1,0,1,horizontalLine);
	PLAIN_NODE_SET(0,1,1,0,rightTurn);
	PLAIN_NODE_SET(0,0,1,1,leftTurn);
	PLAIN_NODE_SET(1,1,1,0,rightFork);
	PLAIN_NODE_SET(1,0,1,1,leftFork);
	PLAIN_NODE_SET(0,1,1,1,T_crossing);
	PLAIN_NODE_SET(1,1,1,1,crossing);
*/

	if(updateOn==tracer_nsp::off)
		return;
	
	/*用uint8_t的四个比特表示front, right, left, back的onpath二值*/
	/*行进方向的节点类型*/
	/*由于keil不支持2进制的表示，故只能计算后用十进制表示*/
	uint8_t pathMask=0;
	direction_t currDirFront=(direction_t)chassis.headingDir;
	direction_t currDirRight=getRightDir(currDirFront);
	direction_t currDir[directionCount]={currDirFront,currDirRight,oppositeDir(currDirRight),oppositeDir(currDirFront)};
	for(uint8_t i=0;i<directionCount;i++){
		pathMask+=tracer[currDir[i]].onPath;
		pathMask*=2;
	}
	switch(pathMask){
		case (0):
			currPlainNode=nowhere;
			break;
		case (8):
			currPlainNode=frontOnly;
			break;
		case (2):
			currPlainNode=backOnly;
			break;
		case (4):
			currPlainNode=rightOnly;
			break;
		case (1):
			currPlainNode=leftOnly;
			break;
		case (10):
			currPlainNode=straightLine;
			break;
		case (5):
			currPlainNode=horizontalLine;
			break;
		case (6):
			currPlainNode=rightTurn;
			break;
		case (3):
			currPlainNode=leftTurn;
			break;
		case (14):
			currPlainNode=rightFork;
			break;
		case (11):
			currPlainNode=leftFork;
			break;
		case (7):
			currPlainNode=T_crossing;
			break;
		case (15):
			currPlainNode=crossing;
			break;
		default:
			currPlainNode=nowhere;
			break;
	}
}

void patrol_t::switchMode(status_t newMode){
	updateOn=newMode;
}

void patrol_t::setPlainNode(plainNode_t newPlainNode){
	currPlainNode=newPlainNode;
}

void patrol_t::setKeyNode(keyNode_t newKeyNode){
	preKeyNode=newKeyNode;
}

status_t patrol_t::detectPlainNode(plainNode_t newNode)const{
	return (currPlainNode==(uint8_t)newNode);
}

status_t detectNode(patrol_t &patrol,plainNode_t newNode){
	return patrol.detectPlainNode(newNode);
}

__DEBUG status_t patrol_t::printPlainNode(void){
	uint8_t newMsg[]={(uint8_t)(currPlainNode+'0'),'\t'};
	printMsg(newMsg,2);
	return (currPlainNode!=nowhere);
}

