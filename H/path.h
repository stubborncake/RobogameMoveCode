
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

/*从起跑线离开的阶段*/
status_t leaveStartLine(void);
/*直角弯旋转的原子指令*/
status_t makeTurn(direction_t newDir,plainNode_t newNode,uint32_t timeout);
/*向右旋转90度*/
status_t turnRight(plainNode_t newNode,uint32_t timeout=timeoutDefault);
/*向左旋转90度*/
status_t turnLeft(plainNode_t newNode,uint32_t timeout=timeoutDefault);
/*穿过弯曲巡线的阶段*/
status_t goThroughWasteLand(uint32_t timeout=timeoutDefault);
/*从不同的节点返回到基地节点，即坐下角的T子路口节点*/
/*TODO:根据当前不同的节点分别进行寻径，
即整合从lowerRightTurn,curlingDeposit等节点返回的功能*/
status_t gotoBaseNode(keyNode_t preKeyNode,uint32_t timeout=timeoutDefault);

/*测试寻径函数,被主函数调用*/
__DEBUG void testPath(void);

/* Private defines -----------------------------------------------------------*/

/* Class defines -----------------------------------------------------------*/



/* Exported macro ------------------------------------------------------------*/

#define __PATH

#ifdef __cplusplus
}
#endif

#endif	/*__PATH_H*/
