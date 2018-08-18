bool checkButtons(unsigned char bb[2], bool buttons[10]) {
  /**********************************
  /**** BUTTONS WITH PROXIMITY ******
  /***********************************/
  //button PS0 - PIN 3 - FIRST BYTE FIRST BIT
  if((bb[0] & 0x01) != 0)
  {
    buttons[9]=true;
  }
  else {buttons[9]=false;}
  //-----------------------------------------------
  //button PS1 - PIN 4 - FIRST BYTE SECOND BIT
  if((bb[0] & 0x02) != 0)
  {
    buttons[8]=true;
  }
  else {buttons[8]=false;}
  //-----------------------------------------------
  /**********************************
  /**** BUTTONS WITHOUT PROXIMITY ******
  /***********************************/
  //button CS5 - PIN 9 - FIRST BYTE SIXTH BIT
  if((bb[0] & 0x20) != 0)
  {
    //FIRST BUTTON
    buttons[7]=true;
  }
  else {buttons[7]=false;}
  //-----------------------------------------------
  //button CS6 - PIN 10 - FIRST BYTE SEVENTH BIT
  if((bb[0] & 0x40) != 0)
  {
    //SECOND BUTTON
    buttons[6]=true;
  }
  else {buttons[6]=false;}
  //-----------------------------------------------
  //button CS7 - PIN 11 - FIRST BYTE EIGHTH BIT
  if((bb[0] & 0x80) != 0)
  {
    //THIRD BUTTON
    buttons[5]=true;
  }
  else {buttons[5]=false;}
  //-----------------------------------------------
  //button CS8 - PIN 12 - SECOND BYTE FIRST BIT
  if((bb[1] & 0x01) != 0)
  {
    //FOURTH BUTTON
    buttons[4]=true;
   }
   else{
    buttons[4]=false;
    }
  //-----------------------------------------------
  //button CS2 - PIN 13 - FIRST BYTE THIRD BIT
  if((bb[0] & 0x04) != 0)
  {
    //FIFTH BUTTON
    buttons[3]=true;
  }
  else {buttons[3]=false;}
  //-----------------------------------------------
  //button CS9 - PIN 14 - SECOND BYTE SECOND BIT
  if((bb[1] & 0x02) != 0)
  {
    //SIXTH BUTTON
    buttons[2]=true;
  }
  else {buttons[2]=false;}
  //-----------------------------------------------
  //button CS3 - PIN 15 - FIRST BYTE FOURTH BIT
  if((bb[0] & 0x08) != 0)
  {
    //SEVENTH BUTTON
    buttons[1]=true;
  }
  else {buttons[1]=false;}
  //-----------------------------------------------
  //button CS4 - PIN 16 - FIRST BYTE FIFTH BIT
  if((bb[0] & 0x10) != 0)
  {
    //EIGHTH
    buttons[0]=true;
  }
  else {buttons[0]=false;}

  return buttons;
}
