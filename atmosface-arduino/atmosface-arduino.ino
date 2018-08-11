/* CY8CMBR3110 Register Map Offset Address */
#define BUTTON_STATUS_ADDR 0xaa
#define CTRL_CMD 0x86
#define REGMAP_ORIGIN 0x00
#define SLAVE_ADDR 0x37
#define DIFF_COUNT_S0_ADDR 0xBA
#define DIFF_COUNT_S1 0xBC

// I2C communication protocol
#include <Wire.h>

const int BlueLedPin=2;

//Capacitive sensing
char b[2]={'0','0'}; //button status bytes
unsigned char p[2]={'0','0'}; //proximity status bytes
unsigned int p0 = 0; //difference count for sensor 0 (proximity sensor)

//Capacitive buttons
boolean buttons[8]={false};

//*************** SETUP ********************************************************
void setup() {
  
  // Join the I2C bus as MASTER
  Wire.begin();

  // Set led pins as outputs
  pinMode(BlueLedPin, OUTPUT);
  digitalWrite(BlueLedPin,HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);

  //attachInterrupt(0, HostInterrruptISR, RISING);
  // Start serial com
  Serial.begin(9600);
  delay(5000);

  // Load the configuration for Cypress CapSense
  configureCY8CMBR3110();
  delay(2000);
}

//*************** LOOP ********************************************************
void loop()
{
  readCapSense();
  /*for (int i = 0; i<8; i++)
  {
    Serial.print(buttons[i]);
    Serial.println(" ");
   }
   Serial.println(" ");
   Serial.println(p0);*/
   Serial.print("proximity: ");
   Serial.println(p0);
}

//*****************************************************************************
// SMOOTHING METHOD: exponentially decaying moving average
// out=tiny*out+(1-tiny)*in;

//*****************************************************************************
void readCapSense() //Interrupt service routine
{
  //----------Read buttons' data from I2C bus------
  readFromI2C(SLAVE_ADDR, BUTTON_STATUS_ADDR, b);
  
  //print the byte obtained from the 0xaa register
  //if(av!=0){printByte(b);}

  //----------- check buttons  --------------------
  checkButtons(b, buttons);

  //---READ PROXIMITY DIFFERENCE COUNT FOR BUTTON 0---
  readFromI2C(SLAVE_ADDR, DIFF_COUNT_S0_ADDR, p);
  
  p0=bitShiftCombine(p[1],p[0]);
  if(p0>10000){p0=10000;} //clip
  p0=map(p0,0,10000,8192,16383); //remap
  if(p0<9500){p0=8192;} //avoid pitch oscillations due to other gestures
  delay(10);
}
