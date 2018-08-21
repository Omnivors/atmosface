// ************************************************************************
/* 
 *  Encode and send data through serial port
 *  0 - button array
 *  1 - proximity sensor 1
 *  2 - proximity sensor 2
 */
void sendData (int sensor) {
  switch (sensor) {
    case (0):
        encodeButtons();
    break;  
    case (1):
        encodeProximity(1, p1c);
    break;
    case (2):
       encodeProximity(2, p2c);
    break;
    }
}

void encodeProximity (int sensor, unsigned int data) {
  uint8_t third  = (data & 63) | 128;
  // SAME AS: third = (data & 0b00111111) | 0b10000000;
  uint8_t second = ((data >> 6) & 63) | 64;
  // SAME AS: second = ((data >> 6) & 0b00111111) | 0b01000000;
  uint8_t first = (data >> 12) | (sensor * 16);
  Serial.write(first);
  Serial.write(second);
  Serial.write(third);
}

void encodeButtons () {
  unsigned int btn = bitArrayToInt16(buttons, BUTTONS_NUMBER);
  uint8_t low = (btn & 63) | 64;
  uint8_t high = (btn >> 6) | 15;
  Serial.write(high);
  Serial.write(low);
}
