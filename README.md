# zet6_merge_beta

## @Swayee @stubborncake Team_BlackStar Robogame_USTC_2022

## TODO LIST

- ~~将运动和旋转等chassis相关的函数全部集成到chassis_t的类方法中，去掉中间接口的调用~~
- 测试counter_t的实现效果，并学习函数指针的使用，实现waitFor的函数实现，而不是宏定义
- 测试armRaise类方法的效果，并考虑集成到takeCurling方法中
- 添加更多的注释
- 让所有人的程序同步更新
- ~~将main.c开头的初始化部分封装起来~~
- 测试和respberry的图像识别的通信
- 进一步测试是否能够检测处正确的冰壶
- ~~将PWM更新的操作放到motor.c中，并封装~~
- 完善直线前进时，对于后方tracer的识别返回值的判断
- 测试节点判断功能，即patrol_t的类方法实现
- 更新plainNode的判断逻辑，减小代码容量和计算消耗
- ~~是否需要保留headingFor的整合功能，目前看是用不到的~~

-----

## NOTICE

基本逻辑框架:
- sensor_t * 5 -> tracer_t;
- tracer_t * 4 + selector_t -> patrol_t;
- patrol -> path
- pid -> motor ;
- motor -> chassis;
- path controls chassis_t;

在tim6中断里，需要依次处理：
1. 更新4个tracer的数据；
2. 更新selector的引脚电平；
3. 在50个周期后判断是否需要对前进方向进行微调；
4. 在50个周期后更新一次PWM数据；

在初始化阶段需要进行的包括：
1. cubeMax的硬件配置初始化；
2. PWM开启
3. PID数值初始化
4. 编码器开启
5. uart2空闲接收开启
6. tim3的全局中断开启
7. motor相关的变量初始化
8. tracer_t的类对象初始化
9. chassis_t的类对象初始化，即集成motor相关函数(TODO)；
10. 等待，发送uart3一段测试信息，蜂鸣器叫一声；
11. 进入预设的测试函数，或者进入无限循环挂机；

---------
