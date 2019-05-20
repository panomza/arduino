# arduino
Development project

# Hardware Development AP12

## Executive summary
***Situation:***  The presence of dust in environments are unavoidable. In fact, according to the Environmental Protection Agency, indoor air can be 2 to 5 times more polluted than outdoor air. This airborne pollution contributes to minor annoyances such as itchy eyes, sneezing, and headaches to human beings. Worst still, it can be a major contributing factor to severe allergies, life-threatening asthma.

To solve this problem we have the current Facelift air purifier product which working well address this issue. But, we would like to leverage the advantage of IoT to make the air purifier smarter.

***Steps Involved:***
        1. Hardware design
        2. Software component design
        3. Make development sample
        4. Test

## Project descriptions
Develop Electronics control board with Micro-controller and Wifi module (ESP8286) to connect online data to mobile application, with sufficient I/O pins to support the large number of peripherals. Remote control and Touchpad Capacitive sensor for user control, Buzzer, 7 segments display and LED status for interfacing with the user. Power supply unit sufficiently large for a system use. Soft switch Triac to control fan motor speed. Plasma control.

#### Step1
Design Hardware diagram and overall function.
![Block diagram](https://ws2.sinaimg.cn/large/006tNc79gy1g2tnwsc0cfj30xq0h241i.jpg)

***Required function:***

No. | item | Descriptions | Note
-- | -- | -- |--
1 | Air quality monitoring | Measure air quality | PM2.5, Tem/Hud
2 | Automatic mode | operate if the presence of dust or hazardous gas reach certain level automatically | PM 2.5 (0 -35 Good , 36 -99 Fair, Over 99 Poor)
3 | Application/Web app. | Functional control and display via online application/website
4| Manual function | Functional controls and displays on control panel(Capacitive sensor) | ON/OFF, Speed control 1-4, Automatic Mode, Turn ON/OFF Plasma, Timer ON / OFF 
5 | Remote control | Functional controls |control is like as manual function
6 | Display/Alert | status for interfacing with the user |***LED Status;*** ON/OFF, Speed control 1-4, Automatic Mode, Turn ON/OFF Plasma, Timer ON / OFF ***LED 7 segments;*** Air quality ***Buzzer;*** push button switch pressed canbe turned On/Off

#### Step2
***Gather all components***
![PCBA_F_Rev04](https://ws1.sinaimg.cn/large/006tNc79gy1g2tp2lkqmcj31n00lg7cz.jpg)
![PCBA_B_Rev04](https://ws4.sinaimg.cn/large/006tNc79gy1g2tp2mthtuj31oe0kwdpf.jpg)

#### Step3
***Wiring components***
![Wiring](https://ws2.sinaimg.cn/large/006tNc79gy1g2toxtvi8xj315i0q4qdd.jpg)
 
#### Step4
***Coding:***
https://github.com/panomza/arduino/tree/master/code%20%E0%B9%81%E0%B8%A2%E0%B8%81%20AP/main

#### Step5
***Product sample:***

## Conclusion
This developed version can be controlled by all Touchpad control panel, Remote control and mobile application of all functional ie. Power On/Off, Fan speeds and Plasma On/Off. Result of Air quality monitoring PM2.5 , temperature and humidity result can be detected and displayed.

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
