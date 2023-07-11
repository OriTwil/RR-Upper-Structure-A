# RR-Upper-Structure-A
2023 ROBOCON RR Upper Structure ported to F427 MCU
## "Rabbit Robot"
<image src="https://github.com/OriTwil/RR-Upper-Structure-A/blob/main/image/xmind-rr.png" width="1000">
<image src="https://github.com/OriTwil/RR-Upper-Structure-A/blob/main/image/mavlink-rr.png" width="1000">
  
## Version History
- 2023.4.29 Create the project and complete the basic framework.
- 2.23.4.30 Basically complete the task
- 5.14 完成框架
- 5.17 基本完成，还需要设计遥控器方面内容

## Tips
- 双击workspace进入工作区
- 移植只需要复制UserCode文件夹
- RR使用两块主板，这个工程是上层机构
  
## Result
- 5.16 电机速度规划
  <image src="https://github.com/OriTwil/RR-Upper-Structure-A/blob/main/image/speed-planning.jpg" width="1000">

## 主板A

- 主函数：usermain
- 状态机 (State Machine)
  - 手动模式：通过摇杆控制底盘移动
  - 自动模式：通过上位机规划底盘的目标点位，并依次执行
  - 锁死模式：使用反馈控制将底盘锁死在当前位置
- 伺服系统 (Servo)
  - 底盘解算与闭环控制
- 感知模块 (Perception)
  - 感知模式：以一定频率接收传感器信息并更新数据
  - 校正模式：根据校正方案更新传感器数据，完成后恢复自动模式
- 通信模块 (Communication)
  - 以一定频率向上位机、主板B和遥控器发送MAVLINK消息，并接收它们的MAVLINK消息
- 状态管理 (State Management)
  - 根据遥控器按键组合进行状态切换

## 主板B
- 主函数：usermain
- 伺服系统 (Servo)
  - 以一定频率进行伺服控制
- 状态机 (State Machine)
  - Ready模式：初始状态，等待命令
  - Pickup模式：完成不同层环的拾取任务
    - Overturn：翻转环
      - 第一个环
      - 第二个环
      - ...
    - Clamp：夹持环
    - Overturn_back：翻转回位
    - Release：释放环
  - Fire模式：完成不同点到不同柱子的射环任务，射环后进入Ready模式
    - 射环点1
      - 目标柱子1
      - 目标柱子2
      - ...
    - 射环点2
      - 目标柱子1
      - 目标柱子2
      - ...
    - 射环点3
    - 射环点4
- 通信模块 (Communication)
  - 接收主板A的MAVLINK消息，并以一定频率向主板A发送MAVLINK消息
- 状态管理 (State Management)
  - 根据遥控器按键组合进行状态切换

## MAVLINK通信协议

- 主控A到上位机
  - 通道0
    - id = 9：上位机到主板A
    - id = 10：主板A到上位机
- 主控A到主控B
  - 通道1
    - id = 11：主板A到主板B
    - id = 12：主板B到主板A
- 主控A到遥控器
  - 通道2
    - 根据遥控器设定

## 贡献者

感谢以下贡献者对本项目的支持和贡献。

- 贡献者1
- 贡献者2
- ...

## 许可证

本项目使用 [MIT许可证](LICENSE) 进行授权。详情请参阅许可证文件。

