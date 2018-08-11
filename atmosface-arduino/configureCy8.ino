/* Command Codes */
#define LOAD_FACTORY 0x04
#define SAVE_CHECK_CRC 0x02
#define SW_RESET 0xFF

//*****************************************************************************
void configureCY8CMBR3110 () {

  // Configuration array
  unsigned char configData[128] = {
  //GPO drive mode: Open Drain Low
  //PS0 proximity enabled | all other buttons enabled (except CS1) | FSS disabled | auto-reset enabled to 20 sec
  //EMC enabled | Buttons sensitivity 400 fF (minimum sensitivity) | Buttons Finger Threshold 200
  0xFD, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0x0F, 0x00, 0xC8, 0x7F, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
  0xC8, 0xC8, 0xC8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x80, 0x05, 0x00, 0x3E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,
  0x1E, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x11, 0x03, 0x01, 0xA4, 0x00, 0x37, 0x06, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 0xE9
};

//2 Dummy Writes to Wake up the device
Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(REGMAP_ORIGIN);          // sends Offset byte
Wire.write(00);
Wire.endTransmission();    // stop transmitting

Serial.print("CAPSENSE SETUP IN CORSO\n");

Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(REGMAP_ORIGIN);          // sends Offset byte
Wire.write(00);
Wire.endTransmission();    // stop transmitting

//Arduino function can send only 32 bytes at a time hence the ConfigData is sent to CYCMBR in chunks
Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(REGMAP_ORIGIN);          // sends Offset byte
Wire.write(&configData[0],31);        // sends 31 bytes (from 0 to 31)
Wire.endTransmission();    // stop transmitting

Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(31);          // sends Offset byte
Wire.write(&configData[31],31);        // sends next 31 bytes (from 31 to 62)
Wire.endTransmission();    // stop transmitting

Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(62);          // sends Offset byte
Wire.write(&configData[62],31);        // sends further 31 bytes (from 62 to 93)
Wire.endTransmission();    // stop transmitting

Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(93);          // sends Offset byte
Wire.write(&configData[93],31);        // sends 31 bytes (from 91 to 124)
Wire.endTransmission();    // stop transmitting

Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(124);          // sends Offset byte
Wire.write(&configData[124],4);        // sends last remaining 4 bytes
Wire.endTransmission();    // stop transmitting

//write configuration into non volatile memory
Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(CTRL_CMD);
Wire.write(SAVE_CHECK_CRC);
Wire.endTransmission();    // stop transmitting

delay(200);

//reet the device to apply the configuration
Wire.beginTransmission(SLAVE_ADDR); // transmit to device #0x37
Wire.write(CTRL_CMD);
Wire.write(SW_RESET);
Wire.endTransmission();    // stop transmitting

//Provide a delay to calculate and Save CRC
delay(200);

}
