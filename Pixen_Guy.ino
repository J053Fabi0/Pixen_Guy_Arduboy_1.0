  #include <Arduboy.h>
  #include "animations_bitmaps.h"
  
  Arduboy arduboy;
  
  #define WIDTH 12
  #define HEIGHT 18
  
  #define ACELERACION 0.2
  #define VELOCIDAD_MAX 3
  
  #define XTAM 128 //El tamaño de la pantalla
  #define YTAM 64
  #define GRAV 0.4
  
  float x = 58;
  float vel = 0;
  float y = 45;
  float dy = 0;   //Velocidad (lo que se le suma a y por frame)
  
  int guy_dir = 2; //Guy direction: 1 == left, 2 == right
  int walkFase = 1;
  int xLogo = 0;

  bool login = true;
  
  bool doubleJump = true;
  bool didEndJump = false; //Was endJump called already?
  bool ascending = false;
  bool falling = false;
  bool onGround = true;
  bool gRunning = false;
  bool jumping = false;
  bool des = false;       //Is guy decelerating?
  
  void setup() {
    arduboy.beginNoLogo();
    arduboy.setFrameRate(30);
  }

  void moveLogo(){
    if(xLogo < 32-(HEIGHT/2)){
      xLogo += 1;
    }else{
      login = false;
    }
    arduboy.drawBitmap(0, xLogo, pixenGuyLogo, 126, 18, 1);
  }
  
  void nextWalkFrame(int fase, int dir){//walk
    if(dir == 1){
      if(fase == 1){
        arduboy.drawBitmap(x, y, costumeL1, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 2){
        arduboy.drawBitmap(x, y, costumeL2, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 3){
        arduboy.drawBitmap(x, y, costumeL3, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 4){
        arduboy.drawBitmap(x, y, costumeL4, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 5){
        arduboy.drawBitmap(x, y, costumeL5, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 6){
        arduboy.drawBitmap(x, y, costumeL6, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 7){
        arduboy.drawBitmap(x, y, costumeL7, WIDTH, HEIGHT, 1);
        walkFase = 1;
      }
    }else if(dir == 2){
      if(fase == 1){
        arduboy.drawBitmap(x, y, costumeR1, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 2){
        arduboy.drawBitmap(x, y, costumeR2, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 3){
        arduboy.drawBitmap(x, y, costumeR3, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 4){
        arduboy.drawBitmap(x, y, costumeR4, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 5){
        arduboy.drawBitmap(x, y, costumeR5, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 6){
        arduboy.drawBitmap(x, y, costumeR6, WIDTH, HEIGHT, 1);
        walkFase++;
      }else if(fase == 7){
        arduboy.drawBitmap(x, y, costumeR7, WIDTH, HEIGHT, 1);
        walkFase = 1;
      }
    }
  }
  
  void walk(){//walk
    if(guy_dir == 2){
      vel += ACELERACION;
      if (vel > VELOCIDAD_MAX) {
        vel = VELOCIDAD_MAX;
      }
    }else if(guy_dir == 1){
      vel -= ACELERACION;
      if (vel < -VELOCIDAD_MAX) {
        vel = -VELOCIDAD_MAX;
      }
    }
    x += vel;
    
    if(!jumping){
      nextWalkFrame(walkFase, guy_dir);
    }
    
    gRunning = true;
  }
  
  void stand(){//pixel
    if(guy_dir == 1){
      arduboy.drawBitmap(x, y, standingL, WIDTH, HEIGHT, 1);
    }else if(guy_dir == 2){
      arduboy.drawBitmap(x, y, standingR, WIDTH, HEIGHT, 1);
    }
  }

  void notVisible(){//pixel
    if(x <= -18 && x >= -22 ){
      x = 136;
    }
    if(x >= 140 && x <= 144){
      x = -14;
    }
  }

  void doDoubleJump(){//jump
    if(doubleJump && !onGround){
    dy = -1.7/2 +0.2;
    doubleJump = false;
    }
  }

  void startJump(){//jump
    if(onGround){
      dy = -1.7/2 +0.1; //El primer impulso, el mejor es 3.14 para que no toque el techo
      onGround = false;
      y = 45; //YTAM - HEIGHT -3
    }
  }

  void endJump(){//jump
    didEndJump = true;
    if(dy < 3){
      dy -= -0.3;
    }
  }

  void firstJumpFrame(){//jump
    if(dy == 0.0){
      if(y < 45){
        y = 45;
      }
      if(guy_dir == 1){
        arduboy.drawBitmap(x, y, jumpL, WIDTH, HEIGHT, 1);
      }else if(guy_dir == 2){
        arduboy.drawBitmap(x, y, jumpR, WIDTH, HEIGHT, 1);
      }
    }
  }
  
  void jumpFrames(){//jump
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

  void jump(){//jump
    dy += GRAV;
    y += dy;
    if(y <= 0){
      y = 0;
    }
    
    jumpFrames();
  }

  void sentences(){
    notVisible();
    
    if(arduboy.pressed(UP_BUTTON)){
      firstJumpFrame();
      jumping = true;
    }
    
    else if(arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)){
      guy_dir = 1;
      gRunning = true;
    }
    
    else if(arduboy.pressed(RIGHT_BUTTON) && !arduboy.pressed(LEFT_BUTTON)){
      guy_dir = 2;
      gRunning = true;
    }
    else if(!gRunning && !jumping){
      stand();
    }
  }

  void loopSentences(){
    if(jumping){
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
      
      if(y > 45){
        onGround = true;
        doubleJump = true;
        didEndJump = false;
        jumping = false;
        falling = false;
        ascending = false;
        dy = 0.0;
        y = 45; //YTAM - HEIGHT -3
      }
    }

    if(dy > 3 && !onGround){
      ascending = false;
      falling = true;
    }
    else if(dy < 0 && !onGround){
      ascending = true;
      falling = false;
    }

    if(gRunning){
      
      if(arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(LEFT_BUTTON)){
        walk();
      }
      
      else if(vel > 0){
        vel -= ACELERACION;
        x += vel;

        if(!jumping){
          if(guy_dir == 1){
            arduboy.drawBitmap(x, y, stopL, WIDTH, HEIGHT, 1);
          }
          else{
            arduboy.drawBitmap(x, y, stopR, WIDTH, HEIGHT, 1);
          }
        }
        
        if(vel <= 0){
          vel = 0;
          gRunning = false;
        }
      }
      else{
        vel += ACELERACION;
        x += vel;
        
        if(!jumping){
          if(guy_dir == 1){
            arduboy.drawBitmap(x, y, stopL, WIDTH, HEIGHT, 1);
          }
          else{
            arduboy.drawBitmap(x, y, stopR, WIDTH, HEIGHT, 1);
          }
        }
        
        if(vel >= 0){
          vel = 0;
          gRunning = false;
        }
      }
    }

  }

  
  void loop() {
    if (!(arduboy.nextFrame()))
      return;

    arduboy.clear();

    if(login){
      moveLogo();
    }
    else{
      
      sentences();
      loopSentences();

      arduboy.drawFastHLine(0, 63, 128, WHITE);
    
    }
    
//    arduboy.setCursor(0, 0);
//    arduboy.print(vel);
//    arduboy.setCursor(0, 8);
//    arduboy.print(gRunning);
//    arduboy.setCursor(0, 16);
//    arduboy.print();
    
//    arduboy.setCursor(40, 0);
//    arduboy.print(vel);
//    arduboy.setCursor(40, 8);
//    arduboy.print(des);
//    arduboy.setCursor(40, 16);
//    arduboy.print(onGround);

    arduboy.display();
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
