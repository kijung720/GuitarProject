#include "gpio.h"
#include "gpioextra.h"
#include "gpioevent.h"
#include "i2c.h"
#include "lsm6ds33.h"

#define MINOR GPIO_PIN25
#define SEVEN GPIO_PIN24
#define C_CHORD GPIO_PIN21
#define D_CHORD GPIO_PIN20
#define E_CHORD GPIO_PIN16
#define F_CHORD GPIO_PIN12
#define G_CHORD GPIO_PIN1
#define A_CHORD GPIO_PIN7
#define B_CHORD GPIO_PIN8

//initializes all the gpio functions
void guitar_init() {
    gpio_set_input(MINOR);
    gpio_set_input(SEVEN);
    gpio_set_input(C_CHORD);
    gpio_set_input(D_CHORD);
    gpio_set_input(E_CHORD);
    gpio_set_input(F_CHORD);
    gpio_set_input(G_CHORD);
    gpio_set_input(A_CHORD);
    gpio_set_input(B_CHORD);
}

//get the pressed button. 
int getPressedButton() {
    int ret = 0;

    if(gpio_read(C_CHORD) == 0 ) ret += 100;
    else if(gpio_read(D_CHORD) == 0 ) ret += 200;
    else if(gpio_read(E_CHORD) == 0) ret += 300;
    else if(gpio_read(F_CHORD) == 0 ) ret += 400;
    else if(gpio_read(G_CHORD) == 0 ) ret += 500;
    else if(gpio_read(A_CHORD) == 0) ret += 600;
    else if(gpio_read(B_CHORD) == 0) ret += 700;
    
    if(gpio_read(MINOR) == 0) ret += 1;
    else if(gpio_read(SEVEN) == 0) ret += 2;

    return ret;
}

//check if button is pressed
int isButtonPressed() {
    if (getPressedButton()>=100) return 1;
    else return 0;
}

