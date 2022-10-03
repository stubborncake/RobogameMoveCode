
#ifndef __PATH_H
#define __PATH_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"
#include "patrol.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/



/* Exported constants ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/*  @brief 移动到指定平凡节点并停止
    @note 平凡节点检测软件层面目前无法实现
*/
void moveUntilNode(plainNode_t newNode,uint32_t timeout,direction_t newDir,uint8_t speed=speedHigh);

/*全程测试函数,被主函数调用*/
__DEBUG void testPath_ver2(void);
/*单项调试函数，同样为主函数调用*/
__DEBUG void testPath_ver3(void);
/* Private defines -----------------------------------------------------------*/

/* Class defines -----------------------------------------------------------*/



/* Exported macro ------------------------------------------------------------*/

extern uint8_t baseLineNode;


#define __PATH

#ifdef __cplusplus
}
#endif

#endif	/*__PATH_H*/
