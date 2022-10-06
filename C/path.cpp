
#include "path.h"
#include "chassis.h"

#include "motor.h"
#include "tracer.h"
#include "patrol.h"/*移除*/

using namespace timeout_nsp;

/* Exported macro ------------------------------------------------------------*/

/*	@brief 当前岔路口的编号，对应enum baselineNode_t.
	其中node_0为基准线的最右端的直角弯.
	node_6为基准线最左边的T字路口
*/
path_t path;

/* Private functions defines ------------------------------------------------------------*/



/*path_t construction &destruction func---------------------------------------------*/

path_t::path_t()
{
	baselineNode=lowerRightTurning;
	flag_Baseline=0;
	chassisHeadingDir=dirNowhere;
}

path_t::~path_t()
{
	baselineNode=lowerRightTurning;
	flag_Baseline=0;
	chassisHeadingDir=dirNowhere;
}

/*path_t private func---------------------------------------------*/

/*在起点等待一段时间*/
void path_t::waitInStartLine(void){
#ifdef __DEBUG
	HAL_Delay(startLineWaitingTime);
#endif
	chassis.onTrail=0;
	flag_Baseline=0;
	chassisHeadingDir=dirFront;
}

/*从起点的正方形区域内离开*/
void path_t::leaveStartLine(void){
	/*前进半步对准线*/
	chassis.move(dirFront,speedHigh);
	WAIT_FOR(tracer[dirLeft].exactOnPath==1 || tracer[dirRight].exactOnPath==1 ,decelerateTime);
	chassis.stop();
	/*离开出发点的正方形的框*/
	chassis.onTrail=1;
	chassis.move(dirRight,speedHigh);
	WAIT_FOR(tracer[dirFront].onPath==1,leavingStartLineTime);
	HAL_Delay(passingForkTime);
	chassis.onTrail=1;
	
}

/*到达上端的右转直角弯*/
void path_t::landonUpperTurning(void){
	WAIT_FOR(tracer[dirRight].onPath==0,upperTurningTime);
	chassis.move(dirRight,speedLow);
	WAIT_FOR(tracer[dirBack].exactOnPath==1,decelerateTime);
	chassis.stop();
}

/*穿越无巡线路径*/
void path_t::gothroughWasteLand(void){
	/*向后移动*/
	chassis.move(dirBack,speedHigh);
	HAL_Delay(guideLineTime);
	/*开始冲刺*/
	chassis.onTrail=0;
	chassis.move(dirBack,superDash,wasteLandTime);	
}

/*抵达基准线*/
void path_t::landonBaseline(void){
	WAIT_FOR(tracer[dirBack].onPath==1,quiteLongTime);
	chassis.move(dirBack,speedLow);	
	WAIT_FOR(tracer[dirLeft].exactOnPath==1 || tracer[dirRight].exactOnPath==1,decelerateTime);/*条件有点强*/
	chassis.stop();
	/*将巡线模块使能，并设置基线节点为node_0*/
	chassis.onTrail=1;
	flag_Baseline=1;
	baselineNode=lowerRightTurning;

}

void path_t::goPassForks(direction_t newDir,uint8_t forkCount){
	/*越界矫正*/
	if(forkCount==0 || forkCount>baselineNodeCount){
		forkCount=1;
	}
	if(newDir!=dirRight && newDir!= dirLeft){
		return;
	}
	/*车子向指定方向前进,并挂起一段时间，确保当前节点不会影响判断*/
	chassis.move(newDir,speedHigh,passingForkTime);
	chassis.onTrail=1;

	/*若forkCount==1，则到达下一个路口就停止,*/
	if(forkCount==1){
		WAIT_FOR(tracer[dirFront].exactOnPath==1 || tracer[dirBack].exactOnPath==1,upperTurningTime);
		chassis.stop();
		return;
	}

	/*中间需要跳过的节点*/
	for(uint8_t i=0;i<forkCount-1;i++){
		if(baselineNode==lowerRightTurning){
			WAIT_FOR(tracer[dirFront].onPath==1 ||tracer[dirBack].onPath==1 ,upperTurningTime);	
		}else{
			WAIT_FOR(tracer[dirFront].onPath==1 ||tracer[dirBack].onPath==1 ,curlingIntervalTime);
		}
		HAL_Delay(passingForkTime);
	}
	/*到达指定的节点*/
	WAIT_FOR(tracer[dirFront].exactOnPath==1 || tracer[dirBack].exactOnPath==1,decelerateTime);
	chassis.stop();
}

/*在十字交叉口上原地旋转180度*/
void path_t::turnBack(direction_t newDir){
	chassis.onTrail=1;
	chassis.stop();
	/*
	chassis.rotate(newDir,speedHigh);
	HAL_Delay(passingForkTime);
	WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirBack].onPath==1,rotateTime_90degree);
	HAL_Delay(passingForkTime);
	WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirBack].onPath==1,rotateTime_90degree);
	chassis.rotate(newDir,speedLow);
	WAIT_FOR(tracer[dirFront].exactOnPath==1  || tracer[dirBack].exactOnPath==1,decelerateTime);
	*/
	Rotate180degree(newDir);
	WAIT_FOR(tracer[dirFront].exactOnPath==1,decelerateTime);
	chassis.stop();

	chassisHeadingDir=oppositeDir(chassisHeadingDir);
}

void path_t::putdownCurling(void){
	chassis.move(dirBack,speedLow,500);
	chassis.stop();
	chassis.raiseArm(down,5);
	chassis.move(dirBack,speedLow,1300);/*确保不会在放下机械臂时碰到冰壶*/
	chassis.stop();
	chassis.raiseArm(up,7);/*确保在发射时推进杆不会撞到机械臂*/
	chassis.move(dirFront,speedLow,2000);/*确保发射时地盘顶住场地柱子*/
	chassis.stop();
}


/*path_t public func---------------------------------------------*/

/*从出发点出发，经过第一个右转弯，无巡线的情况下到达基准线，停止*/
void path_t::gotoBaseline(void){

	waitInStartLine();
	leaveStartLine();
	landonUpperTurning();
	gothroughWasteLand();
	landonBaseline();

}

__DEBUG void path_t::testBaselineInit(void){
	HAL_Delay(startLineWaitingTime);
	chassis.onTrail=1;
	chassisHeadingDir=dirFront;
	baselineNode=lowerRightTurning;
	flag_Baseline=1;
	chassis.stop();
}

/*  @brief 在基准线上移动到指定的baselineNode,默认此时车头要朝着场地前方
	@param newNode: 移动到的新的节点标号
*/
void path_t::gotoBaselineNode(uint8_t newNode){
	/*越界判断*/
	if(newNode>baselineNodeCount){
		return;
	}
	/*车头方向判断*/
	if(chassisHeadingDir!=dirFront){
		return;
	}
	/*是否在基线上的判断*/
	if(flag_Baseline==0){
		return;
	}
	/*计算需要途径的节点数量*/
	if(newNode>baselineNode){
		goPassForks(dirLeft,newNode-baselineNode);
	}else if(newNode<baselineNode){
		goPassForks(dirRight,baselineNode-newNode);		
	}
	baselineNode=newNode;
}

/*向前移动，取回一个低难度的冰壶，并退回基准线*/
void path_t::goTakeEasyCurling(void){
	/*前进到冰壶面前*/
	chassis.move(dirFront,speedLow,easyCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
    chassis.raiseArm(up,5);
    /*退回到基准线*/
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime);
	chassis.stop();

}
/*向前移动，取回一个高难度的冰壶，并退回基准线,TODO确定前进的时间*/
void path_t::goTakeHardCurling(void){

	turnBack(dirRight);
	/*前进到冰壶面前*/
	chassis.raiseArm(up,5);/*在接近冰壶前需要先将铲子抬高到底座高度5cm*/
	chassis.move(dirFront,speedLow,hardCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
    chassis.raiseArm(up,2);/*在底座的高度上再抬高2cm*/

    /*退回到基准线*/
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,hardCurlingTakeTime);
	chassis.stop();
	chassis.raiseArm(down,2);
	turnBack(dirLeft);
}

void trimThenLaunch(direction_t newDir){
	chassis.onTrail=0;
	PushCurlingTrimBack(newDir);
	
	chassis.raiseArm(down,5);

	PushCurlingMoveFrontorBack(dirBack);
	/*此处插入一个抬爪子函数*/
	chassis.raiseArm(up,7);

	PushCurlingMoveFrontorBack(dirFront);
	chassis.pushCurling();

	PushCurlingTrimFront(newDir);
	chassis.onTrail=1;
}


/*向前移动，发射冰壶，并退回基准线*/
void path_t::goLaunchCurling(uint8_t launchNode,status_t flag_trimLaunch,status_t flag_lastShot){
	/*准备发射，确保顶到发射边沿的柱子*/
	chassis.move(dirFront,speedLow,easyCurlingTakeTime);
	chassis.stop();
	/*是否需要偏转发射*/
	if(flag_trimLaunch==0){
		putdownCurling();
		chassis.pushCurling();
	}else{
		if(launchNode==launchRight){
			trimThenLaunch(dirLeft);
		}else{
			trimThenLaunch(dirRight);
		}
	}
    /*退回基准线，如果为最后一次则停止运动TODO*/
	if(flag_lastShot==1){
		//return;
	}
    chassis.move(dirBack,speedHigh);
    WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime);
	chassis.stop();
	chassis.raiseArm(down,7);

}

status_t path_t::goDetectEasyCurling(void){
	status_t flag=0;
	/*前进到冰壶面前*/
	chassis.move(dirFront,speedLow,easyCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
	flag=chassis.detectCode(1);
	if(flag==1){
		chassis.raiseArm(up,5);
	}else{
		//do nothing
	}
	/*退回到基准线*/
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime);
	chassis.stop();
	return flag;
}

status_t path_t::goDetectHardCurling(void){
	status_t flag=0;
	/*前进到冰壶面前*/
	turnBack(dirRight);
	chassis.raiseArm(up,5);
	chassis.move(dirFront,speedLow,hardCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
	flag=chassis.detectCode(1);
	if(flag==1){
		chassis.raiseArm(up,2);
	}else{
		//do nothing
	}
	/*退回到基准线*/
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,hardCurlingTakeTime);
	chassis.stop();
	if(flag==0){
		chassis.raiseArm(down,5);
	}else{
		chassis.raiseArm(down,2);
	}
	turnBack(dirLeft);
	return flag;

}

status_t path_t::detectFatalError(void){
	if(flag_Baseline==0){
		return 0;
	}
	uint8_t tracerDir=chassis.headingDir;
	if(tracerDir!=dirNowhere && tracer[tracerDir].onPath==0){
		return FATAL_ERROR;
	}else{
		return 0;
	}
}

status_t path_t::adjustBacktoTrace(void){
	chassis.stop();

	return 1;
}

status_t path_t::adjustOnCrossing(void){
	chassis.stop();
	chassis.onTrail=1;
	if(tracer[dirFront].exactOnPath==1){
		chassis.move(dirFront,speedHigh,500);
		WAIT_FOR(tracer[dirBack].exactOnPath==1,2000);
		chassis.move(dirBack,speedHigh,500);
		WAIT_FOR(tracer[dirLeft].exactOnPath==1 || tracer[dirRight].exactOnPath==1,2000);
		chassis.stop();		
		return 1;
	}else{

		return 0;
	}
}

/* Private functions defines ---------------------------------------------*/

void moveUntilNode(plainNode_t newNode,uint32_t timeout,direction_t newDir,uint8_t speed){
	chassis.move(newDir,speed);
	WAIT_FOR(patrol.detectPlainNode(newNode)==1,timeout);
	chassis.stop();
}
