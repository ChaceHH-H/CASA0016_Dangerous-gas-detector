# CASA0016_Dangerous-gas-detector
My project is a dangerous gas detector specially designed for use in mines. The gas detector uses 4 Arduino MQ gas sensors to detect four common dangerous gases in mines (Methane, Carbon monoxide, Hydrogen, Flammable gas), and After detecting that the gas content exceeds the safe range, LED lights and buzzers are used to warn users. The gas detector has an OLED display to display the gas data detected by the MQ sensors.  
![Image text](https://github.com/ChaceHH-H/Image/blob/main/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20231212162756.jpg) 
![Image text](https://github.com/ChaceHH-H/Image/blob/main/%E5%BE%AE%E4%BF%A1%E5%9B%BE%E7%89%87_20231212162749.jpg) 

# Hardware  

Sensors and components  
- Arduino uno R4 Board
- 4-MQ gas sensors
- Buzzer
- 2-LED
- OLED
- Stripboard
![Image text](https://github.com/ChaceHH-H/Image/blob/main/Dangerous%20gas.png)  

How to wire and build? The ground and power supply pins of the sensors and components are soldered to the PCB Stripboard, and then the PCB Stripboard is connected to the R4 board. Then connect A0 of the MQ sensor to Analog A0 to A3 of the board. The SCL and SDA of the OLED screen are connected to the same-named interface next to the board reset button. The buzzer is connected to board Digital 12 and the two LEDs are connected to board Digital 11 and 10 using 220 resistors.   
The housing of the detector is built with laser-cut wooden boards. There are seven openings on the front to place the mq sensor, OLED screen and LED. The sensors are glued to the wooden boards with tape.
