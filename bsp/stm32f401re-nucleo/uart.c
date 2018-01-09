/*******************************************************************************
 * @file		apps/uart/uart.c
 * @brief		This source file is for uart communications.
 * @author	HoYa	<hoya128@gmail.com>
 *******************************************************************************
 * @version	v1.0
 * @note
 *	- 2018.01.04	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
// User Header
#include "uart.h"

/* Macros --------------------------------------------------------------------*/
#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
	#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define GETCHAR_PROTOTYPE int fgetc(FILE* f)
#endif

/* Private Variables ---------------------------------------------------------*/
UART_HandleTypeDef	uartHandle;

/* Private Function Prototypes -----------------------------------------------*/
PUTCHAR_PROTOTYPE;
GETCHAR_PROTOTYPE;

/* APIs ----------------------------------------------------------------------*/
eUART_STATUS uart_init(uint32_t baudrate) {
	uartHandle.Instance = USARTx;
	uartHandle.Init.BaudRate = baudrate;
	uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	uartHandle.Init.StopBits = UART_STOPBITS_1;
	uartHandle.Init.Parity = UART_PARITY_NONE;
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle.Init.Mode = UART_MODE_TX_RX;
	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&uartHandle) != HAL_OK) {
		return eUART_STATUS_INIT_FAIL;
	}

	setvbuf(stdin, NULL, _IONBF, 0);
	return eUART_STATUS_SUCCESS;
}

/* System Functions ----------------------------------------------------------*/
PUTCHAR_PROTOTYPE {
	HAL_UART_Transmit(&uartHandle, (uint8_t*)&ch, 1, 0xffff);
	return ch;
}

GETCHAR_PROTOTYPE {
	int ch;
	HAL_UART_Receive(&uartHandle, (uint8_t*)&ch, 1, 0xffff);
	return ch;
}

/* MSP Functions -------------------------------------------------------------*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
	(void)huart;
	GPIO_InitTypeDef	GPIO_InitStruct;

	USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();
  USARTx_CLK_ENABLE();

  GPIO_InitStruct.Pin = USARTx_TX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;
  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;
  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart) {
	(void)huart;
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}
