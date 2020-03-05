# Failure Analysis Report(FAR)

** Issue: ** IEC Test resulted fail in the item of Fast Transient(FTS) Burst @2kV

To solve this problem we have the find out solutions as below problem solving below

Item | Possible Cause | Details | Solution | Modification | Validation
-- | -- | -- |-- | -- | --  
1 | Power supply efficiency | There is some AC Component(ripple) at O/P | Upgrade max rate current from 250 to 650 mA O/P rate | Change Power Controller IC from RAA223011 to be MT175 | There still be some ripple about 350mV@120Hz >> NG
2 | Power supply efficiency | The system ground loop is not Isolate | Isolate the system ground loop | Use Isolate Power supply | Ripple was improved, still be some ripple about 320mV@36Hz, >>OK
3 | AC component of TM1640 LED Drive controller | the opearating of TM1640 causing a voltage spike and impact to DC output supply | "Separate VDD of TM1640 LED driver from the others circuit | TM1640 --> 5V Vcc, Other --> 3.3V Vcc | VCC 3.3V waveform is stable and there still be some ripple at VCC 5V which is supplied to TM1640 about 350mV@120Hz >>OK
4 | AC component of TM1640 LED Drive controller| the opearating of TM1640 causing a voltage spike and impact to DC output supply | Changes O/P Capacitor | Calculate the O/P Capacitor value which can be reduce that ripple | The calculated Capacitor value is about 15,000uF, it's too high cost and huge package >> NG
5 | AC component of TM1640 LED Drive controller| the opearating of TM1640 causing a voltage spike and impact to DC output supply | Improve TM1640 driving circuit |  Add R220 to reduce spike and limit LED current and Add C100uF at TM1640 Vcc to provide current when the output voltage drops | Pending

Find more info as [Failure Analysis]

[Failure Analysis]:https://docs.google.com/spreadsheets/d/1j6A67tcR5tFxOFAbNM7gbgGV5nbukRrkgzcsJO8MNyo/edit#gid=655437679&range=H1:J1

## Actions
The improved solutions of Failure analysis would be implementd to the new prototype version as details below;
  1. Prototype V17.1: implemented item#2 and 5
  2. Prototype V17.2: implemented item#3 and 5
