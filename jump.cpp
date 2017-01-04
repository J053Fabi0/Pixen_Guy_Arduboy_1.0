  #include "jump.h"
  #include "animations_bitmaps.h"

  float dy = 0; //Velocidad (lo que se le suma a y por frame)

  bool doubleJump = true;
  bool didEndJump = false; //was endJump called already
  bool ascending = false;
  bool falling = false;
  bool onGround = true;
  bool jumping = false;

  bool getOnGround(){
    return onGround;
  }
  
  void doDoubleJump(){
    if(doubleJump && !onGround){
    dy = -1.7/2 +0.2;
    doubleJump = false;
    }
  }

  void startJump(){
    if(onGround){
      dy = -1.7/2 +0.1; //El primer impulso, el mejor es 3.14 para que no toque el techo
      onGround = false;
      y = YTAM - HEIGHT -2;
    }
  }

  void endJump(){
    didEndJump = true;
    if(dy < 3){
      dy -= -0.3;
    }
  }

  void firstJumpFrame(){
    if(!(dy != 0.0)){
      if(y < YTAM - HEIGHT){
        y = y > YTAM - HEIGHT;
      }
      if(guy_dir == 1){
        arduboy.drawBitmap(x, y, jumpL, WIDTH, HEIGHT, 1);
      }else if(guy_dir == 2){
        arduboy.drawBitmap(x, y, jumpR, WIDTH, HEIGHT, 1);
      }
    }
  }
  
  void jumpFrames(){
    if(guy_dir == 1){
      if(ascending == true){
        arduboy.drawBitmap(x, y, jumpL, WIDTH, HEIGHT, 1);
      }else if(falling == true){
        arduboy.drawBitmap(x, y, fallL, WIDTH, HEIGHT, 1);
      }
    }else if(guy_dir == 2){
      if(ascending == true){
        arduboy.drawBitmap(x, y, jumpR, WIDTH, HEIGHT, 1);
      }else if(falling == true){
        arduboy.drawBitmap(x, y, fallR, WIDTH, HEIGHT, 1);
      }
    }
  }

  void jump(){
    dy += GRAV;
    y += dy;
    if(y <= 0){
      y = 0;
    }
    
    jumpFrames();
  }

  void updateJ(){
    y -= 4;
    if(arduboy.pressed(UP_BUTTON)){
      if(!didEndJump){
        startJump();
      }else if(didEndJump && doubleJump){
        doDoubleJump();
      }
    }
    if(!arduboy.pressed(UP_BUTTON)){
      endJump();
    }
    
    jump();
      
    if(y > 46){
      onGround = true;
      doubleJump = true;
      didEndJump = false;
      setJumping(false);
      falling = false;
      ascending = false;
      dy = 0.0;
      y = 46;
    }

    if(dy > 3 && !onGround){
      ascending = false;
      falling = true;
    }else if(dy < 0 && !onGround){
      ascending = true;
      falling = false;
    }
  }

  
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
