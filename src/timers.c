#include "timers.h"
#include "stm32f302x8.h"


void TimInit(TIM_TypeDef* timx, uint16_t psc, uint16_t arr) {
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

  timx->PSC = psc;
  timx->ARR = arr;
}


void TimEnebaleUpdateInterrupts(TIM_TypeDef* timx, IRQn_Type interrupt) {
  timx->DIER |= (1<<TIM_DIER_UIE_Pos);
  NVIC_EnableIRQ(interrupt);
}

void TimDisableUpdateInterrupts(TIM_TypeDef* timx, IRQn_Type interrupt) {
  timx->DIER &= ~(1<<TIM_DIER_UIE_Pos);
  NVIC_DisableIRQ(interrupt);
}


void TimStart(TIM_TypeDef *timx) {
  timx->CR1 |= (1<<TIM_CR1_CEN_Pos);
  while(timx->SR & TIM_SR_UIF_Pos) {}
  timx->SR &= ~(1<<TIM_SR_UIF_Pos);
}

uint16_t TimGetCounter(TIM_TypeDef *timx) {
  return timx->CNT;
}


