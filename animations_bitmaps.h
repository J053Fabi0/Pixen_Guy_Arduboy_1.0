  //Standing Left and Right//
  const unsigned char standingL[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0xc3, 0xc3, 
  0x3f, 0x3f, 0xc3, 0xc3, 0x0c, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char standingR[] PROGMEM = {
  0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0xc3, 0xc3, 
  0x3f, 0x3f, 0xc3, 0xc3, 0x0c, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  
  //Jumping//
  const unsigned char fall[] PROGMEM = {
  0x0c, 0x0c, 0x30, 0x30, 0xff, 0xff, 0x3c, 0x3c, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x30, 0x30, 
  0x3f, 0x3f, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char jump[] PROGMEM = {
  0x00, 0x00, 0xc0, 0xc0, 0xff, 0xff, 0xcf, 0xcf, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0xf0, 0xf0, 
  0xcf, 0xcf, 0x30, 0x30, 0x03, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  
  //Shield or down//
  const unsigned char dock1[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0xc3, 0xc3, 
  0x3f, 0x3f, 0xf3, 0xf3, 0x0c, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char dock2[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x30, 0x30, 
  0xff, 0xff, 0xcf, 0xcf, 0xf0, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 
  0x03, 0x03, 0x00, 0x00, 
  };
  
  //Running//
  
  //Left//
  
  const unsigned char costumeL1[] PROGMEM = {
  0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 
  0xcf, 0xcf, 0xf0, 0xf0, 0xc0, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeL2[] PROGMEM = {
  0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 
  0x0f, 0x0f, 0xfc, 0xfc, 0xc0, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeL3[] PROGMEM = {
  0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x33, 0x33, 
  0xcf, 0xcf, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x03, 0x00, 0x00, 
  };
  
  const unsigned char costumeL4[] PROGMEM = {
  0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0xc0, 0xc0, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 
  0xcf, 0xcf, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 
  0x03, 0x03, 0x03, 0x03, 
  };
  
  const unsigned char costumeL5[] PROGMEM = {
  0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0xc0, 0xc0, 
  0xc0, 0xc0, 0x00, 0x00, 0x03, 0x03, 0xcc, 0xcc, 
  0xcf, 0xcf, 0x30, 0x30, 0xc0, 0xc0, 0x30, 0x30, 
  0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeL6[] PROGMEM = {
  0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0xc0, 0xc0, 
  0xc0, 0xc0, 0x00, 0x00, 0xc3, 0xc3, 0xcc, 0xcc, 
  0xcf, 0xcf, 0x30, 0x30, 0xc0, 0xc0, 0x30, 0x30, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeL7[] PROGMEM = {
  0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 
  0xcf, 0xcf, 0x33, 0x33, 0xc0, 0xc0, 0xc0, 0xc0, 
  0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  //Right//
  
  const unsigned char costumeR1[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0xc0, 0xc0, 
  0xf0, 0xf0, 0xcf, 0xcf, 0x03, 0x03, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeR2[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0xc0, 0xc0, 
  0xfc, 0xfc, 0x0f, 0x0f, 0x03, 0x03, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeR3[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0xf0, 0xf0, 0xcf, 0xcf, 0x33, 0x33, 0x03, 0x03, 
  0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeR4[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 
  0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0xf0, 0xf0, 0xcf, 0xcf, 0x0c, 0x0c, 0x00, 0x00, 
  0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeR5[] PROGMEM = {
  0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 
  0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0x30, 0xc0, 0xc0, 
  0x30, 0x30, 0xcf, 0xcf, 0xcc, 0xcc, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 
  };
  
  const unsigned char costumeR6[] PROGMEM = {
  0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 
  0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0x30, 0xc0, 0xc0, 
  0x30, 0x30, 0xcf, 0xcf, 0xcc, 0xcc, 0xc3, 0xc3, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 
  };
  
  const unsigned char costumeR7[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xf0, 0xf0, 0xf0, 0xf0, 0xc0, 0xc0, 0xc0, 0xc0, 
  0x33, 0x33, 0xcf, 0xcf, 0x0c, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x03, 0x00, 0x00, 
  };
  
  
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////