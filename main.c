#include "printf.h"
#include "i2c.h"
#include "LSM6DS33.h"
#include "uart.h"
#include "guitar.h"
#include "timer.h"
#include "assert.h"
#include <math.h>

void main() {

    timer_init();
    printf_init();
    i2c_init();
    lsm6ds33_init();
    guitar_init();

//calibrate accelerometer  
    short startZ = 0;
    short x, y, z;
        
    for(int i = 0; i < 10; i++) {
        lsm6ds33_read_accelerometer(&x, &y, &z);
        startZ += z/16;
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

        //make average of ten values
        if(cnt == 10) {
            lastTenValues = currTenValues;
            currTenValues = cumm / 10;
      
            //compare the two averages, increment down or up. If not consecutive, subract one
            if(lastTenValues - currTenValues >= 100) {
                down++;                
                if(up!=0) up--; 
            }             
            else if(currTenValues - lastTenValues >= 100) {
                up++;                
                if(down!=0)  down--;                        
            }            
            cnt = 0;
            cumm = 0;
        }
        
        //If more than 4 downs / ups are detected, play down / up
        if(down >= 4) {
          down = 0;
          if(isButtonPressed()) {
              int button = getPressedButton();
              button += 10;
              printf("%d", button);
          }
      }
        else if (up >= 4) {
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
