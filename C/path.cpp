
#include "path.h"
#include "tracer.h"
#include "patrol.h"
#include "connectivity.h"

using namespace timeout_nsp;

/* Exported macro ------------------------------------------------------------*/
uint8_t headingDir=dirNowhere;
status_t onTrail=0;

/* Private functions prototypes ---------------------------------------------*/
/*最基本的运动函数最好被封装好，不需要被extern.
TODO:返回状态status_t以表示参数是否符合定义，
例如在运动时发送了旋转指令，需要被识别到*/
/*再封装好后和zet6上原本的运动函数对接*/
/*向指定方向，以指定速度运动*/
void chassisMove(direction_t newDir,uint8_t targetSpeed=speedHigh);
/*静止状态下向左或者向右旋转，以指定速度*/
void chassisRotate(direction_t newDir,uint8_t targetSpeed=speedHigh);
/*在行进过程中，微调前进方向，目前仅支持向前行进时调整方向，
	TODO:横向移动的还没写，向后移动时，输入相反参数即可*/
void chassisTrim(direction_t newDir,uint8_t trimIntensity=1);
/*急刹指令，在任意速度运动时停止*/
void chassisStop(uint8_t stopIntensity=1);

/* Private functions defines ---------------------------------------------*/

void chassisMove(direction_t newDir,uint8_t targetSpeed){
	if(newDir==dirNowhere || newDir==dirAll)
		return;
	headingDir=newDir;
    //chassisMoveCmd(newDir,targetSpeed);
}

void chassisRotate(direction_t newDir,uint8_t targetSpeed){
	if(headingDir!=dirNowhere)
		return;
	if(newDir==dirRight || newDir==dirLeft){
    	//chassisRotateCmd(newDir,targetSpeed);
	}
}

void chassisTrim(direction_t newDir,uint8_t trimIntensity){
	if(headingDir==dirNowhere)
		return;
	if(onTrail==0)
		return;
	//根据前进方向的不同发送不同的trim指令，或者在从机那边接收TODO:
	if(newDir==dirRight || newDir==dirLeft){
    	//chassisTrimCmd(newDir,trimIntensity);
	}
}

void chassisStop(uint8_t stopIntensity){
	headingDir=dirNowhere;
    //chassisStopCmd(stopIntensity);
}

/* Exported functions defines ---------------------------------------------*/

status_t leaveStartLine(void){
  onTrail=1;
  chassisMove(dirFront,speedHigh);
  HAL_Delay(2000);
  return 1;
}

status_t makeTurn(direction_t newDir,plainNode_t newNode,uint32_t timeout){
	chassisMove(dirFront,speedHigh);
	if(newNode==rightTurn || newNode==T_crossing || newNode==leftFork){
		WAIT_FOR(leavingPath(tracer[dirFront],dirFront),timeout);
		chassisMove(dirFront,speedLow);
	}
	WAIT_FOR(detectNode(patrol,newNode),decelerateTime);
	chassisStop();
	chassisRotate(newDir);
	//最基本的旋转结束判断,TODO:根据当前节点来设置判断条件
	WAIT_FOR(hittingPath(tracer[dirFront],newDir),rotateTime_90degree);
	chassisStop();
	chassisMove(dirFront,speedHigh);
	return 1;
}

status_t turnRight(plainNode_t newNode,uint32_t timeout){
	return makeTurn(dirRight,newNode,timeout);
}

status_t turnLeft(plainNode_t newNode,uint32_t timeout){
	return makeTurn(dirLeft,newNode,timeout);
}


status_t goThroughWasteLand(uint32_t timeout){
	chassisMove(dirFront,speedHigh);
  WAIT_FOR(leavingPath(tracer[dirFront],dirFront),timeoutDefault);
  onTrail=0;
  chassisMove(dirFront,superCharge);
  //借由路过的曲线顶点为参照，或者干脆通过预设延迟来抵达最下端的路径线
  HAL_Delay(timeout);

  WAIT_FOR(hittingPath(tracer[dirFront],dirFront),timeoutDefault);
  chassisMove(dirFront,speedLow);
  WAIT_FOR(hittingPath(tracer[dirRight],dirLeft),decelerateTime);
	//抵达底线的判定
	//WAIT_FOR(detectNode(patrol,horizontalLine),timeout);

  chassisStop();
	chassisRotate(dirRight);
  //判断旋转完毕
  WAIT_FOR(hittingPath(tracer[dirFront],dirRight),rotateTime_90degree);
  //WAIT_FOR((tracer[dirFront].onPath && tracer[dirRight].onPath),timeoutDefault);
  chassisStop();
  onTrail=1;
  chassisMove(dirFront,speedHigh);
  return 1;

}

status_t gotoBaseNode(keyNode_t preKeyNode,uint32_t timeout){
	switch (preKeyNode)
	{
	case lowerRightTurning:
		chassisMove(dirFront,speedHigh);

		break;
	case curlingDepositEasy:

		break;
	case curlingDepositHard:

		break;
	case launchNode:

		break;
	default:
		return 0;
	}
	WAIT_FOR(leavingPath(tracer[dirFront],dirFront),timeout);
	chassisMove(dirFront,speedLow);
	WAIT_FOR(detectNode(patrol,T_crossing),decelerateTime);
	chassisStop();
	chassisRotate(dirRight,speedHigh);
	WAIT_FOR(hittingPath(tracer[dirLeft],dirRight),rotateTime_180degree);
	chassisStop();
	return 1;
}

__DEBUG void testPath(void){
	leaveStartLine();
	patrol.setKeyNode(startLine);

	turnRight(rightTurn,timeoutDefault);
	patrol.setKeyNode(upperRightTurning);

	chassisMove(dirFront,speedHigh);
	HAL_Delay(1000);

	return;
/*
	goThroughWasteLand(wasteLandTime);
	patrol.setKeyNode(lowerRightTurning);

	gotoBaseNode(lowerRightTurning,timeoutDefault);
	patrol.setKeyNode(baseNode);
	*/
}


