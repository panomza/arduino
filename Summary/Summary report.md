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
There are 2 developed PCBAs:
  - Prototype V17.1 Isolated Power Supply
  - Prototype V17.2 Non-Isolate Power Supply

More design info as [PCBA Design]

[PCBA Design]: https://drive.google.com/drive/u/0/folders/1jMU6nZqV70yxMnKUBBw2v8H-WO1wf9Ig


Component list [BOM]

[BOM] : https://docs.google.com/spreadsheets/d/1OoUqc4dZkHaTaQ2dJCIZbOoq1gXtm2C6JJ563SU6HNw/edit#gid=1445442228&range=A1


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
- [x] LED Display
- [x] LED Status
- [x] Buzzer
- [x] Fan speed control(Low, Mid,High,Turbo)
- [x] Plasma module control, **Canceled**
- [x] Timer( 8,4,2,1 hrs)

## Cost Comparison
This table shows the estimate cost comparison of the new development PCBA 

Detail | Hatari_Current AP12 | Hatari_Facelift AP12 V17.1 | Hatari_Facelift AP12 V17.2 | SCR_Facelift AP12
-- | -- | -- |-- | --
PM 2.5 Sensor | No | 195 | 195 | 195
Component Cost | NA | 240.06 | 200.17 | 191.40
PCB Cost | NA | 28.20 | 28.17 | 28.17
Operation Cost(20%)| NA | 40.00 | 40.0 | 40.0
Total cost(THB)| 357.49 | 503.26 | 463.37 | 454.60
Cost compare to the current model(%)| - | 40.78%| 29.62% | 27.16%

Find more info as [Cost comparison]

[Cost comparison]: https://docs.google.com/spreadsheets/d/1OoUqc4dZkHaTaQ2dJCIZbOoq1gXtm2C6JJ563SU6HNw/edit#gid=1445442228&range=F60


## Prototype Verification
***IEC test results:***

Issue in standard IEC 60335-1 | Details | Prototype V17.1(Isolated) | Prototype V17.2(Non Isolateed
-- | -- | -- |--
19.11.4.1 | Electrostatic Discharges | NA | NA
19.11.4.2 | Fast transient bursts | Pass(Class B: LED flickerd on):(4kV@220V 50Hz) Pass(Class B: LED flickerd on):(4kV@240V 60Hz) | Fail
19.11.4.3 | Voltage surges | Pass:(4kV@220V 50Hz)Pass:(4kV@240V 60Hz) | NA
19.11.4.4| Voltage dip and interruption | NA | Pass(Class C: manual reset):(%Test level= 0,40,70,80 of 220V 50Hz) 
19.11.4.5| Injected Current | Pass:Level 3 (10V, cover frequency 0.15-80 MHz) | NA

Find more info as [IEC Test results]

[IEC Test results]:https://drive.google.com/drive/u/0/folders/1pRGlJxpX68WHeiG0OGF6jnQy6Eyk631P

## Project time plan
***Project timeplan:***
![Timeplan](https://tva1.sinaimg.cn/large/0082zybpgy1gc9yj89kxtj32fm0fm7e1.jpg)

***Failure analysis plan:***
![Timeplan](https://tva1.sinaimg.cn/large/0082zybpgy1gc9yl5x6zsj329k0f0qgr.jpg)
