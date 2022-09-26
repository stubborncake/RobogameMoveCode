
#include "counter.h"
/* Exported macro ------------------------------------------------------------*/
counter_t counter;

/*counter_t construction &destruction func*/
counter_t::counter_t():interval(intervalDefault)
{
    flag_timeout=0;
    turnOff();
}

counter_t::~counter_t()
{
    turnOff();
}

/*counter_t private func*/

void counter_t::clearData(void){
    prescaler=0;
    tick=0;
}

status_t counter_t::timeUp(void){
    flag_timeout=1;
    turnOff();
    return flag_timeout;
}

/*counter_t public func*/

void counter_t::setup(uint32_t newTimeout){
    flag_timeout=0;
    flag_working=1;
    prescaler=newTimeout;
    tick=0;
}
void counter_t::turnOff(void){
    flag_working=0;
    clearData();
}

void counter_t::updateDate(void){
    if(flag_working==1){
        tick++;
        if(tick>=prescaler){
            timeUp();
        }
    }
}


