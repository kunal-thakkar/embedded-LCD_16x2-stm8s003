#include "stm8s.h"
#include "main.h"
#include "lcd.h"

volatile uint32_t f_cpu=0;
volatile uint32_t time_keeper=0;

void init_tim4();

void main(void)
{
  init_tim4();
  f_cpu=CLK_GetClockFreq();

  //Config output for LED
  GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

  //Config output for text lcd
  GPIO_Init(LCD_PORT,(GPIO_Pin_TypeDef)(LCD_RS|LCD_EN),GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(LCD_PORT,(GPIO_Pin_TypeDef)(LCD_D4|LCD_D5|LCD_D6|LCD_D7),GPIO_MODE_OUT_PP_LOW_FAST);  
  
  lcd_init();

  lcd_puts(0,0,(int8_t*)"STM8S003");
  lcd_puts(1,0,(int8_t*)"Hello Kunal!");
    
  while (1)
  {
    /* Toggles LEDs 
    GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
    Delay(0xFFFF);*/
  }
}

//Setup clock from external quartz that must be 8MHz
void init_tim4(){
  CLK_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 0x7D);//127 63 and 0x7D == Interrupt 1ms
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);
  enableInterrupts();
}

void handleTimer(){
  if(time_keeper!=0)
  {
    time_keeper--;
  }
  else
  {
    /* Disable Timer to reduce power consumption */
    //TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
  }
  TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
}

void delay_ms(uint32_t time)
{
  time_keeper=time;
  /* Reset Counter Register value */
  TIM4->CNTR = (uint8_t)(0);

  /* Enable Timer */
  //TIM4->CR1 |= TIM4_CR1_CEN;
  while(time_keeper);
 // GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
