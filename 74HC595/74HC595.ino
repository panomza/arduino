const byte DS_PIN   = 8;     // to Pin 14 of the 75HC595 
const byte STCP_PIN = 9;     // to Pin 12 of the 75HC595 
const byte SHCP_PIN = 10;    // to Pin 11 of the 75HC595 

// global variables
uint32_t ts = 0;

void setup() {
  pinMode( DS_PIN, OUTPUT );
  pinMode( STCP_PIN, OUTPUT );
  pinMode( SHCP_PIN, OUTPUT );
  digitalWrite( STCP_PIN, LOW );
  digitalWrite( SHCP_PIN, LOW );
}               

// shift out data byte(s) 
void shiftOut( uint8_t *data, uint16_t len ) {
  uint16_t num_bits = 8*len;
  uint8_t b;
  digitalWrite( SHCP_PIN, LOW );
  for (uint16_t i=0; i < num_bits; i++) {
    b = (data[i/8] >> (i%8)) & 1; // LSB first
    digitalWrite( DS_PIN, b);
    digitalWrite( SHCP_PIN, HIGH );
    digitalWrite( SHCP_PIN, LOW );
  }
  digitalWrite( SHCP_PIN, LOW );
  digitalWrite( STCP_PIN, HIGH );
  digitalWrite( STCP_PIN, LOW );
}

void leds_dimming() {
  byte data, level=0;
  byte levels[8] = {0,0,0,0,0,0,0,0};
  byte index = 0;

  while (true) { 
    // update one PWM period
    for ( int j=0; j < 100; j++) { 
      data = 0;
      for ( int i=0; i < 8; i++) {
        level = levels[i];
        if (level >= 100) {
          level = 200-level;
        }
        if (j < level) data |= (1 << i);
      }
      shiftOut( &data, 1 );
      //delayMicroseconds(4);
    }
    if ( micros() - ts >= 50 ) { // update every 50 usec
      if ( levels[index] == 200 ) {
         levels[index] = 0;
         index = (index+1) % 8;
      } else {
        levels[index]++;
      }
      ts = micros(); 
    }
  }
}

void loop() {
  leds_dimming();
}
