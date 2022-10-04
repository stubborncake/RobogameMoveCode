
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


/* Exported functions prototypes ---------------------------------------------*/


/* Private defines -----------------------------------------------------------*/
#define __DEBUG /*调试用的函数或者变量标记*/

#define STATIC_DEBUG (0) /*让小车在静止时进行调试*/

#define BACKUP_PLAN (1) /*备用方案*/

#if (BACKUP_PLAN==1)

#define EASY_CURLING_NODE_1 (1)
#define HARD_CURLING_NODE_1 (4)
#define HARD_CURLING_NODE_2 (5)

#endif

#define __DEBUG_RESERVED

#ifdef __cplusplus
}
#endif

#endif	/*__DEBUG_H*/
