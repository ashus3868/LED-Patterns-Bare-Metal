// Patterns ON LEDs
#include <stdio.h>
#include <stdint.h>

#define GPIO_PIN            2
#define GPIO_PIN1           4
#define GPIO_PIN2           5

#define GPIO_OUT_W1TS_REG  0x3FF44008 
#define GPIO_OUT_W1TC_REG  0x3FF4400C 
#define GPIO_ENABLE_REG    0x3FF44020 

void delay(volatile uint32_t cycles){
    while (cycles--)
    {
        for (int i = 0; i < 10000; i++)
        {
            __asm__ volatile("nop");    // no operation
        }   
    }
}

void app_main(void){
    volatile uint32_t* gpio_out_w1ts_reg = (volatile uint32_t*)GPIO_OUT_W1TS_REG;
    volatile uint32_t* gpio_out_w1tc_reg = (volatile uint32_t*)GPIO_OUT_W1TC_REG;
    volatile uint32_t* gpio_enable_reg = (volatile uint32_t*)GPIO_ENABLE_REG;
    
    *gpio_enable_reg |= (1<<GPIO_PIN);
    *gpio_enable_reg |= (1<<GPIO_PIN1);
    *gpio_enable_reg |= (1<<GPIO_PIN2);


    while (1)
    {   // GPIO2
        *gpio_out_w1ts_reg = (1<<GPIO_PIN);
        delay(500);
        *gpio_out_w1tc_reg = (1<<GPIO_PIN);
        delay(500);

        // GPIO4
        *gpio_out_w1ts_reg = (1<<GPIO_PIN1);
        delay(500);
        *gpio_out_w1tc_reg = (1<<GPIO_PIN1);
        delay(500);

        // GPIO5
        *gpio_out_w1ts_reg = (1<<GPIO_PIN2);
        delay(500);
        *gpio_out_w1tc_reg = (1<<GPIO_PIN2);
        delay(500);

    }   
}
