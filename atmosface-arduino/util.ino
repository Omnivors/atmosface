// UTILITY FUNCTIONS
//
// ************************************************************************
void printByte(char b)
{
  int j=0;
  for (j = 0; j < 8; j++) {

      Serial.print(!!((b << j) & 0x80));
      }

  Serial.print("\n");

  }

// ************************************************************************
void blinkledfastBLUE()
 {
   digitalWrite(BlueLedPin, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because it is acive low on the ESP-01)
   delay(200);                      // wait
   digitalWrite(BlueLedPin, HIGH);  // Turn the LED off by making the voltage HIGH
   delay(200);                      // wait
 }


// ************************************************************************
 void blinkledfastRED()
 {
   digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                     // but actually the LED is on; this is because it is acive low on the ESP-01)
   delay(200);                       // wait
   digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
   delay(200);                       // wait
 }


// ************************************************************************
char boolToChar(bool b)
{
  return b ? '1' : '0';
}

// ************************************************************************
int mapFloat(float x, float in_min, float in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// ************************************************************************
unsigned int bitShiftCombine(unsigned char x_high, unsigned char x_low)
{
  unsigned int combined;
  combined = x_high;           //send x_high to rightmost 8 bits
  combined = combined<<8;      //shift x_high over to leftmost 8 bits
  combined |= x_low;           //logical OR keeps x_high intact in combined and fills in rightmost 8 bits
  return combined;
}

// ************************************************************************
unsigned int bitArrayToInt16(bool arr[], unsigned int count)
{
    unsigned int ret = 0;
    unsigned int tmp;
    for (int i = 0; i < count; i++) {
        tmp = arr[i];
        ret |= tmp << (count - i - 1);
    }
    return ret;
}

