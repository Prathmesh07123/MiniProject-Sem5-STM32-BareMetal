
#include <stdint.h>
#include <stdio.h>
#include "Printf_debug.h"

	// Clock REG
	uint32_t *pAPB2ENR    = (uint32_t*)0x40021018;
	uint32_t *pAPB1ENR    = (uint32_t*)0x4002101c;

	// GPIO A (PA2)
	uint32_t *pGPIOACRL   = (uint32_t*)0x40010800;

	// USART REG
	uint32_t *pUART2_SR   = (uint32_t*)0x40004400;	// Check Status of Transmission Complete
	uint32_t *pUART_2DR   = (uint32_t*)0x40004404;	//Data Present
	uint32_t *pUART_2BRR  = (uint32_t*)0x40004408;	//Baud Rate Selection
	uint32_t *pUART_2CR1  = (uint32_t*)0x4000440c;	//Control REG To Enable Transmission

void USART2_INIT(void);
void Uart_Write(int ch);
int __io_putchar(int ch); // Receive Char From Printf Function

void USART2_INIT(void){

	// Enable Clock Of GPIOA
	*pAPB2ENR |= (1 << 2);

	//Enable Clock Of USART2
	*pAPB1ENR |= (1 << 17);

	// Configure GPIO To Alternate Function (CRL)
	*pGPIOACRL &= ~(0xF << 8);
	*pGPIOACRL |= (0xB << 8); // CNF2 = 10 , MODE2 = 11

	// Configure Baud Rate too 9600
	*pUART_2BRR = 0x01D4C;

	// Configuration of control REG of USART
	*pUART_2CR1 |= (1 << 13); // UART Enable
	*pUART_2CR1 |= (1 << 3); // Transmission Enable


}

void Uart2_Write(int ch){

	while (!(*pUART2_SR & 0x0080)){
		// No Operation when TXE is 1 Then DR ready to get new data
	}
	*pUART_2DR = (ch & 0xFF);

}

int __io_putchar(int ch){

	Uart2_Write(ch);
	return ch;
}
