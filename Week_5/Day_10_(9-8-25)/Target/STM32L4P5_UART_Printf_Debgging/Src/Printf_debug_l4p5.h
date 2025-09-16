/*
 * Printf_debug_l4p5.h
 *
 *  Created on: Aug 14, 2025
 *      Author: prath
 */

#ifndef PRINTF_DEBUG_L4P5_H_
#define PRINTF_DEBUG_L4P5_H_

void USART2_INIT(void);
void USART2_WriteChar(char c);
void USART2_WriteString(const char *str);

#endif /* PRINTF_DEBUG_L4P5_H_ */
