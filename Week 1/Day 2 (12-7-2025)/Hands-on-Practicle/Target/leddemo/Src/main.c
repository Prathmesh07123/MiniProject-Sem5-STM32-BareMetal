

#include <stdint.h>
#include <stdio.h>

uint32_t *AHB2ENR = (uint32_t*)0x4002104c;
uint32_t *GPIOB_MODER = (uint32_t*)0x48000400;
uint32_t *GPIOB_ODR = (uint32_t*)0x48000414;

void delay(int ms);

void delay(int ms){
	for(int i = 0; i < ms; i++){
		for(int j = 0; j < 7599; j++);
	}
}

int main(void)
{
	*AHB2ENR |= (1 << 1);
	*GPIOB_MODER &= ~(0b11 << 14);
	*GPIOB_MODER |= (0b01 << 14);

	while(1){
		*GPIOB_ODR |= (1 << 7);
		delay(100);
		*GPIOB_ODR &= ~(1 << 7);
		delay(100);
	}
}
