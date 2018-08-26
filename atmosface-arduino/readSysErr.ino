bool readSysErr (int deviceAddress) {
  Wire.beginTransmission(deviceAddress); // transmit to device "deviceAddress"
  Wire.write(TOTAL_WORKING_SNS);         // sends one byte
  Wire.endTransmission();    // stop transmitting

  // Request 1 byte from slave device "deviceAddress"
  Wire.requestFrom(deviceAddress, 1);
  unsigned char data = Wire.read(); // Receive a byte as character
  Wire.endTransmission(); // Stop receiving

  //unsigned int sensors = (data & 0x1F);
  //Serial.print("sensor count: ");
  //Serial.println(sensors);
  
  //SYSD_ERR - SEVENTH BIT
  if((data & 0x40) != 0)
  {
    return true;
  }
  else {
    return false;
    }
  }

void enableSysDiagnostic (int deviceAddress) {
  Wire.beginTransmission(deviceAddress); // transmit to device "deviceAddress"
  Wire.write(DEVICE_CFG1);         // sends one byte
  Wire.write(0x01); //enable diagnostic
  Wire.endTransmission();    // stop transmitting
  }
  
bool readSysDiagnosticEnable (int deviceAddress) {
  Wire.beginTransmission(deviceAddress); // transmit to device "deviceAddress"
  Wire.write(DEVICE_CFG1);         // sends one byte
  Wire.endTransmission();    // stop transmitting

  // Request 1 byte from slave device "deviceAddress"
  Wire.requestFrom(deviceAddress, 1);
  unsigned char data = Wire.read(); // Receive a byte as character
  Wire.endTransmission(); // Stop receiving

  //printByte(data);
  
  //SYSD_EN - BIT ZERO
  if((data & 0x01) != 0)
  {
    return true;
  }
  else {
    return false;
    }
  }
