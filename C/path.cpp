
#include "path.h"

#include "motor.h"
#include "tracer.h"
#include "patrol.h"
#include "connectivity.h"

using namespace timeout_nsp;

/* Exported macro ------------------------------------------------------------*/
uint8_t headingDir=dirNowhere;
status_t onTrail=0;

/*最基本的运动函数最好被封装好，不需要被extern.
TODO:返回状态status_t以表示参数是否符合定义，
例如在运动时发送了旋转指令，需要被识别到*/

/* Private functions defines ---------------------------------------------*/
/*向指定方向，以指定速度运动*/
void chassisMove(direction_t newDir,uint8_t targetSpeed=speedHigh){
	if(newDir==dirNowhere || newDir==dirAll)
		return;
	headingDir=newDir;
	Move(newDir,targetSpeed);
}
/*静止状态下向左或者向右旋转，以指定速度*/
void chassisRotate(direction_t newDir,uint8_t targetSpeed=speedHigh){
	if(headingDir!=dirNowhere)
		return;
	if(newDir==dirRight || newDir==dirLeft){
    	Rotate(newDir,targetSpeed);
	}
}
/*在行进过程中，微调前进方向，目前仅支持向前行进时调整方向，
	TODO:横向移动的还没写，向后移动时，输入相反参数即可*/
void chassisTrim(direction_t newDir,uint8_t trimIntensity){
	if(headingDir==dirNowhere)
		return;
	if(onTrail==0)
		return;
	//根据前进方向的不同发送不同的trim指令，或者在从机那边接收TODO:
	if(newDir==dirRight || newDir==dirLeft){
		Trim(newDir,speedHigh,trimIntensDefault);
	}else if(newDir==dirFront){
		Move(dirFront,speedHigh);
	}
}
/*急刹指令，在任意速度运动时停止*/
void chassisStop(uint8_t stopIntensity=1){
	headingDir=dirNowhere;
	Stop();
}

/* Exported functions defines ---------------------------------------------*/

status_t leaveStartLine(void){
  onTrail=1;
  HAL_Delay(5000);
  chassisMove(dirFront,speedHigh);
  HAL_Delay(2000);
  return 1;
}

status_t makeTurn(direction_t newDir,plainNode_t newNode,uint32_t timeout){
	chassisMove(dirFront,speedHigh);
	if(newNode==rightTurn || newNode==T_crossing || newNode==leftFork){
		WAIT_FOR(tracer[dirFront].onPath==0,timeout);
		chassisMove(dirFront,speedLow);
	}

	//WAIT_FOR(detectNode(patrol,newNode),timeoutMax);
	WAIT_FOR(tracer[dirRight].readSensorVal(tracer_nsp::R1)==blackParcel ||\
		tracer[dirRight].readSensorVal(tracer_nsp::R2)==blackParcel,quiteLongTime);
	chassisStop();
	chassisRotate(newDir);
	//最基本的旋转结束判断,TODO:根据当前节点来设置判断条件
	WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirRight].onPath==1 ,quiteLongTime);
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
  WAIT_FOR(tracer[dirFront].onPath==0,wasteLandTime);
  onTrail=0;
  chassisMove(dirFront,superDash);
  //借由路过的曲线顶点为参照，或者干脆通过预设延迟来抵达最下端的路径线
  HAL_Delay(timeout);

  WAIT_FOR(hittingPath(tracer[dirFront],dirFront),quiteLongTime);
	//WAIT_FOR(tracer[dirFront].readSensorVal(tracer_nsp::M)==blackParcel,quiteLongTime);
  chassisMove(dirFront,speedLow);
  WAIT_FOR(tracer[dirRight].onPath==1 || tracer[dirLeft].readSensorVal(tracer_nsp::M)==blackParcel ,decelerateTime);
	//WAIT_FOR(tracer[dirRight].readSensorVal(tracer_nsp::M)==blackParcel,quiteLongTime);
	

	//抵达底线的判定
	//WAIT_FOR(detectNode(patrol,horizontalLine),timeout);

  chassisStop();
  chassisRotate(dirRight);
  //判断旋转完毕
  WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirBack].onPath==1,quiteLongTime);
  //WAIT_FOR(tracer[dirFront].readSensorVal(tracer_nsp::M)==blackParcel,rotateTime_90degree);
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
	//WAIT_FOR(detectNode(patrol,T_crossing),decelerateTime);
	WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirBack].onPath==1,quiteLongTime);
	chassisStop();
	chassisRotate(dirRight,speedHigh);
	WAIT_FOR(hittingPath(tracer[dirLeft],dirRight),quiteLongTime);
	chassisStop();
	return 1;
}

status_t gotoCurlingDeposit(void){
	turnRight(crossing,timeoutMax);
	WAIT_FOR(0,timeout_nsp::curlingDepositeTime);


	return 1;
}

__DEBUG void testPath(void){
	leaveStartLine();
	patrol.setKeyNode(startLine);

	turnRight(rightTurn,quiteLongTime);
	patrol.setKeyNode(upperRightTurning);

	chassisMove(dirFront,speedHigh);
	HAL_Delay(1000);

	goThroughWasteLand(wasteLandTime);
	patrol.setKeyNode(lowerRightTurning);

	gotoBaseNode(lowerRightTurning,quiteLongTime);
	patrol.setKeyNode(baseNode);

}

__DEBUG void testCurlingTake(void){

}

