
#ifndef __PLAN_H
#define __PLAN_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/


/* Exported constants ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

/*单项调试函数，使用视觉模块*/
__DEBUG void testPath_ver3(void);
/*全程测试函数，为path_t的封装类，已经废弃*/
__DEBUG void testPath_ver4(void);
/*全程测试函数，使用备用方案1，已经被否决*/
__DEBUG void testPath_ver5(void);
/*全程测试函数，使用备用方案2，在开始前将指定线接高压来输入冰壶位置信息，已被否决*/
__DEBUG void testPath_ver6(void);

/* Private defines -----------------------------------------------------------*/

#define __PLAN

#ifdef __cplusplus
}
#endif

#endif	/*__PLAN_H*/
