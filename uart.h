#ifndef		__UART_H__
#define		__UART_H__

#include<stdint.h>
#include "stm32f4xx.h"

/**----UART #define Macros---***/
#define 	GPIOAEN		(1UL<<0)
#define		USART2EN	(1UL<<17)
#define		__SYS_FREQ_	16000000
#define 	APBCLK		__SYS_FREQ_
#define 	BAUD_RATE_	9600

/***UART TX bit defined Registers*****/
#define 	CR1_TE		(1UL<<3)
#define 	CR1_UE		(1UL<<13)
#define 	SR_TXE		(1UL<<7)
#define 	CR1_RE		(1UL<<2)
#define		SR_RXNE		(1UL<<5)
/***User defined function*****/
void uart_init_tx(void);
void set_baudRate(USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t baudRate);
uint16_t compute_bd(uint32_t PeriphCLK, uint32_t baudRate);
void transmitt(int character);
void uart_init_tx_RX(void);
char reciever(void);
void toggle_PA5(void);




#endif
