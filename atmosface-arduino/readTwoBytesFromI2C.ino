void readTwoBytesFromI2C(int deviceAddress, int functionAddress, char dataIn[2]) 
{
  // Read information from the I2C bus
  
  Wire.beginTransmission(deviceAddress); // transmit to device "deviceAddress"
  Wire.write(functionAddress);         // sends one byte
  Wire.endTransmission();    // stop transmitting

  // Request 2 bytes from slave device "deviceAddress"
  Wire.requestFrom(deviceAddress, 2);

  int i=0;
  while (Wire.available()) {
    dataIn[i] = Wire.read(); // Receive a byte as character
    i++;
  }
  Wire.endTransmission(); // Stop receiving
}
