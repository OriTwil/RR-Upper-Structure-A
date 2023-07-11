# RR-Upper-Structure-A
2023 ROBOCON RR Upper Structure ported to F427 MCU
## "Rabbit Robot"
<image src="https://github.com/OriTwil/RR-Upper-Structure-A/blob/main/image/xmind-rr.png" width="1000">
<image src="https://github.com/OriTwil/RR-Upper-Structure-A/blob/main/image/mavlink-rr.png" width="1000">

## File Structure
#### MCU A

- Main ：usermain
- State Machine (State Machine)
  - Manual Mode: Control chassis movement with joystick
  - Auto Mode: Plan target waypoints for chassis through the upper computer and execute them sequentially
  - Locked Mode: Lock the chassis in the current position using feedback control
- Servo  (Servo)
  - Chassis computation and closed-loop control
- Perception Module
  - Perception Mode: Receive sensor information at a certain frequency and update data
  - Calibration Mode: Update sensor data based on calibration schemes, and restore to auto mode after completion
- Communication Module
  - Send and receive MAVLINK messages with the upper computer, Mainboard B, and remote controller at a certain frequency
- State Management
  - Switch states based on combinations of remote controller buttons

#### MCU B
- Main：usermain
- Servo System
  - Servo control at a certain frequency
- State Machine
  - Ready Mode: Initial state, waiting for commands
  - Pickup Mode: Complete picking up rings on different levels
    - Overturn: Flip the ring
    - Clamp: Hold the ring
    - Overturn_back: Flip back to the original position
    - Release: Release the ring
  - Fire Mode: Shoot rings from different points to different pillars, then enter Ready mode
    - Shooting Point 1
      - Target Pillar 1
      - Target Pillar 2
      - ...
    - Shooting Point 2
      - ...
    - Shooting Point 3
    - Shooting Point 4
- Communication Module
  - Receive MAVLINK messages from Mainboard A and send MAVLINK messages to Mainboard A at a certain frequency
- State Management
  - Switch states based on combinations of remote controller buttons

#### MAVLINK Communication Protocol

- Mainboard A to Upper Computer
  - Channel 0
    - id = 9: Upper computer to Mainboard A
    - id = 10: Mainboard A to Upper computer
- Mainboard A to Mainboard B
  - Channel 1
    - id = 11: Mainboard A to Mainboard B
    - id = 12: Mainboard B to Mainboard A
- Mainboard A to Remote Controller
  - Channel 2
    - Depending on the remote controller configuration
  
## Version History
- 2023.4.29 Create the project and complete the basic framework.
- 2.23.4.30 Basically complete the task
- 5.14: Framework completed.
- 5.17: Basic functionality completed, additional design required for the remote controller.

## Tips
- Double-click the workspace to enter the working area.
- For porting, only copy the UserCode folder.
- The RR project uses two mainboards, and this project focuses on the upper structure.
  
## Result
- 5.16 Motor speed planning
  <image src="https://github.com/OriTwil/RR-Upper-Structure-A/blob/main/image/speed-planning.jpg" width="1000">

## Contributors

Thanks to the following contributors for their support and contributions to this project.

- WTR senior students @MirTITH
- WTR Master Xing @xingweiyang0

