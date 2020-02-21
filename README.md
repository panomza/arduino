# Hardware Development AP12R1 V17

## Executive summary
***Situation:***  The latest version V16 IEC Test result was Passed but unfotunatly, there is abig problem about the MCU program memory is not enought.

To solve this problem we have the find out new MCU with enought memory size is about 32kB.

***Steps Involved:***
1. Concept design
2. PCBA design
3. Software design
4. Engineering sample

## Project descriptions
Develop PCBA with Micro controller(ATMEGA328P) that is coome equip with 32kB program memory. However this MCU IO pin is just 23 IO then we need to add TM1640 to LED drive control insted of MCU 

#### Step1 PCBA design
https://drive.google.com/drive/u/0/folders/1jMU6nZqV70yxMnKUBBw2v8H-WO1wf9Ig

#### Step2 Software design

***Coding:***
XXX

#### Step3 Engineering sample
***Product prototype***
![Prototype](https://tva1.sinaimg.cn/large/0082zybpgy1gc43pkno86j30me06egvm.jpg)

## Conclusion
This developed version can be controlled by all Touchpad control panel, Remote control and mobile application of all functional ie. Power On/Off and Fan speeds control. Result of Air quality monitoring PM2.5 , temperature and humidity result can be detected and displayed.

- [x] Smart Application/Wifi
- [x] Control panel(Capsense)
- [x] Remote control
- [x] PM2.5 detection
- [x] Temp/Humidity detection
- [x] LED Display
- [x] LED Status
- [x] Buzzer
- [x] Fan speed control(Low, Mid,High,Turbo)
- [x] Plasma module control, **Canceled**
- [x] Timer( 8,4,2,1 hrs)

## Project time plan
![Timeplan](https://tva1.sinaimg.cn/large/0082zybpgy1gc4418syezj31y60oyql7.jpg)
