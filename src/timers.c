#include "timers.h"
#include "gpio.h"

//void TIM6_DAC1_IRQHandler() {
//  GpioTogglePin(GPIOA, 9);
//}

void handler() {
  GpioTogglePin(GPIOA, 9);
}

#define IRQ_PIOTR ((volatile uint32_t*)0x000000A4U)

void TimInit(TIM_TypeDef* timx, uint16_t psc, uint16_t arr) {
  timx->PSC = psc;
  timx->ARR = arr;

  if(timx == TIM16) {
    RCC->APB2ENR |= (1<<RCC_APB2ENR_TIM16EN_Pos);
  } else if(timx == TIM1) {
    RCC->APB2ENR |= (1<<RCC_APB2ENR_TIM1EN_Pos);
  } else if(timx == TIM15) {
    RCC->APB2ENR |= (1<<RCC_APB2ENR_TIM15EN_Pos);
  } else if(timx == TIM17) {
    RCC->APB2ENR |= (1<<RCC_APB2ENR_TIM17EN_Pos);
  } else if(timx == TIM2) {
    RCC->APB1ENR |= (1<<RCC_APB1ENR_TIM2EN_Pos);
  } else if(timx == TIM6) {
    RCC->APB1ENR |= (1<<RCC_APB1ENR_TIM6EN_Pos);
  } else if(timx == TIM2) {
    RCC->APB1ENR |= (1<<RCC_APB1ENR_TIM2EN_Pos);
  } 
}


void TimEnebaleUpdateInterrupts(TIM_TypeDef* timx) {
  timx->DIER |= (1<<TIM_DIER_UIE_Pos);
}

void TimDisableUpdateInterrupts(TIM_TypeDef* timx) {
  timx->DIER &= ~(1<<TIM_DIER_UIE_Pos);
}


void TimStart(TIM_TypeDef *timx) {
  timx->CR1 |= (1<<TIM_CR1_CEN_Pos);
}

uint16_t TimGetCounter(TIM_TypeDef *timx) {
  return timx->CNT;
}


