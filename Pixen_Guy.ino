  #include <Arduboy2.h>
  #include <ArduboyPlaytune.h>
  #include "animations_bitmaps.h"
  
  Arduboy2 arduboy;
  ArduboyPlaytune tunes(arduboy.audio.enabled);
  
  #define WIDTH 12
  #define HEIGHT 18
  
  #define ACELERACION 0.2
  
  #define XTAM 128 //El tamaño de la pantalla
  #define YTAM 64
  #define GRAV 0.3 //0.4 was the correct

  #define CLOUD_velocidadMaxima 2

  #define GROUND 45
  
  float x = 58;
  float vel = 0;
  float y = 45; //Pixen Guy default y is "ground"
  float dy = 0;   //Velocidad (lo que se le suma a y por frame)
  float caidaMaxima = 9;
  float velocidadMaxima = 3;
  
  float cloud_y = 30; //random(0, 10)
  float cloud_x = 58;
  float cloud_dx = 0.1;
  float cloud_acx = -0.2;

  float fire_x = 58;
  float fire_y = 41; //41 is the ground of the fire
  
  int guy_dir = 2; //Guy direction: 1 == left, 2 == right
  int ground = 45; //45 is the ground of the pixel guy
  int room = 1;
  
  int walkFase = 1;
  int fireFase = 1;
  
  int counter = 0; //Is use it to make a simple loop, like the "i" in a "for" loop
  int arrowCounter = 0; //The arrow that shows up when you are hide an a corner

  bool login = true; //Boot is true at the beginning
  float xBootLogo = 0; //The x pos of the boot logo
  
  bool doubleJump = true; //Can do doubleJump or not?
  bool didEndJump = false; //Was endJump called already?
  bool ascending = false; //Is ascending? (going up and not falling)
  bool falling = false; // Is falling?
  bool gRunning = false; //Is guy running?
  bool jumping = false; //Is jumping?
  bool des = false;       //Is guy decelerating?
  bool isOnHole = false; // Is on the hole of the room 4?
  bool hasCeiling = true;
  
  void setup() {
    arduboy.boot();
    arduboy.blank();
    arduboy.flashlight();
    arduboy.audio.begin();
    arduboy.setFrameRate(30); //Default is 30    
  }

  void moveLogo(){
    if(xBootLogo < 32-(HEIGHT/2)){
      xBootLogo += 0.8;
      arduboy.drawBitmap(0, xBootLogo, pixenGuyLogo, 126, 18, 1);
      arduboy.setCursor(35, 46);
      arduboy.print("Developed by");
      arduboy.setCursor(39, 56);
      arduboy.print("Jose Fabio Loya");
    }
    else{
      if(counter < 50){
        arduboy.drawBitmap(0, 23, pixenGuyLogo, 126, 18, 1);
        arduboy.setCursor(35, 46);
        arduboy.print("Developed by");
        arduboy.setCursor(39, 56);
        arduboy.print("Jose Fabio Loya");
        counter++;
      }else{
        login = false;
        counter = 0;
      }
    }
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
      if (vel > velocidadMaxima) {
        vel = velocidadMaxima;
      }
    }else if(guy_dir == 1){
      vel -= ACELERACION;
      if (vel < -velocidadMaxima) {
        vel = -velocidadMaxima;
      }
    }
    x += vel;
    
    if(!jumping){    //Here is how it skid automatically  *skid es derrapar en inglés*
      if(vel < 0 && guy_dir == 2){
        arduboy.drawBitmap(x, y, stopL, WIDTH, HEIGHT, 1);
      }
      else if(vel > 0 && guy_dir == 1){
        arduboy.drawBitmap(x, y, stopR, WIDTH, HEIGHT, 1);
      }
      else{
        if(!( arduboy.pressed(A_BUTTON) || arduboy.pressed(UP_BUTTON) )){
          nextWalkFrame(walkFase, guy_dir);
        }
      }
    }
    
    gRunning = true;
  }
  
  void stand(){//pixel
    if(!jumping && !gRunning){
      if(guy_dir == 1){
        arduboy.drawBitmap(x, y, standingL, WIDTH, HEIGHT, 1);
      }else if(guy_dir == 2){
        arduboy.drawBitmap(x, y, standingR, WIDTH, HEIGHT, 1);
      }
    }
  }

  void notVisible(){//pixel
    //Left of the room
    if(x < -18){
      x = 136;
      rooms(room, 1);
    }
    //Right of the room
    if(x > 140){
      x = -14;
      rooms(room, 2);
    }
    
    //If it go down
    if(y > 64){
      y = -18;
      if(room == 4){
        rooms(room, 6);
      }
    }
    //If it go up
    if(y < -18){
      y = 64;
      if(room == 6){
        rooms(room, 4);
      }
    }

    if(hasCeiling && y <= 0){
      y = 1;
      dy -= -0.8; //Touching the ceiling stops the velocity
    }
    

    //The arrow will be shoing up if you hide for 20 frames.
    //Is an arrow made with drawLine() that follow your posY when you are hide on one side of the screen
    if(x <= -10 || x >= 128){
      if(arrowCounter <= 20){ //This arrowCounter is acting like an i in a for loop
        arrowCounter++;
      }
      else{
        if(x <= -10){
          //<-- Arrow
          arduboy.drawFastHLine(2, y+9, 8, WHITE);
          arduboy.drawLine(2, y+9, 4, (y+9)-2, WHITE);
          arduboy.drawLine(2, y+9, 4, (y+9)+2, WHITE);
          arduboy.drawBitmap(12, y+6, miniCostume, 5, 7, 1);
        }
        if(x >= 128){
          arduboy.drawFastHLine(120, y+9, 126, WHITE);
          arduboy.drawLine(127, y+9, 125, (y+9)-2, WHITE);
          arduboy.drawLine(127, y+9, 125, (y+9)+2, WHITE);
          arduboy.drawBitmap(113, y+6, miniCostume, 5, 7, 1);
        }
      }
    }
    else{
      arrowCounter = 0;
    }
    
  }

  void doDoubleJump(){// If doubleJump is true, then you can make a doubleJump.
    if(doubleJump && !onGround(ground)){
      dy = -4.14;
      doubleJump = false;
    }
  }

  boolean onGround(int iGround){ //GROUND is the real ground = 45, ground is the variable ground. So you can ask for GROUND or for ground.
    if(y < iGround){
      return false;
    }
    else{
      return true;
    }
  }

  void endJump(){// This func is called when you relese the jump button. If you are trying to get high you wont relese the button (...)
    //(...) but if you relese the button this func will decrese the velocity.
    didEndJump = true;
    if(dy < -0.4){
      dy -= -0.4;
    }
  }

  void startJump(){
    if(onGround(GROUND)){
      dy = -4.14; //El primer impulso, el mejor es 3.14 para que no toque el techo
    }
  }

  void firstJumpFrame(){//jump
    if(guy_dir == 1){
      arduboy.drawBitmap(x, y, jumpL, WIDTH, HEIGHT, 1);
    }
    else if(guy_dir == 2){
      arduboy.drawBitmap(x, y, jumpR, WIDTH, HEIGHT, 1);
    }
  }
  
  void jumpFrames(){//jump
    if(guy_dir == 1){
      if(ascending == true){
        arduboy.drawBitmap(x, y, jumpL, WIDTH, HEIGHT, 1);
      }
      else if(falling == true){
        arduboy.drawBitmap(x, y, fallL, WIDTH, HEIGHT, 1);
        
        if(arduboy.pressed(DOWN_BUTTON)){ //The unbrella
          arduboy.drawBitmap(x, y-8, umbrella, 9, 8, 1);
          caidaMaxima = 1.5;
        }
        else{
          caidaMaxima = 6;
        }
      }
    }
    else if(guy_dir == 2){
      if(ascending == true){
        arduboy.drawBitmap(x, y, jumpR, WIDTH, HEIGHT, 1);
      }
      else if(falling == true){
        arduboy.drawBitmap(x, y, fallR, WIDTH, HEIGHT, 1);
        
        if(arduboy.pressed(DOWN_BUTTON)){ //The unbrella
          arduboy.drawBitmap(x-1, y-8, umbrella, 9, 8, 1);
          caidaMaxima = 1.5;
        }
        else{
          caidaMaxima = 6;
        }
        
      }
    }
  }

  void printA(String alarm){ //Easy print alarm to debug the game
    arduboy.setCursor(0, 0);
    arduboy.print(alarm);
  }

  void jump(){//jump
    
    if(dy < caidaMaxima){
      dy += GRAV;
    }
    else{
      dy = caidaMaxima;
    }
    
    if(y + dy >= ground){
      doubleJump = true;
      didEndJump = false;
      falling = false;
      ascending = false;
      jumping = false;
      dy = 0.0;
      y = GROUND;
      
      if(!(arduboy.pressed(UP_BUTTON) || arduboy.pressed(A_BUTTON))){
        stand();
      }
      else{
        firstJumpFrame();
      }
    }
    else{
      y += dy;
      jumping = true;
    }
    
    jumpFrames();
  }

  void cloud(){

    cloud_dx += cloud_acx;
    if (cloud_dx > CLOUD_velocidadMaxima && cloud_acx > 0) {            //Move forwards and backwards
      cloud_acx = cloud_acx * (-1);
      cloud_dx = CLOUD_velocidadMaxima;
    }
    else if(cloud_dx < (CLOUD_velocidadMaxima * -1) && cloud_acx < 0){
      cloud_acx = cloud_acx * (-1);
      cloud_dx = CLOUD_velocidadMaxima * -1;
    }
        
    if(!(cloud_x+1 == x) || !(cloud_x-1 == x)){                       //Follow your x pos
      if(x >= cloud_x){
        cloud_x = cloud_x + 0.5;
      }
      else if(x <= cloud_x){
        cloud_x = cloud_x - 0.5;
      }
    }

    if(cloud_x <= 2){
      cloud_x = 2;
    }
    else if(cloud_x >= 128-19){
      cloud_x = 128-19;
    }

    //This detect if pixen guy is touching  the cloud
    if(( (cloud_y <= y+HEIGHT && cloud_y >= y) || (y <= cloud_y+7 && y >= cloud_y) ) && ( (cloud_x <= x+WIDTH && cloud_x >= x) || (x <= cloud_x+17 && x >= cloud_x) ))
    {
      caidaMaxima = 0.3;
      velocidadMaxima = 0.3;
      doubleJump = true;
    }
    // Else if not touching the cloud
    else if(!(( (fire_y <= y+(HEIGHT-8) && fire_y >= y) || (y <= fire_y+14 && y >= fire_y) ) && ( (fire_x <= x+(WIDTH-2) && fire_x >= x) || (x <= fire_x+5 && x >= fire_x) )))
    {
      velocidadMaxima = 3;
    }

    cloud_x = cloud_dx + cloud_x;
    
    arduboy.drawBitmap(cloud_x, cloud_y, cloud_1, 17, 7, WHITE);
  }

  void fire(){ //El fuego tiene 6 imagenes diferentes. fireFase determina en que fase está para asignar a su respectivo frame.
    if(fireFase >= 1 && fireFase <= 3){
      arduboy.drawBitmap(fire_x, fire_y, fire_1, 7, 22, 1);
      fireFase++;
      fire_y = 40;
    }else if(fireFase >= 4 && fireFase <= 6){
      arduboy.drawBitmap(fire_x, fire_y, fire_2, 7, 22, 1);
      fireFase++;
    }else if(fireFase >= 7 && fireFase <= 9){
      arduboy.drawBitmap(fire_x, fire_y, fire_3, 7, 22, 1);
      fireFase++;
    }else if(fireFase >= 10 && fireFase <= 13){
      arduboy.drawBitmap(fire_x, fire_y, fire_4, 7, 22, 1);
      fireFase++;
      fire_y = 39;
    }else if(fireFase >= 14 && fireFase <= 16){
      arduboy.drawBitmap(fire_x, fire_y, fire_5, 7, 22, 1);
      fireFase++;
    }else if(fireFase >= 17 && fireFase <= 19){
      arduboy.drawBitmap(fire_x, fire_y, fire_6, 7, 22, 1);
      fireFase++;
    }else{
      fireFase = 1;
      arduboy.drawBitmap(fire_x, fire_y, fire_1, 7, 22, 1);
    }

    //This detect if the fire is touching you
    if(( (fire_y <= y+(HEIGHT-8) && fire_y >= y) || (y <= fire_y+14 && y >= fire_y) ) && ( (fire_x <= x+(WIDTH-2) && fire_x >= x) || (x <= fire_x+5 && x >= fire_x) ))
    {
      if(guy_dir == 1){
        vel = 8;
      }
      if(guy_dir == 2){
        vel = (-8);
      }
    }
    else if(!(( (cloud_y <= y+HEIGHT && cloud_y >= y) || (y <= cloud_y+7 && y >= cloud_y) ) && ( (cloud_x <= x+WIDTH && cloud_x >= x) || (x <= cloud_x+17 && x >= cloud_x) ))) //Si no está tocando la nuve
    { 
      
    }
  }

  void rooms(int r, int where){ //r is the room you are and where is the side that you´r going
    room = r;

    //(where == 1) is left and (where == 2) is right
    if(where == 2){
      room++;
      if(room == 6){
        room = 1;
      }
    }
    else if(where == 1){
      room--;
    }
    else if(where > 2){
      room = where;
    }

    switch(room){ //This is where rooms are made
      case 1:
        ground = 45;
        arduboy.drawBitmap(64-32, 5, miniPGLogo, 63, 9, 1);
        arduboy.drawFastHLine(0, 63, 128, WHITE);
        arduboy.drawFastHLine(0, 0, 128, WHITE);
        hasCeiling = true;
        break;
        
      case 2:
        ground = 45;
        fire();
        arduboy.drawFastHLine(0, 63, 128, WHITE);
        arduboy.drawFastHLine(0, 0, 128, WHITE);
        hasCeiling = true;
        break;
        
      case 3:
        ground = 45;
        cloud_y = 30;
        arduboy.drawFastHLine(0, 63, 128, WHITE);
        arduboy.drawFastHLine(0, 0, 128, WHITE);
        hasCeiling = true;
        cloud();
        break;
        
      case 4:
        arduboy.drawFastHLine(0, 63, 49, WHITE);
        arduboy.drawFastHLine(79, 63, 128, WHITE);
        arduboy.drawFastHLine(0, 0, 128, WHITE);
        hasCeiling = true;
        
        if(x > 47 && x < 72 && y >= GROUND -5){ //El -5 le quita un pequeño error que tenía al caer directamente en la grieta
          isOnHole = true;
          
          if(onGround(ground)){            
            if(guy_dir == 1){
              arduboy.drawBitmap(x, y, fallL, WIDTH, HEIGHT, 1);
            }else if(guy_dir == 2){
              arduboy.drawBitmap(x, y, fallR, WIDTH, HEIGHT, 1);
            }
          }
          
          jumping = true;
          ground = 90;
        }
        if(!(x > 47 && x < 72) && isOnHole){
          if(x < 47 && y > GROUND || x > 72 && y > GROUND){
            if(x < 47 && y > GROUND){
              x = 47;
            }
            if(x > 72 && y > GROUND){
              x = 72;
            }
          }
          else{
            isOnHole = false;
            ground = 45;
          }
          
        }
        break;
      
      case 5:
        ground = 45;
        cloud_y = 50;
        cloud();
        arduboy.drawFastHLine(0, 63, 128, WHITE);
        arduboy.drawFastHLine(0, 0, 128, WHITE);
        hasCeiling = true;
        break;

      case 6: //Cuarto de abajo
        ground = 45;
        
        arduboy.drawBitmap(52, 56, trampoline, 25, 8, 1);
        
        //Techo
        arduboy.drawFastHLine(0, 0, 49, WHITE);
        arduboy.drawFastHLine(79, 0, 128, WHITE);
        hasCeiling = false; //Si tiene, pero le falta un poco, por eso lo ponemos en false
        
        //Paredes
        arduboy.drawFastVLine(0, 0, 64, WHITE);
        arduboy.drawFastVLine(127, 0, 64, WHITE);
        
        //Piso
        arduboy.drawFastHLine(0, 63, 128, WHITE);

        //wont let you pass left
        if(x < 1){
          x = 1;
          vel += 4.5;
        }
        //wont let you pass rigth
        if(x > 117){
          x = 117;
          vel -= 4.5;
        }
        
        //Touching the trampoline
        if(y > 37 && (x > 42 && x < 77)){
          dy = -11;
          doubleJump = true;
//          firstJumpFrame();
        }

        //The hole on the top
        if(y < 2 && x > 47 && x < 72)
        {
          isOnHole = true;
        }
        
        if(y >= 3 && isOnHole)
        {
          isOnHole = false;
        }
        
        if( (x <= 47 || x >= 72) && isOnHole )
        {
          if(x <= 47){
            x = 46;
            vel = -0.5;
          }
          if(x >= 72){
            x = 71;
            vel = 0.5;
          }
        }

        //Touching the ceiling
        if(!isOnHole && y < 1){
          y = 1;
          dy -= -0.8; //Touching the ceiling stops the velocity
        }
        
        break;
        
      default:
        if(room > 5){
          room = 1;
        }
        else if(room < 1){
          room = 5;
        }
        break;
        
    }
  }

  void sentences(){
    notVisible();
    rooms(room, 0); //0 means nothing, this just call the function rooms
    
    if(arduboy.pressed(UP_BUTTON) || arduboy.pressed(A_BUTTON))
    {  
      if(onGround(ground))
      {
        firstJumpFrame();
        startJump();
      }
      jumping = true;
    }
    else if(onGround(ground))
    {
      jumping = false;
    }
    
    if(arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)){
      guy_dir = 1;
      gRunning = true;
    }
    
    else if(arduboy.pressed(RIGHT_BUTTON) && !arduboy.pressed(LEFT_BUTTON)){
      guy_dir = 2;
      gRunning = true;
    }
    
    if(!gRunning && !jumping){
      stand();
    }
    
  }

  void loopSentences(){

    jump();
    
    if(jumping){
      
      if(arduboy.pressed(UP_BUTTON) || arduboy.pressed(A_BUTTON)){
        if(didEndJump && doubleJump){
          doDoubleJump();
        }
      }
      
      if(!arduboy.pressed(UP_BUTTON) && !arduboy.pressed(A_BUTTON)){
        endJump();
      }
    }
    
    if(!onGround(ground)){ //Esto determina si está ascendiendo o cayendo
      if(dy > 0){
        ascending = false;
        falling = true;
      }
      else{
        ascending = true;
        falling = false;
      }
    }
    else{
      ascending = false;
      falling = false;
    }

    if(gRunning){
      
      if(arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(LEFT_BUTTON)){
        walk();
      }
      
      else if(vel > 0){
        vel -= ACELERACION;
        x += vel;

        if(vel <= 0){
          vel = 0;
          gRunning = false;
          stand();
        }

        if(!jumping){
          if(vel < 0){
            arduboy.drawBitmap(x, y, stopL, WIDTH, HEIGHT, 1);
          }
          else if(vel > 0){
            arduboy.drawBitmap(x, y, stopR, WIDTH, HEIGHT, 1);
          }
        }
      }
      else{
        vel += ACELERACION;
        x += vel;

        if(vel >= 0){
          vel = 0;
          gRunning = false;
          stand();
        }
        
        if(!jumping){
          if(vel < 0){
            arduboy.drawBitmap(x, y, stopL, WIDTH, HEIGHT, 1);
          }
          else if(vel > 0){
            arduboy.drawBitmap(x, y, stopR, WIDTH, HEIGHT, 1);
          }
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
      
      

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////RESET////////////////////////////////////////////////////////////  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

      if(arduboy.pressed(B_BUTTON)){ //Reset the game
        if(counter > 60){ //"For" loop where counter is "i"
          x = 58;
          vel = 0;
          y = 45; //Pixen Guy default y is "ground"
          dy = 0;   //Velocidad (lo que se le suma a y por frame)
          caidaMaxima = 9;
          velocidadMaxima = 3;
          
          cloud_y = 30; //random(0, 10)
          cloud_x = 58;
          cloud_dx = 0.1;
          cloud_acx = -0.2;
        
          fire_x = 58;
          fire_y = 41; //41 is the ground of the fire
          
          guy_dir = 2; //Guy direction: 1 == left, 2 == right
          ground = 45; //45 is the ground of the pixel guy
          room = 1;
          
          walkFase = 1;
          fireFase = 1;
          
          counter = 0; //Is use it to make a simple loop, like the "i" in a "for" loop
          arrowCounter = 0; //The arrow that shows up when you are hide an a corner
        
          login = true; //Boot is true at the beginning
          xBootLogo = 0; //The x pos of the boot logo
          
          doubleJump = true; //Can do doubleJump or not?
          didEndJump = false; //Was endJump called already?
          ascending = false; //Is ascending? (going up and not falling)
          falling = false; // Is falling?
          gRunning = false; //Is guy running?
          jumping = false; //Is jumping?
          des = false;       //Is guy decelerating?
          isOnHole = false; // Is on the hole of the room 4?
          hasCeiling = true;

          arduboy.setRGBled(0, 0, 0);
           
        }else{
          counter++;

          //Timer (1, 2, 3... Reset)
          if(counter >= 10 && counter <= 29){
            arduboy.setCursor(60, 0);
            arduboy.print("1");
          }
          else if(counter >= 30 && counter <= 49){
            arduboy.setCursor(60, 0);
            arduboy.print("2");
          }
          else if(counter >= 50){
            arduboy.setCursor(60, 0);
            arduboy.print("3");
          }
        }
      }
      else { //If you decide to not reset the game it reset the counter
        counter = 0;
      }
    
    }
   
//    arduboy.setCursor(0, 0);
//    arduboy.print(isOnHole);
//    arduboy.setCursor(0, 8);
//    arduboy.print(jumping);
//    arduboy.setCursor(0, 16);
//    arduboy.print(gRunning);
    
//    arduboy.setCursor(40, 0);
//    arduboy.print(ascending);
//    arduboy.setCursor(40, 8);
//    arduboy.print(falling);
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
