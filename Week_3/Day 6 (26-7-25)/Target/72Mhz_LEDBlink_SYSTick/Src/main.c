

#include <stdint.h>
#include <stm32f1xx.h>

void clock_init(void);
void SysTick_init(void);



void clock_init(void){

	RCC->CR |= (1 << 16);

	while(!(RCC->CR & (1 << 17)));

	FLASH->ACR |= (1 << 1);

	RCC->CFGR |= (1 << 16);
	RCC->CFGR |= (0x7 << 18);

	RCC->CR |= (1 << 24);
	while(!(RCC->CR & (1 << 25)));

	RCC->CFGR |= (1 << 1);
	while(!(RCC->CFGR & (1 << 3)));

}

void SysTick_delay_us(uint32_t delay){

	SysTick->LOAD = 71999;

	SysTick->VAL = 0;

	SysTick->CTRL |= (1 << 2);
	SysTick->CTRL |= (1 << 0);

	for(int i = 0; i < delay; i++){
		while(!(SysTick->CTRL & (1 << 16)));
	}

	SysTick->VAL = 0;

}

void TIM1_Init(void)
{
    RCC->APB2ENR |= (1 << 11);
    TIM1->PSC = 71;
    TIM1->ARR = 0xFFFF;
    TIM1->CR1 |= (1 << 0);
}

void microDelay(uint32_t us)
{
    TIM1->CNT = 0;
    while (TIM1->CNT < us);
}

void milliDelay(uint32_t ms)
{
	while (ms--) {
		microDelay(1000);
	}
}

int main(void)
{
	clock_init();
	TIM1_Init();
	RCC->APB2ENR |= (1 << 2);

	GPIOA->CRH &= ~(0xF << 4);
	GPIOA->CRH |= (0x2 << 4);

	while(1){
		GPIOA->ODR |= (1 << 9);
		microDelay(1);
		GPIOA->ODR &= ~(1 << 9);
		microDelay(1);
	}

}
