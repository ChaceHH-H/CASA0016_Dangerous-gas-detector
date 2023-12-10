#include<Wire.h>
#include  <MQUnifiedsensor.h>
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);


#define         Board                   ("Arduino UNO")
#define         Pin4                     (A0)
#define         Pin7                     (A1)
#define         Pin8                     (A2)
#define         Pin9                     (A3)

#define         RatioMQ4CleanAir          (4.4)  //RS / R0 = 4.4 ppm
#define         RatioMQ7CleanAir          (27.5) //RS / R0 = 27.5 ppm
#define         RatioMQ8CleanAir          (70) //RS / R0 = 70 ppm
#define         RatioMQ9CleanAir          (9.6) //RS / R0 = 9.6 ppm
#define         ADC_Bit_Resolution        (10) // 10 bit ADC 
#define         Voltage_Resolution        (5) //  Volt resolution to calc the voltage
#define         Type                      ("Arduino UNO") //Board used
MQUnifiedsensor MQ4(Board, Voltage_Resolution,  ADC_Bit_Resolution, Pin4, Type);
MQUnifiedsensor MQ7(Board, Voltage_Resolution,  ADC_Bit_Resolution, Pin7, Type);
MQUnifiedsensor MQ8(Board, Voltage_Resolution,  ADC_Bit_Resolution, Pin8, Type);
MQUnifiedsensor MQ9(Board, Voltage_Resolution,  ADC_Bit_Resolution, Pin9, Type);

int buzzer = 12;
#define Red_LED 11
#define Green_LED 10

float CH4;
float CO;
float H2;
float FG;

String ch4;
String co;
String h2;
String fg;

void setup(){
  Serial.begin(9600);
  MQ4.init();
  MQ4.setRegressionMethod(1);  //_PPM =  a*ratio^b
  MQ4.setR0(3.19);
  MQ7.init();
  MQ7.setRegressionMethod(1);
  MQ7.setR0(0.46);
  MQ8.init();
  MQ8.setRegressionMethod(1);
  MQ8.setR0(0.24);
  MQ9.init();
  MQ9.setRegressionMethod(1);
  MQ9.setR0(0.99);

  // Serial.print("Calibrating  please wait.");
  // float  MQ4calcR0 = 0,
  //        MQ7calcR0 = 0,
  //        MQ8calcR0 = 0,
  //        MQ9calcR0  = 0;
  // for (int i = 1; i <= 10; i ++)
  // {
  //   //Update the voltage lectures
  //   MQ4.update();
  //   MQ7.update();
  //   MQ8.update();
  //   MQ9.update();

  //   MQ4calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
  //   MQ7calcR0 += MQ7.calibrate(RatioMQ7CleanAir);
  //   MQ8calcR0 += MQ8.calibrate(RatioMQ8CleanAir);
  //   MQ9calcR0 += MQ9.calibrate(RatioMQ9CleanAir);
  //   Serial.print(".");
  // }
  // MQ4.setR0(MQ4calcR0 / 10);
  // MQ7.setR0(MQ7calcR0 / 10);
  // MQ8.setR0(MQ8calcR0 / 10);
  // MQ9.setR0(MQ9calcR0  / 10);
  // Serial.println("  done!.");

  // Serial.print("(MQ4 - MQ9):");
  // Serial.print(MQ4calcR0  / 10); Serial.print(" | ");
  // Serial.print(MQ7calcR0 / 10); Serial.print(" | ");
  // Serial.print(MQ8calcR0  / 10); Serial.print(" | ");
  // Serial.print(MQ9calcR0 / 10); Serial.println("  |");


  u8g2.begin();
  u8g2.setFont(u8g2_font_t0_11_tf);
  pinMode(buzzer,OUTPUT);
  pinMode(Red_LED,OUTPUT);
  pinMode(Green_LED,OUTPUT);


}

void loop() {
  MQ4.update();
  MQ7.update();
  MQ8.update();
  MQ9.update();

  MQ4.setA(1012.7); MQ4.setB(-2.786); //CH4
  CH4 = MQ4.readSensor();
  //MQ4.setA(30000000); MQ4.setB(-8.308);
  //float smoke = MQ4.readSensor();
  MQ7.setA(99.042);  MQ7.setB(-1.518);
  CO = MQ7.readSensor();
  MQ8.setA(976.97);  MQ8.setB(-0.688);
  H2 = MQ8.readSensor();
  MQ9.setA(1000.5);  MQ9.setB(-2.186);
  FG = MQ9.readSensor();

  Serial.print("Methane:  "); Serial.println(CH4);
  Serial.print("CO:       "); Serial.println(CO);
  Serial.print("H2:       "); Serial.println(H2);
  Serial.print("FG:       "); Serial.println(FG);
  Serial.println("--------------------------------------------------------");

  //u8g2.firstPage();
  ch4="Methane: " + String(CH4);
  co="CO     : " + String(CO);
  h2="H2     : " + String(H2);
  fg="FG     : " + String(FG);

  if(CH4>1000||CO>50||H2>50||FG>20){
    detection();
    digitalWrite(Red_LED,HIGH);
    digitalWrite(Green_LED,LOW);
    tone(buzzer, 1000);
  }else{
    u8g2.clearBuffer();
    u8g2.drawStr(50,10,"SAVE");
    u8g2.drawStr(0,20,ch4.c_str());
    u8g2.drawStr(0,30,co.c_str());
    u8g2.drawStr(0,40,h2.c_str());
    u8g2.drawStr(0,50,fg.c_str());
    u8g2.sendBuffer();
    digitalWrite(Red_LED,LOW);
    digitalWrite(Green_LED,HIGH);
    noTone(buzzer);
  }

  // tone(buzzer, 1000);
  // delay(1000);
  // noTone(buzzer);

  // digitalWrite(Red_LED,HIGH);
  // delay(2000);
  // digitalWrite(Red_LED,LOW);
  // digitalWrite(Green_LED,HIGH);
  // delay(2000);
  // digitalWrite(Green_LED,LOW);

  delay(5000);
}

void detection(){
    u8g2.clearBuffer();
    u8g2.drawStr(0,10,"!Danger gas detected!");
    if(CH4>1000){
      u8g2.drawStr(0,20,ch4.c_str());
    }
    if(CO>50){
      u8g2.drawStr(0,30,co.c_str());
    }
    if(H2>50){
      u8g2.drawStr(0,40,h2.c_str());
    }
    if(FG>20){
      u8g2.drawStr(0,50,fg.c_str());
    }
    u8g2.sendBuffer();
}

