
#include <stdint.h>
#include <stm32l4xx.h>
#include <stdio.h>

void clock_init(void);
void TIM2_init_us(void);
void delay_us(uint32_t us);

void Systick_delay_ms(int delay);
//void Systick_delay_us(int delay);

void DHT_GPIO_init_MCU_Start(void);
void DHT_GPIO_init_DHT_Start(void);
void DHT11_Init(void);
uint8_t DHT11_Read_bit();
uint8_t DHT11_Response_check();
uint8_t DHT11_Read_Byte();
void GET_DHT11_Data(uint8_t *humadity, uint8_t *temperature);

void clock_init(void){

	RCC->CR |= (1 << 8);

	while(!(RCC->CR & (1 << 10)));

	FLASH->ACR |= (3 << 0);
	FLASH->ACR |= (1 << 8);
	FLASH->ACR |= (1 << 9);
	FLASH->ACR |= (1 << 10);


	RCC->PLLCFGR = 0;
	RCC->PLLCFGR |= (0b10 << 0);
	RCC->PLLCFGR |= (0x1 << 4);
	RCC->PLLCFGR |= (18 << 8);
	RCC->PLLCFGR |= (0b00 << 25);
	RCC->PLLCFGR |= (1 << 24);

	RCC->CR |= (1 << 24);
	while(!(RCC->CR & (1 << 25)));

	RCC->CFGR &= ~(0b11 << 0);
	RCC->CFGR |= (0b11 << 0);
	while((RCC->CFGR & (0b11 << 2)) != (0b11 << 2));

	RCC->CFGR &= ~(0xF << 4);
	RCC->CFGR &= ~(0b111 << 8);
	RCC->CFGR &= ~(0b111 << 11);

}

void TIM2_init_us(void){

	RCC->APB1ENR1 |= (1 << 0);

	TIM2->PSC = 71;
	TIM2->ARR = 0xFFFF;
	TIM2->CNT = 0;
	TIM2->CR1 = (1 << 0);
}

void delay_us(uint32_t us){
	TIM2->CNT = 0;
	while(TIM2->CNT < us);
}

void delay_ms(uint32_t ms){
	for(uint32_t i = 0; i < ms; i++){
		delay_us(1000);
	}
}

void Systick_delay_ms(int delay){

	SysTick->LOAD = 71999;

	SysTick->VAL = 0;

	SysTick->CTRL |= (1 << 2);
	SysTick->CTRL |= (1 << 0);

	for(int i = 0; i < delay; i++){
		while(!(SysTick->CTRL & (1 << 16)));
	}

}

//void Systick_delay_us(int delay){
//
//	SysTick->LOAD = 71;
//
//	SysTick->VAL = 0;
//
//	SysTick->CTRL |= (1 << 2);
//	SysTick->CTRL |= (1 << 0);
//
//	for(int i = 0; i < delay; i++){
//		while(!(SysTick->CTRL & (1 << 16)));
//	}
//}

void DHT_GPIO_init_MCU_Start(void){

	RCC->AHB2ENR |= (1 << 0);

	GPIOA->MODER &= ~(0b11 << 6);
	GPIOA->MODER |= (0b01 << 6);

}

void DHT_GPIO_init_DHT_Start(void){

	RCC->AHB2ENR |= (1 << 0);

	GPIOA->MODER &= ~(0b11 << 6);
	GPIOA->MODER |= (0b00 << 6);

}

void DHT11_Init(void){
	DHT_GPIO_init_MCU_Start();
	GPIOA->ODR &= ~(1 << 3);
	Systick_delay_ms(20);
	GPIOA->ODR |= (1 << 3);
	delay_us(30);
	DHT_GPIO_init_DHT_Start();
}

uint8_t DHT11_Read_bit(){
	return (GPIOA->IDR & (1 << 3)) != 0;
}

uint8_t DHT11_Response_check(){

	delay_us(40);
	if(!DHT11_Read_bit()){
		delay_us(80);
		if(DHT11_Read_bit()){
			return 1;
		}
	}
	return 0;
}

uint8_t DHT11_Read_Byte(){
	uint8_t i, result = 0;
	printf("Byte is Reading....\n");

	for(i = 0; i < 8; i++){

		while(!DHT11_Read_bit());

		delay_us(30);

		if(DHT11_Read_bit()){
			result |= (1 << (7 - i));
			printf("Data 1\n");
		}
		printf("2i = %d\n", i);
		while(DHT11_Read_bit()){
			printf("i = %d\n", i);
//			Systick_delay_ms(1000);
		}
		printf("i = %d\n", i);

	}
	return result;
}

void GET_DHT11_Data(uint8_t *humadity, uint8_t *temperature){
	uint8_t RH_integral, RH_decimal, T_integral, T_decimal, checksum;

	DHT11_Init();

	if(DHT11_Response_check()){

	printf("response from DHT11!\n");
	printf("response from DHT112!\n");



	RH_integral = DHT11_Read_Byte();
	printf("H : %d\n", RH_integral);
	RH_decimal = DHT11_Read_Byte();
	T_integral = DHT11_Read_Byte();
	printf("T : %d\n", T_integral);
	T_decimal = DHT11_Read_Byte();
	checksum = DHT11_Read_Byte();

	if (checksum == (RH_integral + RH_decimal + T_integral + T_decimal)){
		*humadity = RH_integral;
		*temperature = T_integral;
		printf("H : %d\n", RH_integral);
		printf("T : %d\n", T_integral);
	}
	else{
		*humadity = 0;
		*temperature = 0;
		printf("Error");
	}

	}

}

int main(void)
{
	clock_init();

	TIM2_init_us();

	printf("Hello \n");
	uint8_t temperature, humidity;

	while(1){
	GET_DHT11_Data(&humidity, &temperature);

	printf("Temperature = %d°C\n", temperature);
	fflush(stdout);
	printf("Humidity    = %d%%\n\n", humidity);
	fflush(stdout);

	Systick_delay_ms(2000);
	}


}
