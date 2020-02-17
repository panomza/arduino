//#define SCL_PIN  1                 // SCLは9番ピンとする
//#define SCL_PORT PORTB 
//#define SDA_PIN  0                 // SDAは8番ピンとする
//#define SDA_PORT PORTB 
#include <avr/wdt.h>
#include <TimerOne.h>
#include <Wire.h>
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(A4, A5); // RX, TX
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int bit8[] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

unsigned char SENSOR_ADDRESS = 0x33; // Slave address(fixed)

int P_i2c_scl = 19;
int P_i2c_sda = 18;
int i2c_delay = 5;
int err = 0;
int ecnt = 0;
int datacnt = 0;
int data1, data2;
bool firstRun = true;


byte sliceInteger(int integer, int _start, int _length) {
  return (integer >> _start) & ((1 << _length) - 1);
}

int readRegister(byte reg)  // Read data
{
  int read_byte;

  Wire.beginTransmission(SENSOR_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false);

  delayMicroseconds(800);

  Wire.requestFrom(SENSOR_ADDRESS, 1, true);
  if (firstRun){
    Serial.print("wire is");
    Serial.print (Wire.available());
    Serial.println("available");
  }

  while (Wire.available()) {
    read_byte = Wire.read();
  }
  return read_byte;
}

double fourBytesToFloat(byte hh, byte hl, byte lh, byte ll){
    uint64_t myInt1 = (int)hh * pow(256, 3) + (int)hl * pow(256, 2) + (int)lh * pow(256, 1) + (int)ll * pow(256, 0);
  return double(myInt1) /1000;
  }

void setup(){ // Set up
   Serial.begin(9600); // Set up communication speed
   Wire.begin();  // Connection start
   Wire.setClock(60000L); 
   Serial.println("set up complete");
//   Serial.println(Serial.available());

//  wdt_enable(WDTO_1S);
}

void loop() // Main function
{ 
  unsigned int raw;
  int input, cnt;
  double value,PM;
  unsigned int read_byte10, read_byte11, read_byte12, read_byte13;
  unsigned int read_byte14, read_byte15, read_byte16, read_byte17;
  unsigned int read_byte18, read_byte19;
  unsigned int read_byte20, read_byte21, read_byte22, read_byte23;
  unsigned int read_byte24, read_byte25, read_byte26, read_byte27;
  unsigned int read_byte28, read_byte29;
  unsigned int read_byte30, read_byte31, read_byte32, read_byte33;
  unsigned int read_byte34, read_byte35, read_byte36, read_byte37;
  unsigned int read_byte38, read_byte39;
  unsigned int read_byte40, read_byte41, read_byte42, read_byte43;
  unsigned int read_byte44, read_byte45, read_byte46, read_byte47;
  unsigned int read_byte48, read_byte49;
  unsigned int read_byte_Status;


//  if (Serial.available()) {
//    Serial.println("serial is available");
//  } else {
//    Serial.println("serial is not available");
//  }
//  

//  Wire.requestFrom(0x33, 6);
//  do {
//    wdt_reset();
//  }
//  while (Wire.available() == 0); // 受信したデータが存在する
  if (firstRun) {
    Serial.println("data has arrived for the first time");
    firstRun = !firstRun;
  }
  
//  input = Serial.read();
//0x21
//  Serial.print("serial input is");
//  Serial.println(input);
//  if(input == 10){ 
//  if(Wire.available()){
    Serial.print("sensor found");
    read_byte10 = readRegister(0x0); // PM1 LL of atmosphere
    delayMicroseconds(1000);
    read_byte11 = readRegister(0x1); // PM1 LH of atmosphere
    delayMicroseconds(1000);
    read_byte12 = readRegister(0x2); // PM1 HL of atmosphere
    delayMicroseconds(1000);
    read_byte13 = readRegister(0x3); // PM1 HH of atmosphere
    delayMicroseconds(100);

    read_byte14 = readRegister(0x4); // PM25 LL of atmosphere
    delayMicroseconds(1000);
    read_byte15 = readRegister(0x5); // PM25 LH of atmosphere
    delayMicroseconds(1000);
    read_byte16 = readRegister(0x6); // PM25 HL of atmosphere
    delayMicroseconds(1000);
    read_byte17 = readRegister(0x7); // PM25 HH of atmosphere
    delayMicroseconds(100);

    read_byte18 = readRegister(0x8); // PM10 LL of atmosphere
    delayMicroseconds(1000);
    read_byte19 = readRegister(0x9); // PM10 LH of atmosphere
    delayMicroseconds(1000);
    read_byte20 = readRegister(0xa); // PM10 HL of atmosphere
    delayMicroseconds(1000);
    read_byte21 = readRegister(0xb); // PM10 HH of atmosphere
    delayMicroseconds(100);


    read_byte22 = readRegister(0xc); // PM25 N3 L of atmosphere
    delayMicroseconds(1000);
    read_byte23 = readRegister(0xd); // PM25 N3 H of atmosphere
    delayMicroseconds(1000);
    read_byte24 = readRegister(0xe); // PM25 N2 L of atmosphere
    delayMicroseconds(1000);
    read_byte25 = readRegister(0xf); // PM25 N2 H of atmosphere
    delayMicroseconds(1000);
    read_byte26 = readRegister(0x10); // PM25 N1 L of atmosphere
    delayMicroseconds(1000);
    read_byte27 = readRegister(0x11); // PM25 N1 H of atmosphere
    delayMicroseconds(1000);
    read_byte28 = readRegister(0x12); // PM25 N0 L of atmosphere
    delayMicroseconds(1000);
    read_byte29 = readRegister(0x13); // PM25 N0 H of atmosphere
    delayMicroseconds(1000);

    read_byte30 = readRegister(0x14); // PM10 N3 L of atmosphere
    delayMicroseconds(1000);
    read_byte31 = readRegister(0x15); // PM10 N3 H of atmosphere
    delayMicroseconds(1000);
    read_byte32 = readRegister(0x16); // PM10 N2 L of atmosphere
    delayMicroseconds(1000);
    read_byte33 = readRegister(0x17); // PM10 N2 H of atmosphere
    delayMicroseconds(1000);
    read_byte34 = readRegister(0x18); // PM10 N1 L of atmosphere
    delayMicroseconds(1000);
    read_byte35 = readRegister(0x19); // PM10 N1 H of atmosphere
    delayMicroseconds(1000);
    read_byte36 = readRegister(0x1a); // PM10 N0 L of atmosphere
    delayMicroseconds(1000);
    read_byte37 = readRegister(0x1b); // PM10 N0 H of atmosphere
    delayMicroseconds(1000);

    read_byte_Status = readRegister(0x26); // status check
    delayMicroseconds(1000);

    
    read_byte44 = readRegister(0x66); //
    delayMicroseconds(100);

    Serial.println("data read");

    
//    Serial.write(read_byte10);  // 0x00
//    Serial.write(read_byte11);  // 0x01
//    Serial.write(read_byte12);  // 0x02
//    Serial.write(read_byte13);  // 0x03
//    Serial.write(read_byte14);  // 0x04
//    Serial.write(read_byte15);  // 0x05
//    Serial.write(read_byte16);  // 0x06
//    Serial.write(read_byte17);  // 0x07
//    Serial.write(read_byte18);  // 0x08
//    Serial.write(read_byte19);  // 0x09
//    Serial.write(read_byte20);  // 0x0a
//    Serial.write(read_byte21);  // 0x0b
//
//    Serial.write(read_byte22);  // 0x0c
//    Serial.write(read_byte23);  // 0x0d
//    Serial.write(read_byte24);  // 0x0e
//    Serial.write(read_byte25);  // 0x0f
//    Serial.write(read_byte26);  // 0x10
//    Serial.write(read_byte27);  // 0x11
//    Serial.write(read_byte28);  // 0x12
//    Serial.write(read_byte29);  // 0x13
//    Serial.write(read_byte30);  // 0x14
//    Serial.write(read_byte31);  // 0x15
//    Serial.write(read_byte32);  // 0x16
//    Serial.write(read_byte33);  // 0x17
//    Serial.write(read_byte34);  // 0x18
//    Serial.write(read_byte35);  // 0x19
//    Serial.write(read_byte36);  // 0x1a
//    Serial.write(read_byte37);  // 0x1b
//    
//    Serial.write(read_byte44);  //

//    Serial.print("PM 1 LL of atmosphere ");
//    Serial.println(read_byte10);  // 0x00
//    Serial.print("PM 1 LH of atmosphere ");
//    Serial.println(read_byte11);  // 0x01
//    Serial.print("PM 1 HL of atmosphere ");
//    Serial.println(read_byte12);  // 0x02
//    Serial.print("PM 1 HH of atmosphere ");
//    Serial.println(read_byte13);  // 0x03
//    Serial.print("PM 25 LL of atmosphere ");
//    Serial.println(read_byte14);  // 0x04
//    Serial.print("PM 25 LH of atmosphere ");
//    Serial.println(read_byte15);  // 0x05
//    Serial.print("PM 25 HL of atmosphere ");
//    Serial.println(read_byte16);  // 0x06
//    Serial.print("PM 25 HH of atmosphere ");
//    Serial.println(read_byte17);  // 0x07
//    Serial.print("PM 10 LL of atmosphere ");
//    Serial.println(read_byte18);  // 0x08
//    Serial.print("PM 10 LH of atmosphere ");
//    Serial.println(read_byte19);  // 0x09
//    Serial.print("PM 10 HL of atmosphere ");
//    Serial.println(read_byte20);  // 0x0a
//    Serial.print("PM 10 HH of atmosphere ");
//    Serial.println(read_byte21);  // 0x0b
//
//    Serial.print("R1 count L ");
//    Serial.println(read_byte22);  // 0x0c
//    Serial.print("R1 count H ");
//    Serial.println(read_byte23);  // 0x0d
//    Serial.print("R2 count L ");
//    Serial.println(read_byte24);  // 0x0e
//    Serial.print("R2 count H ");
//    Serial.println(read_byte25);  // 0x0f
//    Serial.print("R3 count L ");
//    Serial.println(read_byte26);  // 0x10
//    Serial.print("R3 count H ");
//    Serial.println(read_byte27);  // 0x11
//    Serial.print("R4 count L ");
//    Serial.println(read_byte28);  // 0x12
//    Serial.print("R4 count H ");
//    Serial.println(read_byte29);  // 0x13
//    Serial.print("R5 count L ");
//    Serial.println(read_byte30);  // 0x14
//    Serial.print("R5 count H ");
//    Serial.println(read_byte31);  // 0x15
//    Serial.print("R6 count L ");
//    Serial.println(read_byte32);  // 0x16
//    Serial.print("R6 count H ");
//    Serial.println(read_byte33);  // 0x17
//    Serial.print("R7 count L ");
//    Serial.println(read_byte34);  // 0x18
//    Serial.print("R7 count H ");
//    Serial.println(read_byte35);  // 0x19
//    Serial.print("R8 count L ");
//    Serial.println(read_byte36);  // 0x1a
//    Serial.print("R8 count H ");
//    Serial.println(read_byte37);  // 0x1b
//    //Status check
//    Serial.print("sensor status ");
//    Serial.println(sliceInteger(read_byte_Status,0,2));
//    
////    Serial.write(read_byte44);  //
//
//    Serial.println(read_byte44);
//    Serial.println("read_byte44");

  Serial.println("sending a delay of 2 seconds");
  delay(2000);


  Serial.print("pm2.5 is ");
  double _pm25 = fourBytesToFloat(read_byte17,read_byte16,read_byte15,read_byte14);
  Serial.println(_pm25);
  Serial.print("pm1 is ");
  double _pm1 = fourBytesToFloat(read_byte13,read_byte12,read_byte11,read_byte10);
  Serial.println(_pm1);
  
//  uint32_t myInt1 = (read_byte17 << 24) + (read_byte16 << 16) + (read_byte15 << 8) + read_byte14 ;
  




 
  
  

}
