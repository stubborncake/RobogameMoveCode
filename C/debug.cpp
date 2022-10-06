#include "common.h"
#include "path.h"
#include "chassis.h"
#include "tracer.h"

uint8_t flag_fatalError=0;

#ifdef __DEBUG

#if (BACKUP_PLAN==1)
/*简单区取壶,在到达底线之后*/



#elif(BACKUP_PLAN==2)

uint8_t bp_easyCurlingNode=1;
uint8_t bp_hardCurlingNode_1=3;
uint8_t bp_hardCurlingNode_2=4;

#endif

#else

#endif

