#include "adc.h"
#include "stm32f302x8.h"


void ADCInit() {
  RCC->AHBENR |= RCC_AHBENR_ADC1EN;

  ADC1_COMMON->CCR |= ADC_CCR_CKMODE_0;

  ADC1->CR |= ADC_CR_ADVREGEN;
  for(int i = 0 ; i < 1000 ; ++i) {}
  ADC1->CR |= ADC_CR_ADEN;
  while(!(ADC1->ISR & ADC_ISR_ADRDY));
}

uint16_t ADCGetValue() {
  return ADC1->DR;
}

void ADCStartConversion() {
  ADC1->CR |= ADC_CR_ADSTART;
  while(!(ADC1->ISR & ADC_ISR_EOC));
}
