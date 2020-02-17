

unsigned int t0;         // time of last reading
unsigned int timer=200;  // time between each reading

float voMeasured = 0;
float calcVoltage = 0;
unsigned int dustDensity = 0;


float readdust(){
  digitalWrite(ledPower,0);
  delayMicroseconds(280);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(40);
  digitalWrite(ledPower,1);
  delayMicroseconds(9680);

  calcVoltage = voMeasured*(6.72/1024);
  
  dustDensity = (((calcVoltage)/0.51)*100);
  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }
return dustDensity;
}

unsigned int takeaverage(unsigned int input[]){
    
  unsigned long sum=0;
  
  for(int i = 0; i < (numaverage) ; i++){
    sum+=input[i];
  }
  return sum/numaverage;
}

void sensor_dust() {

    if (currenttime-t0>timer){
       count++;
//       Serial.println(averagedust);
       dust[count]=readdust();
       averagedust=takeaverage(dust);

    ///// get index for the next reading
    
    if ((count>numaverage)){ count =0; }
    
    t0=currenttime;
  } 

}

/////////////////////////////////////////////////////////////////////////////////////////

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



void sensor_pana(){
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



  if (firstRun) {
    Serial.println("data has arrived for the first time");
    firstRun = !firstRun;
  }
  

    read_byte14 = readRegister(0x4); // PM25 LL of atmosphere
    delayMicroseconds(1000);
    read_byte15 = readRegister(0x5); // PM25 LH of atmosphere
    delayMicroseconds(1000);
    read_byte16 = readRegister(0x6); // PM25 HL of atmosphere
    delayMicroseconds(1000);
    read_byte17 = readRegister(0x7); // PM25 HH of atmosphere
//    delayMicroseconds(100);




  Serial.print("pm2.5 is ");
  double _pm25 = fourBytesToFloat(read_byte17,read_byte16,read_byte15,read_byte14);
  Serial.println(_pm25);

panadust = _pm25;
averagedust = panadust;
}
