

#ifndef __SENSOR_H
#define __SENSOR_H

/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif
	
static const float valThreholdDefault=0.6;
static const uint8_t valCacheMaxDefault=5;
static const float confidenceCoeMaxDefault=1;/*old version of class tracer_t required*/

class sensor_t
{
private:
	const float valThrehold;

	/*检测得到的新的二值*/
	status_t newSensorVal;
	/*历史数值缓存区，为循环队列*/
	status_t valCache[valCacheMaxDefault];
	/*缓存区指针*/
	uint8_t cachePtr;
	/*历史平均值*/
	float valAverage;
	/*置信系数*/
	float confidenceCoe;
	/*返回的二值*/
	status_t valBinary;

	/*瞬时测得的传感器数值*/
	void getNewVal(GPIO_TypeDef *gpioPort,uint16_t pin);
	/*更新缓存区*/
	void updateCache(void);
	/*更新历史平均数值*/
	void updateValAverage(void);
	/*更新历史平均数值的二值化结果*/
	void updateValBinary(void);
	/*清空缓存区*/
	void clearCache(void);


public:
	sensor_t(float newCoe=1);
	~sensor_t();

	/*更新所有数据*/
	status_t updateData(GPIO_TypeDef *gpioPort,uint16_t pin);
	/*取得二值化的数据*/
	status_t getValBinary(void)const;
	/*设置该传感器的置信系数*/
	void setConfCoe(float newCoe=1);
	/*清空所有数值*/
	void clearData(void);
	/*取得最近一次的检测值*/
	__DEBUG status_t getNewVal(void)const;
};

#define __SENSOR
	
#ifdef __cplusplus
}
#endif

#endif	/*__SENSOR_H*/
