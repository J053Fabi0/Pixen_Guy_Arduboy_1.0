  #include <Arduboy.h>
  #include "animations_bitmaps.h"
  using namespace std;
  
  Arduboy arduboy;
  
  #define WIDTH 12
  #define HEIGHT 18

  const int XTAM = 128; //El tamaño de la pantalla
  const int YTAM = 64;
  const float GRAV = 0.4;
  
  float x = 58;
  float y = 46;
  float dy = 0; //Velocidad (lo que se le suma a y por frame)
  
  int guy_dir = 2; //Guy direction: 1 == left, 2 == right
  int walkFase = 1;
  
  bool doubleJump = true;
  bool didEndJump = false; //was endJump called already
  bool ascending = false;
  bool falling = false;
  bool onGround = true;
  bool gRunning = false;
  bool jumping = false;
  
  void setup() {
    arduboy.beginNoLogo();
    arduboy.setFrameRate(30);
  }
  
  void nextWalkFrame(int fase, int dir){
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

  void moveX(){
    
  }
  
  void walk(int guy_direction){
    if(guy_direction == 1){
      //walk left
      nextWalkFrame(walkFase, guy_direction);
      x = x - 2;
    }else if(guy_direction == 2){
      //walk right
      nextWalkFrame(walkFase, guy_direction);
      x = x + 2;
    }
  }
  
  void stand(int guy_dir){
    if(guy_dir == 1){
      arduboy.drawBitmap(x, y, standingL, WIDTH, HEIGHT, 1);
    }else if(guy_dir == 2){
      arduboy.drawBitmap(x, y, standingR, WIDTH, HEIGHT, 1);
    }
  }

  void notVisible(){
    if(x <= -16 && x >= -20 ){
      x = 136;
    }
    if(x >= 138 && x <= 140){
      x = -14;
    }
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

  
  void loop() {
    if (!(arduboy.nextFrame()))
      return;
      
    arduboy.clear();
  
    if(arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)){
      if(arduboy.pressed(UP_BUTTON)){
        firstJumpFrame();
        jumping = true;
        x -= 2;
        guy_dir = 1;
      }else{
        if(jumping == true){
          jumping = true;
          x -= 2;
          guy_dir = 1;
        }else{
          guy_dir = 1;
          walk(guy_dir);
          gRunning = true;
        }
      }
    }else if(arduboy.pressed(RIGHT_BUTTON) && !arduboy.pressed(LEFT_BUTTON)){
      if(arduboy.pressed(UP_BUTTON)){
        firstJumpFrame();
        jumping = true;
        x += 2;
        guy_dir = 2;
      }else{
        if(jumping == true){
          jumping = true;
          x += 2;
          guy_dir = 2;
        }else{
          guy_dir = 2;
          walk(guy_dir);
          gRunning = true;
        }
      }
    }else if(arduboy.pressed(UP_BUTTON)){
      firstJumpFrame();
      jumping = true;
      
    }else if(!arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON) && !arduboy.pressed(UP_BUTTON)&& onGround || arduboy.pressed(RIGHT_BUTTON) && arduboy.pressed(LEFT_BUTTON) && onGround){
      stand(guy_dir);
      walkFase = 1;
      gRunning = false;
      y = 46;
    }

    if(dy > 3 && !onGround){
      ascending = false;
      falling = true;
    }else if(dy < 0 && !onGround){
      ascending = true;
      falling = false;
    }

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
      
      if(y > 46){
        onGround = true;
        doubleJump = true;
        didEndJump = false;
        jumping = false;
        falling = false;
        ascending = false;
        dy = 0.0;
        y = 46;
      }
    }

//    arduboy.setCursor(0, 0);
//    arduboy.print(dy);
//    arduboy.setCursor(0, 8);
//    arduboy.print(y);
//    arduboy.setCursor(0, 16);
//    arduboy.print(x);
//    
//    arduboy.setCursor(40, 0);
//    arduboy.print(ascending);
//    arduboy.setCursor(40, 8);
//    arduboy.print(falling);
//    arduboy.setCursor(40, 16);
//    arduboy.print(onGround);

    notVisible();

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
