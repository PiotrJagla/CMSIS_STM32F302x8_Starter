#include "stm32f302x8.h"
#include <stdint.h>
#include "stm32f3xx.h"
#include <stdio.h>
#include "usart.h"

#define LED_PIN 13
uint32_t ticks;

void systick_handler(){
  ticks++;
}

void delay_ms(uint32_t miliseconds){
  uint32_t start = ticks;
  uint32_t end = start + miliseconds;
  if(end < start) {
    while(ticks > start);
  }

  while(ticks < end);
}

void main(void)
{
  RCC->AHBENR |= (1 << RCC_AHBENR_GPIOBEN_Pos);
  
  volatile uint32_t dummy;
  dummy = RCC->AHBENR;
  dummy = RCC->AHBENR;

  GPIOB->MODER |= (1 << GPIO_MODER_MODER13_Pos);


  SysTick_Config(8000);
  __enable_irq();

  usart_init(USART2);
  
  while(1)
  {
    printf("[%d]Hello world\n\r", ticks);
    GPIOB->ODR ^= (1 << LED_PIN);
    delay_ms(1000);
  }
}
