
#ifndef __TRACER_H
#define __TRACER_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"
#include "sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/



/* Exported constants ------------------------------------------------------------*/
static const uint8_t sensorCount=5;/*每一个巡线模块有5个传感器*/

/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

#define __TRACER

/* Class defines -----------------------------------------------------------*/

using namespace tracer_nsp;

class tracer_t{
private:
	sensor_t sensor[sensorCount];

	/*是否开启传感器检测*/
	status_t detectOn;
	/*是否开启路径检测*/
	status_t calcStatus;


	/*更新传感器数值*/
	void updateSensorVal(void);
	/*更新tracer的路径检测数值，包括onPath,hitPath,leavePath*/
	void updatePathStatus(void);
	/*重置所有传感器历史数值*/
	void clearSensorVal(void);
	/*重置tracer统计的路线状况*/
	void clearStatus(void);

public:
	/*该tracer是否在线上*/
	status_t onPath;
	/*该tracer是否完美的在线上*/
	status_t exactOnPath;
	/*该tracer是否刚从线外进入到线上*/
	status_t hitPath;
	/*该tracer是否刚从线上离开到线外*/
	status_t leavePath;
	/*取得指定传感器的二值结果*/
	__DEBUG status_t sensorVal(uint8_t order)const;

	tracer_t();
	~tracer_t();

	/*更新tracer所有数值*/
	void updateData(void);	
	/*update()的另一个形式*/
	friend void updateTracer(tracer_t &newTracer);
	/*开启或关闭检测*/
	void detectMode(status_t newStatus=2);

	/*开启或关闭撞线计算*/
	void calcStatusMode(status_t newStatus=2);

	/*更新置信系数，即过程中是否存在传感器失灵的情况,未使用*/
	void setConfCoe(uint8_t sensorOrder,float newConfCoeVal);

	/*判断是否撞线或者离线*/
	friend status_t hittingPath(tracer_t &tracer);
	friend status_t leavingPath(tracer_t &tracer);
	
	/*清空所有数值*/
	void clearData(void);

	/*计算大致偏移角度*/
	int8_t calcTrimDir(void);

	/*调试用函数，输出相关变量*/
	__DEBUG void printNewSensorVal(void)const;
	__DEBUG void printSensorVal(void)const;
	__DEBUG void printPathStatus(void)const;
};

/* Exported macro ------------------------------------------------------------*/

extern tracer_t tracer[];

/* Private defines -----------------------------------------------------------*/

#define __TRACER

#ifdef __cplusplus
}
#endif

#endif	/*__TRACER_H*/
