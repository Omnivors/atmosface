/* CY8CMBR3110 Register Map Offset Address */
#define BUTTON_STATUS_ADDR 0xaa
#define CTRL_CMD 0x86
#define REGMAP_ORIGIN 0x00
#define SLAVE_ADDR 0x37
#define DIFF_COUNT_S0_ADDR 0xBA
#define DIFF_COUNT_S1_ADDR 0xBC

// I2C communication protocol
#include <Wire.h>

const int BlueLedPin = 2;

//Capacitive sensing
unsigned char b[2]={'0','0'}; //button status bytes
unsigned char p1[2]={'0','0'}; //proximity status bytes - proximity sensor 1
unsigned char p2[2]={'0','0'}; //proximity status bytes - proximity sensor 2

unsigned int p1c = 0; //difference count for proximity sensor 1
unsigned int p2c = 0; //difference count for proximity sensor 2

//Capacitive buttons
const int BUTTONS_NUMBER = 10;
//bool buttons[BUTTONS_NUMBER] = {false};
bool buttons[BUTTONS_NUMBER] = {0,0,0,0,0,1,1,1,1,1};
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
  // TEMP: test with dumb data
  //p1c = 65000;
  //p2c = 3233; 
  sendData(0);
  sendData(1);
  sendData(2);
  /*readCapSense();
  for (int i = 0; i<BUTTONS_NUMBER; i++)
  {
    Serial.print(buttons[i]);
   }
   Serial.println(" ");
   /*
   Serial.print("proximity 1: ");
   Serial.println(p1c);
   Serial.print("proximity 2: ");
   Serial.println(p2c);
   */
}

//*****************************************************************************
// SMOOTHING METHOD: exponentially decaying moving average
// out=tiny*out+(1-tiny)*in;

//*****************************************************************************
void readCapSense() //Interrupt service routine
{
  //----------Read buttons' data from I2C bus------
  readTwoBytesFromI2C(SLAVE_ADDR, BUTTON_STATUS_ADDR, b);
  
  //print the byte obtained from the 0xaa register
  //if(av!=0){printByte(b);}

  //----------- check buttons  --------------------
  //The values range from 0-255 for button sensors.
  
  checkButtons(b, buttons);

  //----------- check proximity sensors  --------------------
  //The values range from 0-65535  for proximity sensors.
  
  //---READ PROXIMITY DIFFERENCE COUNT FOR BUTTON 0---
  readTwoBytesFromI2C(SLAVE_ADDR, DIFF_COUNT_S0_ADDR, p1);

  //---READ PROXIMITY DIFFERENCE COUNT FOR BUTTON 1---
  readTwoBytesFromI2C(SLAVE_ADDR, DIFF_COUNT_S1_ADDR, p2);
  
  p1c=bitShiftCombine(p1[1],p1[0]);
  p2c=bitShiftCombine(p2[1],p2[0]);

  
  // Clipping and remapping for proximity sensor 1
  /*
  if(p1c>10000){p1c=10000;} //clip
  p1c=map(p1c,0,10000,8192,16383); //remap
  if(p1c<9500){p1c=8192;} //avoid pitch oscillations due to other gestures
  */
  delay(10);
}
