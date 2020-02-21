
#define CLK_PIN (3)
#define DIO_PIN (2)

#define bit_delay_125ns_4clk_of_8Mhz() asm("nop\n nop\n nop\n nop\n")
#define TM1637_CMD1_write_auto_inc_addr (0x40)
#define TM1637_CMD2_1st_mem_addr_7seg_1xxx (0xC0)   
#define TM1637_CMD3_ctrl_screen_head (0x80)         
byte k1=0;
byte k2=0;
byte k3=0;

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

           0b00000001, // 11
           0b00000011, // 12
           0b00000111, // 13
           0b00001011, // 14
           0b00010011, // 15
           0b00100011, // 16
           0b01000011, // 17
           
           0b00000000, // 18
           0b00000001, // 19
           0b00000011, // 20
           0b00000101, // 21
           0b00001001, // 22
           0b00010001, // 23
           0b00100000, // 24
           0b01000000, // 25

           0b00000000, // 26
           0b00100000, // 27

           
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
         for ( uint8_t i=0, value; i <15; i++ ) {
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
    void showTime(uint16_t ds,uint16_t ls,uint16_t ts,uint16_t fs) {
         static uint8_t data[15];

         k3=ds%10;
         k2=ds/10%10;
         k1=ds/100;
          

        /////////RED   
        if(ds>=100) {
         data[0] = k1;   
         data[3] = k2;    
         data[6] = k3;
        }else{
         data[0] = 10;   
         data[3] = 10;    
         data[6] = 10;
        }
        /////////Orenge
        if(ds>=50&&ds<100) {
         data[2] = k1;  
         data[5] = k2;    
         data[8] = k3;
         }else{ 
         data[2] = 10;  
         data[5] = 10;    
         data[8] = 10;
         }
        /////////Green 
        if(ds<50) {
         data[1] = k1;
         data[4] = k2; 
         data[7] = k3;
         }else{ 
         data[1] = 10;
         data[4] = 10; 
         data[7] = 10; 
         }

        data[9] = ls;
        data[10] = ts;
        data[11] = fs;
        data[12] = fs;
         
         showDigits( data); 
     }
unsigned int tts;
int ka=0;
    void Display() {                       

         static uint16_t ds=0;   
         static uint16_t ls=0; 
         static uint16_t ts=0; 
         static uint16_t fs=0;
         static boolean colon=0;
         
         timer_led=(Settime+19)-stateP;
         if(Settime>0&&stateP==1){timer_led=timer_led+1;}
         
         if(stateA==1){speed_led=17;}else{speed_led=(index+12)-stateP;}

         if(ds>999){ds=999;}

         
         if ( currenttime - tts > 50 ) { colon = !colon;                
            showTime(ds,ls,ts,fs); 
              ds=averagedust;  
              ls=speed_led;
              ts=timer_led;
              fs=alarm;   

                        
             tts = currenttime;
//             ka++;
//             
//             if(ka==3){averagedust++;ka=0;}
//             if(averagedust==160){averagedust=0;}
           }
     }
