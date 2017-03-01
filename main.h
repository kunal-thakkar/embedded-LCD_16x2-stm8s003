#include "stm8s.h"

#define LED_GPIO_PORT  (GPIOA)
#define LED_GPIO_PINS  (GPIO_PIN_3)
#define LCD_PORT (GPIOD)
#define LCD_RS GPIO_PIN_1
#define LCD_EN GPIO_PIN_2
#define LCD_D4 GPIO_PIN_3
#define LCD_D5 GPIO_PIN_4
#define LCD_D6 GPIO_PIN_5
#define LCD_D7 GPIO_PIN_6

void delay_ms(uint32_t nCount);
