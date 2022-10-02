
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

__DEBUG void testPath_ver2(void){
	using namespace timeout_nsp;

#ifdef __DEBUG
	HAL_Delay(startLineWaitingTime);
	chassis.onTrail=0;	
	chassis.move(dirRight,speedHigh);
	WAIT_FOR(tracer[dirFront].onPath==1,leavingStartLineTime);
	HAL_Delay(500);
	chassis.onTrail=1;

	WAIT_FOR(tracer[dirRight].onPath==0,upperTurningTime);
	chassis.move(dirRight,speedLow);
	WAIT_FOR(tracer[dirBack].onPath==0,decelerateTime);
	HAL_Delay(100);
	chassis.stop();

	chassis.move(dirBack,speedHigh);
	HAL_Delay(1500);
	chassis.onTrail=0;
	chassis.move(dirBack,superDash);

	HAL_Delay(wasteLandTime);
	WAIT_FOR(tracer[dirBack].onPath==1,quiteLongTime);
	chassis.move(dirBack,speedLow);	
	WAIT_FOR(tracer[dirLeft].exactOnPath==1 || tracer[dirRight].exactOnPath==1,decelerateTime);/*条件有点强*/
	chassis.stop();
#endif
	/*从wasteLand进入基准线*/
	HAL_Delay(2000);
	chassis.onTrail=1;
	
	WAIT_FOR(tracer[dirFront].sensorVal(L2)==1,upperTurningTime);
	chassis.move(dirLeft,20);
	WAIT_FOR(tracer[dirFront].exactOnPath==1,decelerateTime);
	chassis.stop();

	/*在取壶区的移动*/

	chassis.move(dirFront,speedLow);
	HAL_Delay(3000);/*定距离前进去取壶，很艰难的参数*/
	chassis.stop();
	chassis.takeCurling();
	chassis.move(dirBack,speedLow);
	WAIT_FOR(tracer[dirRight].exactOnPath && tracer[dirLeft].exactOnPath ,3500);/*退回基准线*/
	HAL_Delay(300);
	chassis.stop();
	chassis.move(dirLeft,speedHigh);
	WAIT_FOR(tracer[dirFront].onPath==1,5000);
	HAL_Delay(1000);
	WAIT_FOR(tracer[dirFront].exactOnPath==1,5000);
	chassis.stop();
	chassis.move(dirFront,speedLow);
	HAL_Delay(2500);
	chassis.stop();

	chassis.raiseArm(down,5);

}


