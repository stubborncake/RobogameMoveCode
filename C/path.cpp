
#include "path.h"
#include "chassis.h"

#include "motor.h"
#include "tracer.h"
#include "patrol.h"
#include "connectivity.h"

using namespace timeout_nsp;

/* Exported macro ------------------------------------------------------------*/

/* Private functions defines ---------------------------------------------*/

/* Exported functions defines ---------------------------------------------*/

status_t leaveStartLine(void){
  chassis.onTrail=1;
  HAL_Delay(5000);
  chassis.move(dirFront,speedHigh);
  HAL_Delay(2000);
  return 1;
}

status_t makeTurn(direction_t newDir,plainNode_t newNode,uint32_t timeout){
	chassis.move(dirFront,speedHigh);

	WAIT_FOR(tracer[dirRight].readSensorVal(tracer_nsp::R1)==blackParcel ||\
		tracer[dirRight].readSensorVal(tracer_nsp::R2)==blackParcel,quiteLongTime);
	chassis.stop();
	chassis.rotate(newDir);
	//最基本的旋转结束判断,TODO:根据当前节点来设置判断条件
	if(newNode==rightTurn){
		WAIT_FOR(tracer[dirFront].readSensorVal(L1)==blackParcel && \
			tracer[dirRight].readSensorVal(L1)==blackParcel ,quiteLongTime);
	}else if(newNode==horizontalLine){
		WAIT_FOR(tracer[dirFront].readSensorVal(L1)==blackParcel && \
			tracer[dirBack].readSensorVal(L1)==blackParcel ,quiteLongTime);
	}
	chassis.stop();
	chassis.move(dirFront,speedHigh);
	HAL_Delay(500);
	return 1;
}

status_t turnRight(plainNode_t newNode,uint32_t timeout){
	return makeTurn(dirRight,newNode,timeout);
}

status_t turnLeft(plainNode_t newNode,uint32_t timeout){
	return makeTurn(dirLeft,newNode,timeout);
}


status_t goThroughWasteLand(uint32_t timeout){
  chassis.move(dirFront,speedHigh);
  WAIT_FOR(tracer[dirFront].onPath==0,wasteLandTime);
  chassis.onTrail=0;
  chassis.move(dirFront,superDash);
  //借由路过的曲线顶点为参照，或者干脆通过预设延迟来抵达最下端的路径线
  HAL_Delay(timeout);

  WAIT_FOR(hittingPath(tracer[dirFront]),quiteLongTime);
  chassis.move(dirFront,speedLow);
  turnRight(horizontalLine,quiteLongTime);
  return 1;
}

status_t gotoLaunchNode(void){
	for(uint8_t i=0;i<3;i++){
  	WAIT_FOR(tracer[dirRight].onPath==1,quiteLongTime);
		HAL_Delay(1500);
	}
	turnRight(crossing,quiteLongTime);
	HAL_Delay(2000);

	return 1;
}


status_t gotoBaseNode(keyNode_t preKeyNode,uint32_t timeout){
	switch (preKeyNode)
	{
	case lowerRightTurning:
		chassis.move(dirFront,speedHigh);

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
	WAIT_FOR(leavingPath(tracer[dirFront]),timeout);
	chassis.move(dirFront,speedLow);
	//WAIT_FOR(detectNode(patrol,T_crossing),decelerateTime);
	WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirBack].onPath==1,quiteLongTime);
	chassis.stop();
	chassis.rotate(dirRight);
	WAIT_FOR(hittingPath(tracer[dirLeft]),quiteLongTime);
	chassis.stop();
	return 1;
}

status_t gotoCurlingDeposit(void){
	turnRight(crossing,timeoutMax);
	WAIT_FOR(0,curlingDepositeTime);

	return 1;
}

__DEBUG void testPath(void){
	/*测试阶段保留代码，下一步均调用chassis_t中集成的功能实现TODO:*/
	using namespace tracer_nsp;
	HAL_Delay(5000);
	chassis.onTrail=1;
	chassis.move(dirRight,speedHigh);
	WAIT_FOR(tracer[dirBack].readSensorVal(R2)==blackParcel &&\
		tracer[dirBack].readSensorVal(R1)==blackParcel,quiteLongTime);
	chassis.stop();
	chassis.move(dirBack,superDash);
	chassis.onTrail=0;

	HAL_Delay(wasteLandTime);
	WAIT_FOR(tracer[dirBack].readSensorVal(M)==blackParcel,quiteLongTime);
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirLeft].readSensorVal(M)==blackParcel && \
				tracer[dirRight].readSensorVal(M)==blackParcel,quiteLongTime);
	chassis.stop(500);

	chassis.onTrail=1;
	chassis.rotate(dirLeft,speedLow);
	WAIT_FOR(tracer[dirLeft].readSensorVal(R1)==blackParcel && \
			tracer[dirLeft].readSensorVal(M)==blackParcel && \
			tracer[dirLeft].readSensorVal(L1)==blackParcel,500);
	chassis.stop();
	chassis.move(dirLeft,speedHigh);
	HAL_Delay(2000);
	WAIT_FOR(tracer[dirFront].readSensorVal(M)==blackParcel &&\
			tracer[dirFront].readSensorVal(R1)==blackParcel,quiteLongTime);
	chassis.stop();
	chassis.move(dirFront,speedHigh);
	
	HAL_Delay(1000);


	return;
	/*
	leaveStartLine();
	patrol.setKeyNode(startLine);

	WAIT_FOR(tracer[dirRight].readSensorVal(tracer_nsp::R2)==blackParcel,quiteLongTime);
	chassis.stop();
	chassis.move(dirRight,superDash);
	HAL_Delay(wasteLandTime);
	WAIT_FOR(tracer[dirFront].readSensorVal(tracer_nsp::L2)==blackParcel,quiteLongTime);
	chassis.stop();
	chassis.move(dirBack,speedHigh);
	HAL_Delay(5000);


	turnRight(rightTurn,quiteLongTime);
	patrol.setKeyNode(upperRightTurning);

	goThroughWasteLand(wasteLandTime);
	patrol.setKeyNode(lowerRightTurning);

	gotoLaunchNode();
	patrol.setKeyNode(launchNode);
	//patrol.setKeyNode(baseNode);
*/
}

__DEBUG void testPath_ver2(void){
	using namespace timeout_nsp;
	HAL_Delay(startLineWaitingTime);
	chassis.onTrail=1;
	chassis.move(dirRight,speedHigh);

	WAIT_FOR(tracer[dirRight].onPath==0,quiteLongTime);
	chassis.move(dirRight,speedLow);	
	WAIT_FOR(tracer[dirBack].exactOnPath==1,decelerateTime);/*条件有点强*/
	chassis.stop();
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirBack].onPath==0,quiteLongTime);
	chassis.onTrail=0;

	HAL_Delay(wasteLandTime);
	WAIT_FOR(tracer[dirBack].onPath==1,quiteLongTime);
	chassis.move(dirBack,speedLow);	
	WAIT_FOR(tracer[dirLeft].exactOnPath==1 || tracer[dirRight].exactOnPath==1,decelerateTime);/*条件有点强*/
	chassis.stop();

	chassis.onTrail=1;
	chassis.move(dirLeft,speedHigh);
	WAIT_FOR(tracer[dirFront].onPath==1,quiteLongTime);
	chassis.stop();
	chassis.move(dirFront,speedLow);
	HAL_Delay(curlingDepositeTime);
}


