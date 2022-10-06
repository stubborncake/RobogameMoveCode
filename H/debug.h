
#ifndef __DEBUG_H
#define __DEBUG_H
/* Private includes ----------------------------------------------------------*/
#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/


/* Exported constants ------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

extern uint8_t flag_fatalError;

/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/

#define FATAL_ERROR (1)

#define STATIC_DEBUG (0) /*让小车在静止时进行调试*/

#define BACKUP_PLAN (0) /*备用方案*/

#if(BACKUP_PLAN==0)

    #define VISION_MODULE (1)

#elif (BACKUP_PLAN==1)

    #define EASY_CURLING_NODE_1 (2)
    #define HARD_CURLING_NODE_1 (3)
    #define HARD_CURLING_NODE_2 (5)

#elif(BACKUP_PLAN==2)

    extern uint8_t bp_easyCurlingNode;
    extern uint8_t bp_hardCurlingNode_1;
    extern uint8_t bp_hardCurlingNode_2;

#endif

#define __DEBUG /*调试用的函数或者变量标记*/

#ifdef __cplusplus
}
#endif

#endif	/*__DEBUG_H*/
