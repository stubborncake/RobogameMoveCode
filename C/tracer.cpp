
#include "tracer.h"
/* Exported macro ------------------------------------------------------------*/

tracer_t tracer[directionCount];

/* Exported functions definens ---------------------------------------------*/


/* Class construction & destruction functions defines ---------------------------------------------*/


/*tracer_t construction &destruction func*/

tracer_t::tracer_t(){
	clearData();
}

tracer_t::~tracer_t(){
	clearData();
}

/*tracer_t private func*/

void tracer_t::updateSensorVal(void){
  #define PORT(__order__) (SENSOR##__order__##_GPIO_Port)
  #define PIN(__order__)  (SENSOR##__order__##_Pin)
  using namespace tracer_nsp;
  sensor[L2].updateData(PORT(0),PIN(0));
  sensor[L1].updateData(PORT(1),PIN(1));
  sensor[M ].updateData(PORT(2),PIN(2));
  sensor[R1].updateData(PORT(3),PIN(3));
  sensor[R2].updateData(PORT(4),PIN(4));

  #undef PORT
  #undef PIN
}

void tracer_t::updatePathStatus(void){
  using namespace tracer_nsp;

  status_t preOnPath=onPath;
  /*判读是否在线上*/
  if(sensorVal(R1)+sensorVal(M)+sensorVal(L1)+sensorVal(R2)+sensorVal(L2)>=3){    
    onPath=1;
  }else{
    onPath=0;
  }
  /*判断是否完美的在线上*/
  if(sensorVal(R1)+sensorVal(M)+sensorVal(L1)==3 && sensorVal(R2)+sensorVal(L2)==0){
    exactOnPath=1;
  }else{
    exactOnPath=0;
  }

  if(preOnPath==1 && onPath==0){
    leavePath=1;
  }else{
    leavePath=0;
  }
  if(preOnPath==0 && onPath==1){
    hitPath=1;
  }else{
    hitPath=0;
  }

}

void tracer_t::clearSensorVal(void){
  for(uint8_t i=0;i<sensorCount;i++){
    sensor[i].clearData();
  }
}

void tracer_t::clearStatus(void){
	onPath=0;
  exactOnPath=0;
  hitPath=0;
  leavePath=0;
}

/*tracer_t public func*/

status_t tracer_t::sensorVal(uint8_t order)const{
  if(order<sensorCount){
    return sensor[order].getValBinary();
  }else{
    return (status_t)(-1);
  }
}

void tracer_t::updateData(void){
  if(detectOn==on){
    updateSensorVal();
  }
  if(calcStatus==on){
    updatePathStatus();
  }  

}

void updateTracer(tracer_t &newTracer){
  newTracer.updateData();
}

void tracer_t::detectMode(status_t newStatus){
  /*默认传入参数为2，即为切换当前模式*/
  if(newStatus>=2){
    detectOn=!detectOn;
  }else{
    detectOn=newStatus;
  }
  clearSensorVal();
}

void tracer_t::calcStatusMode(status_t newStatus){
  /*默认传入参数为2，即为切换当前模式*/
  if(newStatus>=2){
    calcStatus=!calcStatus;
  }else{
    calcStatus=newStatus;
  }
  clearStatus();
}

void tracer_t::setConfCoe(uint8_t sensorOrder,float newConfCoeVal){
  if(sensorOrder<sensorCount){
    sensor[sensorOrder].setConfCoe(newConfCoeVal);
  }
}

status_t hittingPath(tracer_t &tracer){
  return tracer.leavePath;
}

status_t leavingPath(tracer_t &tracer){
  return tracer.hitPath;
}

void tracer_t::clearData(void){
  clearSensorVal();
  clearStatus();
}

int8_t tracer_t::calcTrimDir(void){
  using namespace tracer_nsp;
  int8_t trimDir=0;
  /*如果在线上且没有完全在线上*/
  if(onPath==1 && exactOnPath==0){
    if(sensorVal(L1)==whiteParcel)
      trimDir++;
    if(sensorVal(R2)==blackParcel)
      trimDir+=2;
    if(sensorVal(R1)==whiteParcel)
      trimDir--;
    if(sensorVal(L2)==blackParcel)
      trimDir-=2;
  }
  return trimDir;
}

__DEBUG void tracer_t::printNewSensorVal(void)const{
  uint8_t newMsg[sensorCount]={0};
  for(uint8_t i=0;i<sensorCount;i++){
    newMsg[i]='0'+sensor[i].getNewVal();
  }
  printMsg(newMsg,sensorCount);
}

__DEBUG void tracer_t::printSensorVal(void)const{
  static const uint8_t msgSize=sensorCount+1;
  uint8_t newMsg[msgSize]={0};
  for(uint8_t i=0;i<sensorCount;i++){
    newMsg[i]='0'+sensorVal(i);
  }
  newMsg[sensorCount]='\t';
  printMsg(newMsg,msgSize);
}

__DEBUG status_t tracer_t::readSensorVal(uint8_t order)const{
  return sensorVal(order);
}


/* Private functions defines ---------------------------------------------*/
