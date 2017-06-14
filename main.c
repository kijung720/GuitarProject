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
  
    short startZ = 0;
    short x, y, z;
        
    for(int i = 0; i < 10; i++) {
        lsm6ds33_read_accelerometer(&x, &y, &z);
        startZ += z/16;
//        printf("up accel= (%dmg, %dmg, %dmg)\n", x/16, y/16, z/16);
        delay_us(300000);
    }
    
    startZ = startZ/ 10;
    
    assert(startZ >= 1000);
    printf("%d", 8);
    
    delay_us(3000000);
        
    int cnt = 0;
    short cumm = 0;
    short lastTenValues = startZ;
    short currTenValues = startZ;
    
    int down = 0;
    int up = 0;
    
    while(1) {
        lsm6ds33_read_accelerometer(&x, &y, &z);
        cumm += z/16;
        cnt++;
//        printf("\n(%dmg) ----- Cumm = %dmg ----- Cnt = %d\n", z/16, cumm, cnt);

        if(cnt == 10) {
            lastTenValues = currTenValues;
            currTenValues = cumm / 10;
//            printf("Last Values: %dmg ----- Curr Values: %dmg \n", lastTenValues, currTenValues);
      
            if(lastTenValues - currTenValues >= 100) {
//                printf("DOWNDOWN\n");
                down++;                
                if(up!=0) up--; 
//                printf("Down: %d ----- Up: %d\n", down, up);
            }             
            else if(currTenValues - lastTenValues >= 100) {
//                printf("UPUP\n");
                up++;                
                if(down!=0)  down--;
                
//                printf("Down: %d ----- Up: %d\n", down, up);            
            }            
            cnt = 0;
            cumm = 0;
        }
        
        if(down >= 4) {
//          printf("DDDDDDDDDDDDDDDDDDDD\n");
          down = 0;
          if(isButtonPressed()) {
              int button = getPressedButton();
              button += 10;
              printf("%d", button);
          }
      }
        else if (up >= 4) {
//          printf("UUUUUUUUUUUUUUUUUUUU\n");
          up = 0;
          if(isButtonPressed()) {
              int button = getPressedButton();
              button += 20;
              printf("%d", button);
          }
      }
      delay_us(500);
  }
}
