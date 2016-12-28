  #include <Arduboy.h>
  #include "animations_bitmaps.h"
  using namespace std;
  
  Arduboy arduboy;
  
  #define WIDTH 12
  #define HEIGHT 18
  
  byte x = 58;
  byte y = 46;
  int state;
  int guy_dir = 2; //Guy direction: 1 == left, 2 == right
  int walkFase = 1;
  
  bool jumping = false; 
  
  void setup() {
    arduboy.beginNoLogo();
    arduboy.setFrameRate(60);
    
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
    if(x <= 250 && x >= 240 ){
      x = 128;
    }
    if(x >= 133 && x <= 140){
      x = 252;
    }
  }
  
  void loop() {
    if (!(arduboy.nextFrame()))
      return;
      
    arduboy.clear();
  
    if(arduboy.pressed(LEFT_BUTTON)){
      guy_dir = 1;
      walk(guy_dir);
    }else if(arduboy.pressed(RIGHT_BUTTON)){
      guy_dir = 2;
      walk(guy_dir);
    }else if(!arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON) && !arduboy.pressed(UP_BUTTON) && !arduboy.pressed(DOWN_BUTTON)){
      stand(guy_dir);
      walkFase = 1;
    }

    notVisible();

    delay(35); //Perfect delay 35

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
