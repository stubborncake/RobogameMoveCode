
#include "path.h"
#include "chassis.h"

#include "motor.h"
#include "tracer.h"
#include "patrol.h"
#include "connectivity.h"

using namespace timeout_nsp;

/* Exported macro ------------------------------------------------------------*/

/*	@brief 当前岔路口的编号，对应enum baselineNode_t.
	其中node_0为基准线的最右端的直角弯.
	node_6为基准线最左边的T字路口
*/
uint8_t baseLineNode=0;
path_t path;

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
	HAL_Delay(startLineWaitingTime);
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
	if(newDir!=dirRight || newDir!= dirLeft){
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
	Rotate180degree();
	WAIT_FOR(tracer[dirFront].exactOnPath==1  || tracer[dirBack].exactOnPath==1,decelerateTime);
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

#ifdef __DEBUG
	waitInStartLine();
#endif
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

/*向前移动，发射冰壶，并退回基准线*/
void path_t::goLaunchCurling(uint8_t launchNode,status_t flag_lastShot){
	/*准备发射*/
	chassis.move(dirFront,speedLow,easyCurlingTakeTime);
	chassis.stop();
	putdownCurling();
	/*一发入魂*/
	chassis.pushCurling(1000);    
    /*退回基准线，如果为最后一次则停止运动*/
	if(flag_lastShot==1){
		return;
	}
    chassis.move(dirBack,speedHigh);
    WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime);
	chassis.stop();
	chassis.raiseArm(down,7);

}

/* Private functions prototypes ---------------------------------------------*/


/*从出发点出发，经过第一个右转弯，无巡线的情况下到达基准线，停止*/
void move_toBaseLine(void);

/*@brief 在基准线上移动到指定的baselineNode,默认此时车头要朝着场地前方
    @param newNode: 移动到的新的节点标号
*/
void move_toNode(uint8_t newNode);

/*向前移动，取回一个低难度的冰壶，并退回基准线*/
void move_takeEasyCurling(void);

/*向前移动，取回一个高难度的冰壶，并退回基准线*/
void move_takeHardCurling(void);

/*向前移动，发射冰壶，并退回基准线*/
void move_lauchCurling(void);

/*  @brief 穿越若干个岔路口,没有使用节点判断
    @param forkCount: 经过的岔路口数量，为1则意味着到下一个岔路口停止
    @param timeout: 最大时间，超过则强制停止，目前尚未使用
    @param speed: 行进速度，默认为高速
    @retval None
    @note 岔路口的定义为任意左右左右fork,turning类的平凡节点
*/
void move_passForks(direction_t newDir,uint8_t forkCount=1,uint8_t speed=speedHigh,uint32_t timeout=timeout_nsp::quiteLongTime);

/* Private functions defines ---------------------------------------------*/

void moveUntilNode(plainNode_t newNode,uint32_t timeout,direction_t newDir,uint8_t speed){
	chassis.move(newDir,speed);
	WAIT_FOR(patrol.detectPlainNode(newNode)==1,timeout);
	chassis.stop();
}

void move_toBaseLine(void){
	using namespace timeout_nsp;
	/*开局等待时间*/
	HAL_Delay(startLineWaitingTime);
	chassis.onTrail=0;
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
	/*到达右转弯并停止*/
	WAIT_FOR(tracer[dirRight].onPath==0,upperTurningTime);
	chassis.move(dirRight,speedLow);
	WAIT_FOR(tracer[dirBack].exactOnPath==1,decelerateTime);
	chassis.stop();
	/*向后移动*/
	chassis.move(dirBack,speedHigh);
	HAL_Delay(guideLineTime);
	/*开始冲刺*/
	chassis.onTrail=0;
	chassis.move(dirBack,superDash,wasteLandTime);
	/*到达基准线*/
	WAIT_FOR(tracer[dirBack].onPath==1,quiteLongTime);
	chassis.move(dirBack,speedLow);	
	WAIT_FOR(tracer[dirLeft].exactOnPath==1 || tracer[dirRight].exactOnPath==1,decelerateTime);/*条件有点强*/
	chassis.stop();
	/*将巡线模块使能，并设置基线节点为node_0*/
	chassis.onTrail=1;
	baseLineNode=lowerRightTurning;
}

void move_toNode(uint8_t newNode){
	/*越界判断*/
	if(newNode>baselineNodeCount){
		return;
	}
	/*TODO:判断车头是否朝前，下一步可以加入两个方向的移动，但是没必要*/
	if(newNode>baseLineNode){
		move_passForks(dirLeft,newNode-baseLineNode);
	}else if(newNode<baseLineNode){
		move_passForks(dirRight,baseLineNode-newNode);		
	}
	baseLineNode=newNode;

}

void move_takeEasyCurling(void){
    /*前进到冰壶面前*/
	chassis.move(dirFront,speedLow,easyCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
    chassis.raiseArm(up,5);
    /*退回到基准线*/
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime/2);
	chassis.stop();

}

void move_takeHardCurling(void){
    /*前进到冰壶面前*/
	chassis.raiseArm(up,5);/*在接近冰壶前需要先将铲子抬高到底座高度，底座的高度为5*/
	chassis.move(dirFront,speedLow,hardCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
    chassis.raiseArm(up,2);/*在底座的高度上再抬高2cm*/

    /*退回到基准线*/
	chassis.move(dirBack,speedHigh);
	WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime);
	chassis.stop();
	chassis.raiseArm(down,2);
}

void move_lauchCurling(void){
	/*准备发射*/
	chassis.move(dirFront,speedLow,easyCurlingTakeTime);
	chassis.stop();
	/*后退一点距离，使得冰壶被放在更接近推杆的位置*/
	chassis.move(dirBack,speedLow,300);
	chassis.stop();
	chassis.raiseArm(down,5);
	chassis.move(dirBack,speedLow,1300);/*确定参数*/
	chassis.stop();
	chassis.raiseArm(up,7);
	chassis.move(dirFront,speedLow,1600);
	chassis.stop();
	/*一发入魂*/
	chassis.pushCurling(1000);    
    /*退回基准线*/
	chassis.raiseArm(down,7);
    chassis.move(dirBack,speedHigh);
    WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,3200);
	chassis.stop();

}

void rotate_180degree(void){
	chassis.onTrail=1;
	chassis.stop();
	chassis.rotate(dirRight,speedHigh);
	HAL_Delay(passingForkTime);
	WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirBack].onPath==1,rotateTime_90degree);
	HAL_Delay(passingForkTime);
	WAIT_FOR(tracer[dirFront].onPath==1 && tracer[dirBack].onPath==1,rotateTime_90degree);
	chassis.rotate(dirRight,speedLow);
	WAIT_FOR(tracer[dirFront].exactOnPath==1  || tracer[dirBack].exactOnPath==1,decelerateTime);
	chassis.stop();
}

void move_passForks(direction_t newDir, uint8_t forkCount,uint8_t speed,uint32_t timeout){
	direction_t relRightDir=getRightDir(newDir);
	direction_t relLeftDir=oppositeDir(relRightDir);
	chassis.move(newDir,speed);
	chassis.onTrail=1;
	/*越界矫正*/
	if(forkCount==0 || forkCount>baselineNodeCount){
		forkCount=1;
	}
	HAL_Delay(passingForkTime);
	/*中间需要跳过的节点*/
	for(uint8_t i=0;i<forkCount-1;i++){
		if(baseLineNode==lowerRightTurning){
			WAIT_FOR(tracer[relRightDir].onPath==1 ||tracer[relLeftDir].onPath==1 ,upperTurningTime);	
		}else{
			WAIT_FOR(tracer[relRightDir].onPath==1 ||tracer[relLeftDir].onPath==1 ,curlingIntervalTime);
		}
		HAL_Delay(passingForkTime);
	}
	if(forkCount==1){
		HAL_Delay(passingForkTime);
		WAIT_FOR(tracer[dirFront].exactOnPath==1,upperTurningTime);
	}else{
		WAIT_FOR(tracer[dirFront].exactOnPath==1,decelerateTime);
	}
	chassis.stop();
}


/* Exported functions defines ---------------------------------------------*/

__DEBUG void testPath_ver2(void){
	using namespace timeout_nsp;

	move_toBaseLine();

	move_toNode(easyCurlingRight_1);

    /*前进到冰壶面前并检测第一个简单冰壶的颜色*/
	chassis.move(dirFront,speedLow,easyCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
	if(chassis.detectCode(3)==1){
    	chassis.raiseArm(up,5);
		chassis.move(dirBack,speedHigh);
		WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime);
		chassis.stop();
		move_toNode(launchRight);
		move_lauchCurling();
	}else{
		chassis.move(dirBack,speedHigh);
		WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,easyCurlingTakeTime);
		chassis.stop();
		move_toNode(easyCurlingRight_2);
		move_takeEasyCurling();
		move_toNode(launchRight);
		move_lauchCurling();

	}
	chassis.stop();	

	/*取第二个简单冰壶*/
	move_toNode(easyCurlingMide);
	move_takeEasyCurling();
	move_toNode(launchRight);
	move_lauchCurling();

	move_toNode(hardCurling_1);
	Rotate180degree();
	chassis.raiseArm(up,5);
	chassis.move(dirFront,speedLow,hardCurlingTakeTime);/*定距离前进去取壶，待定的参数*/
	chassis.stop();
	if(chassis.detectCode(3)==1){
    	chassis.raiseArm(up,2);
		chassis.move(dirBack,speedHigh);
		WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,hardCurlingTakeTime);
		chassis.stop();
		chassis.raiseArm(down,2);
		Rotate180degree();
		move_toNode(launchRight);
		move_lauchCurling();
	}else{
		chassis.move(dirBack,speedHigh);
		WAIT_FOR(tracer[dirRight].exactOnPath || tracer[dirLeft].exactOnPath ,hardCurlingTakeTime);
		chassis.stop();
		move_passForks(dirRight,1);
		move_takeHardCurling();
		Rotate180degree();
		move_toNode(launchRight);
		move_lauchCurling();

	}


	Rotate180degree();
	//rotate_180degree();
	move_takeHardCurling();
	Rotate180degree();
	//rotate_180degree();
	move_toNode(launchLeft);
	move_lauchCurling();
	move_toNode(hardCurling_3);
	Rotate180degree();
	//rotate_180degree();//巡线下的旋转180度
	move_takeHardCurling();
	Rotate180degree();
	//rotate_180degree();//巡线下的旋转180度
	move_toNode(launchLeft);
	move_lauchCurling();

}

__DEBUG void testPath_ver3(void){

	path.testBaselineInit();

	path.gotoBaselineNode(0);
	path.gotoBaselineNode(1);
	path.gotoBaselineNode(3);
	path.gotoBaselineNode(4);
	path.gotoBaselineNode(3);
	path.gotoBaselineNode(5);
	path.gotoBaselineNode(5);

	chassis.stop();
}


__DEBUG void testPath_ver4(void){
	/*前往基准线*/
	path.gotoBaseline();
	/*取第一个简单冰壶并发射*/
	path.gotoBaselineNode(easyCurlingRight_1);
	path.goTakeEasyCurling();
	path.gotoBaselineNode(launchRight);
	path.goLaunchCurling(launchRight);
	/*取第二个简单冰壶并发射*/
	path.gotoBaselineNode(easyCurlingMide);
	path.goTakeEasyCurling();
	path.gotoBaselineNode(launchRight);
	path.goLaunchCurling(launchRight);
	/*取第一个困难冰壶并发射*/
	path.gotoBaselineNode(hardCurling_1);
	path.goTakeHardCurling();
	path.gotoBaselineNode(launchLeft);
	path.goLaunchCurling(launchLeft);
	/*取第二个困难冰壶并发射*/
	path.gotoBaselineNode(hardCurling_2);
	path.goTakeHardCurling();
	path.gotoBaselineNode(launchLeft);
	path.goLaunchCurling(launchLeft,1);

	
}
