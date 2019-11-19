
#define CLK_PIN (3)
#define DIO_PIN (2)

#define bit_delay_125ns_4clk_of_8Mhz() asm("nop\n nop\n nop\n nop\n")
#define TM1637_CMD1_write_auto_inc_addr (0x40)
#define TM1637_CMD2_1st_mem_addr_7seg_1xxx (0xC0)   
#define TM1637_CMD3_ctrl_screen_head (0x80)         
int k1=0;
int k2=0;
int k3=0;

     const uint8_t SEVEN_SEG_DIGITS[] = {
           // gfedcba
           0b00111111, // 0
           0b00000110, // 1
           0b01011011, // 2
           0b01001111, // 3
           0b01100110, // 4
           0b01101101, // 5
           0b01111101, // 6
           0b00000111, // 7
           0b01111111, // 8
           0b01101111, // 9

          
           0b00000000, // 10
   };

    void tm1637_init_pin_for_sent_I2C() {
       pinMode( CLK_PIN, OUTPUT );
       pinMode( DIO_PIN, OUTPUT );
       digitalWrite( CLK_PIN, HIGH );
       digitalWrite( DIO_PIN, HIGH );
     }

    void tm1637_start_bit_I2C() {
         digitalWrite( DIO_PIN, LOW );
         bit_delay_125ns_4clk_of_8Mhz();
         digitalWrite( CLK_PIN, LOW );
         bit_delay_125ns_4clk_of_8Mhz();
     }

     void tm1637_stop_bit_I2C() {
          digitalWrite( CLK_PIN, HIGH );
          bit_delay_125ns_4clk_of_8Mhz();
          digitalWrite( DIO_PIN, HIGH );
          bit_delay_125ns_4clk_of_8Mhz();
      }

    int tm1637_send_1byte_I2C_ack( uint8_t data ) {
         uint8_t ack;
         for( uint8_t i = 0; i < 7; i++ ) {           // Send 8-bit data, LSB first
            digitalWrite( CLK_PIN, LOW );
            digitalWrite( DIO_PIN, ( data & 0x01 ) ? HIGH : 0 ); // ????????????????
            digitalWrite( CLK_PIN, HIGH );
            data >>= 1;                                    // shift bit to the right
           }
         digitalWrite( CLK_PIN, LOW );
             // I2C acknowledgement process , read ack in clolck9
         pinMode( DIO_PIN, INPUT );      // make DIO pin floating (input)
         digitalWrite( DIO_PIN, HIGH );   // enable pull-up
         digitalWrite( CLK_PIN, HIGH );   // start clock9
         ack = digitalRead( DIO_PIN );    // read ACK bit 
            // make DIO pin to output again
         digitalWrite( DIO_PIN, LOW );
         pinMode( DIO_PIN, OUTPUT );
         digitalWrite( CLK_PIN, LOW );
         return (ack==0);                                    
      }

   boolean showDigits( uint8_t digits[], boolean colon=false, uint8_t brightness=bright7) {
       // send the first command-----------------------
         tm1637_start_bit_I2C();
         tm1637_send_1byte_I2C_ack( TM1637_CMD1_write_auto_inc_addr );
         tm1637_stop_bit_I2C();
       // send the second command-------------------
         tm1637_start_bit_I2C();
         tm1637_send_1byte_I2C_ack( TM1637_CMD2_1st_mem_addr_7seg_1xxx );
         for ( uint8_t i=0, value; i <9; i++ ) {
           value = SEVEN_SEG_DIGITS[ digits[i] ];
           if ( (i == 1) && colon ) {
              value |= 0x80; // turn on the colon on the display ,x1xx digit ,hundreds digit
             }
           tm1637_send_1byte_I2C_ack( value );
         }
        tm1637_stop_bit_I2C();
      // send the third command---------------------- option send only 1 time is OK---- 
        tm1637_start_bit_I2C();
        tm1637_send_1byte_I2C_ack( TM1637_CMD3_ctrl_screen_head | (brightness & 7) | 0x08 );
             // brightness [0-7] , &0x07 filter to correct brightness value (before OR with CMD3)
            // 0x08 (0b00001000) , 1 is bit cmd for open 7seg screen ,0= close screen
        tm1637_stop_bit_I2C();
     }

////////////////////////////////////////////////////////////////////////

     
      // show time (hour and minute)
    void showTime(uint16_t ss) {
         static uint8_t data[9];

         k1=ss%10;
         k2=ss/10%10;
         k3=ss/100;   
         
        /////////RED   
        if(ss>=120) {
         data[2] = k1;   
         data[5] = k2;    
         data[8] = k3;
        }else{
         data[2] = 10;   
         data[5] = 10;    
         data[8] = 10;
        }
        /////////Orenge
        if(ss>=60&&ss<120) {
         data[0] = k1;  
         data[3] = k2;    
         data[6] = k3;
         }else{ 
         data[0] = 10;  
         data[3] = 10;    
         data[6] = 10;
         }
        /////////Green 
        if(ss<60) {
         data[1] = k1;
         data[4] = k2; 
         data[7] = k3;
         }else{ 
         data[1] = 10;
         data[4] = 10; 
         data[7] = 10; 
         }
         
         showDigits( data); 
     }
unsigned int ts;
int ka=0;
    void Display() {                       
//if (ka==20){delay(1000);}
         static uint16_t ss=0;   
          if(ss>999){ss=999;}
         if ( currenttime - ts > 300 ) {                
            showTime(ss); 
              ss=averagedust;                
             ts = currenttime;
             ka++;
           }
     }
