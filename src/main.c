#include "stm8s.h"
#include "milis.h"
#include "keypad.h"
#include <stdio.h>
#include "uart1.h"
#include "delay.h"

#define _ISOC99_SOURCE
#define _GNU_SOURCE

void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz


    init_milis(); //inicializace mmilisu
    init_uart1();
    init_keypad();
    GPIO_Init(GPIOD, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST);


    TIM2_TimeBaseInit(TIM2_PRESCALER_16, 7000 - 1 ); 
    TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,3000,TIM2_OCPOLARITY_HIGH);// inicializujeme kanál 1 (TM2_CH1)
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_Cmd(ENABLE);

}


int main(void)
{
    uint8_t key_last = 0;
    uint8_t key_now = 0;
    uint8_t key_pressed = 0;
    int32_t time_key = 0;

    setup();  

    while (1) {

        if (milis() - time_key > 50) {
            time_key = milis();
            key_now = check_keypad();
            if (key_last == 0xFF && key_now != 0xFF) {
                        key_pressed = key_now;
                        printf("%X\r\n", key_pressed);
            
            
            }
            key_last = key_now;
        }

        switch(key_pressed)
        {
            case 1:
                _delay_us(40);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(7000);
                break;
            case 2:
                _delay_us(50);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(6500);
                break;

            case 3:
                _delay_us(60);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(6000);
                break;

            case 4:
                _delay_us(70);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(5500);
                break;
            case 5:
                _delay_us(80);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(5000);
                break;
            case 6:
                _delay_us(90);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(4500);
                break;
            case 7:
                _delay_us(100);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(4000);
                break;
            case 8:
                _delay_us(110);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(3500);
                break;
            case 9:
                _delay_us(120);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(3000);
                break;
            case 10:
                _delay_us(130);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(2500);
                break;
            case 11:
                _delay_us(140);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(2000);
                break;
            case 12:
                _delay_us(150);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(1500);
                break;
            case 13:
                _delay_us(160);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(1000);
                break;
            case 14:
                _delay_us(170);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(500);
                break;
            case 15:
                _delay_us(180);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(200);
                break;
            case 0:
                _delay_us(190);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(100);
                break;



            default:
                _delay_us(200);
                GPIO_WriteReverse(GPIOD, GPIO_PIN_7);
                TIM2_SetCompare1(50);
                break;
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
