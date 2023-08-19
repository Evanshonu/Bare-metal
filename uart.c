#include "uart.h"

char reciever(void) {
	/**Check if the UART RX register not empty**/
	while ((USART2->SR & SR_RXNE) == 0) {
	}

	/**Read from the data register**/
	return USART2->DR;
}

/****PA2 tx Alternate function AF07 ***/
void uart_init_tx_RX(void) {
	/**Enable clock access to GPIOA**/
	RCC->AHB1ENR |= GPIOAEN;
	/**Enable clock access to USARTEN**/
	RCC->APB1ENR |= USART2EN;
	/**Configure PA2 MODER as alternate function**/
	GPIOA->MODER &= ~(1UL << 4);
	GPIOA->MODER |= (1UL << 5);
	/**Configure PA2 MODER as alternate function**/
	GPIOA->MODER &= ~(1UL << 6);
	GPIOA->MODER |= (1UL << 7);
	/**Configure PA2 alternate function type AF07**/
	GPIOA->AFR[0] |= (0x700UL);
	/**Configure PA3 alternate function type AF07**/
	GPIOA->AFR[0] |= (0x7000UL);
	/**Configure the baudrate**/
	set_baudRate(USART2, APBCLK, BAUD_RATE_);
	/**Configure the transfer direct (tx)**/
	USART2->CR1 = (CR1_TE | CR1_RE);
	/**Enable the UART module**/
	USART2->CR1 |= CR1_UE;
}

/****PA2 tx Alternate function AF07 ***/
void uart_init_tx(void) {
	/**Enable clock access to GPIOA**/
	RCC->AHB1ENR |= GPIOAEN;
	/**Enable clock access to USARTEN**/
	RCC->APB1ENR |= USART2EN;
	/**Configure PA2 MODER as alternate function**/
	GPIOA->MODER &= ~(1UL << 4);
	GPIOA->MODER |= (1UL << 5);
	/**Configure PA2 alternate function type AF07**/
	GPIOA->AFR[0] |= (0x700UL);
	/**Configure the baudrate**/
	set_baudRate(USART2, APBCLK, BAUD_RATE_);
	/**Configure the transfer direct (tx)**/
	USART2->CR1 = CR1_TE;
	/**Enable the UART module**/
	USART2->CR1 |= CR1_UE;
}

void transmitt(int character) {
	/**Check if the UART tx register not empty**/
	while ((USART2->SR & SR_TXE) == 0) {
	}

	/**Write 8bit to the data register**/
	USART2->DR = (character & 0xFF);
}
void set_baudRate(USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t baudRate) {
	USART2->BRR = compute_bd(APBCLK, BAUD_RATE_);
}
uint16_t compute_bd(uint32_t PeriphCLK, uint32_t baudRate) {

	return ((PeriphCLK + (baudRate / 2U)) / baudRate);
}
void toggle_PA5(void) {
	GPIOA->MODER |=  (1UL << 20);
	GPIOA->MODER &= ~(1UL << 21);
	GPIOA->ODR ^= (1UL << 10);
}

