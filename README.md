# zet6_merge_beta

## @Swayee @stubborncake TeamBlackStar_Robogame

基本逻辑框架:

sensor_t * 5 -> tracer_t;

tracer_t * 4 + selector_t -> patrol_t;

patrol controls motor ;

pid -> motor ;

motor -> chassis;

在tim6中断里，需要依次处理：
1. 更新4个tracer的数据；
2. 更新selector的引脚电平；
3. 在50个周期后发送一次对运动模块的函数调用,例如前进，或者停止，或者旋转等；
4. 更新decoder的数据（什么意思我看不懂）
