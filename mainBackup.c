#include "printf.h"
#include "i2c.h"
#include "LSM6DS33.h"
#include "uart.h"
#include "guitar.h"
#include "timer.h"
#include "assert.h"
#include <math.h>

void main() {
//all the initializations
    timer_init();
    printf_init();
    i2c_init();
    lsm6ds33_init();
    guitar_init();

//  printf("whoami=%x\n", lsm6ds33_get_whoami());

//calibrate accelerometer
  
//  short upX = 0;
//  short upY = 0;
  short upZ = 0;

//  short downX = 0;
//  short downY = 0;
//  short downZ = 0;

//  short lastZ = 0;
  short x, y, z;
  
  for(int i = 0; i < 10; i++) {
      lsm6ds33_read_accelerometer(&x, &y, &z);

//      upX += x/16;
//      upY += y/16;
      upZ += z/16;
  //    printf("up accel= (%dmg, %dmg, %dmg)\n", x/16, y/16, z/16);
      delay_us(300000);
  }

//  upX = upX/ 10;
//  upY = upY/10;
  upZ = upZ/ 10;

  assert(upZ >= 1000);
  printf("%d", 8);

  delay_us(3000000);

/*  for(int i = 0; i < 10; i ++) {
      lsm6ds33_read_accelerometer(&x, &y, &z);

      downX += x/16;
      downY += y/16;
      downZ += z/16;

    //  printf("down accel = (%dmg, %dmg, %dmg)\n", x/16, y/16, z/16);
      delay_us(300000);
  }

  downX = downX/10;
  downY = downY/10;
  downZ = downZ/10;

  assert(downZ <= 200);
  printf("%d", 9);*/

//  short threshold = upZ - downZ;
 
 // printf("Calibration Done = UP: %dmg ----- DOWN: %dmg ----- Threshold: %dmg\n", upZ, downZ, threshold);

//  lastZ = upZ;

  int cnt = 0; 
  short cumm = 0;
  short lastTenValues = upZ;
  short currTenValues = upZ;

  int down = 0;
  int up = 0;
  while(1) {
      lsm6ds33_read_accelerometer(&x, &y, &z);
      cumm += z/16;
      cnt++;
//      printf("\n(%dmg) ----- Cumm = %dmg ----- Cnt = %d\n", z/16, cumm, cnt);

      if(cnt == 10) {
          lastTenValues = currTenValues;
          currTenValues = cumm / 10;
//          printf("Last Values: %dmg ----- Curr Values: %dmg \n", lastTenValues, currTenValues);
      
          if(lastTenValues - currTenValues >= 100) {
//            printf("DOWNDOWN\n");
            down++;
            if(up!=0) up = 0;
//            printf("Down: %d ----- Up: %d\n", down, up);
          } 
          else if(currTenValues - lastTenValues >= 100) {
//            printf("UPUP\n");
            up++;
            if(down!=0) down = 0;
//            printf("Down: %d ----- Up: %d\n", down, up);
          }

          cnt = 0;
          cumm = 0;
      }

      if(down >= 3) {
//          printf("DDDDDDDDDDDDDDDDDDDD\n");
          down = 0;
          if(isButtonPressed()) {
              int button = getPressedButton();

              button += 10;
              printf("%d", button);
          }

      }

      else if (up >= 3) {
//          printf("UUUUUUUUUUUUUUUUUUUU\n");
          up = 0;
          if(isButtonPressed()) {
              int button = getPressedButton();
              button += 20;
              printf("%d", button);
          }
      }

      delay_us(1000);

  }

/*  while(1) {
      lsm6ds33_read_accelerometer(&x, &y, &z);

      printf("(%dmg, %dmg, %dmg)\n", x/16, y/16, z/16);


      if(isButtonPressed()) {
          int button = getPressedButton();

          if((lastZ - z/16) >= threshold-100) {
              button += 10;
              printf("%d", button);

              printf("DOWN\n");
          } else if((z/16 - lastZ) >= threshold-100) {
              button += 20;
              printf("%d", button);

              printf("UP\n");
          }
       //   lastZ = z/16;
      }

      lastZ = z/16;
      

      delay_us(250000);

  }*/
}
