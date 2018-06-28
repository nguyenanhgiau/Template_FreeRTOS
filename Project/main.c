/**
******************************************************************************
* @file    Project/STM32F10x_StdPeriph_Template/main.c 
* @author  MCD Application Team
* @version V3.5.0
* @date    08-April-2011
* @brief   Main program body
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
******************************************************************************
*/  

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "INCLUDES.h"

/** @addtogroup STM32F10x_StdPeriph_Template
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static INT32U ulIdleCycleCount = 0;
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/*
* Configure the clocks, GPIO and other peripherals as required by the demo.
*/
void prvSetupHardware( void );

static void usartInit(void);
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Main program.
* @param  None
* @retval None
*/
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  file (startup_stm32f10x_xx.s) before to branch to application main.
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f10x.c file
  */
  prvSetupHardware();
  
  /* Add your application code here
  */  
  usartInit();
  
  /**/
  xTaskCreate(vTask1, "Task1", 240, NULL, 2, NULL);
  
  xTaskCreate(vTask2, "Task2", 240, NULL, 1, NULL);
  
  vTaskStartScheduler();
  
  return 0;
}

void prvSetupHardware( void )
{
  /* Start with the clocks in their expected state. */
  RCC_DeInit();
  
  /* Enable HSE (high speed external clock). */
  RCC_HSEConfig( RCC_HSE_ON );
  
  /* Wait till HSE is ready. */
  while( RCC_GetFlagStatus( RCC_FLAG_HSERDY ) == RESET )
  {
  }
  
  /* 2 wait states required on the flash. */
  *( ( unsigned long * ) 0x40022000 ) = 0x02;
  
  /* HCLK = SYSCLK */
  RCC_HCLKConfig( RCC_SYSCLK_Div1 );
  
  /* PCLK2 = HCLK */
  RCC_PCLK2Config( RCC_HCLK_Div1 );
  
  /* PCLK1 = HCLK/2 */
  RCC_PCLK1Config( RCC_HCLK_Div2 );
  
  /* PLLCLK = 8MHz * 9 = 72 MHz. */
  RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );
  
  /* Enable PLL. */
  RCC_PLLCmd( ENABLE );
  
  /* Wait till PLL is ready. */
  while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
  {
  }
  
  /* Select PLL as system clock source. */
  RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );
  
  /* Wait till PLL is used as system clock source. */
  while( RCC_GetSYSCLKSource() != 0x08 )
  {
  }
  
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x0 );
  
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
  
  /* Configure HCLK clock as SysTick clock source. */
  SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
}

static void usartInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
  
  /* Enable USART1 & GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
  
  /* Configure USART1 Tx as alternate function push-pull */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* Configure USART1 Rx as input floating */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* Configure USARTx */
  USART_InitStruct.USART_BaudRate = 115200;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_Init(USART1, &USART_InitStruct);
  /* USART enable */
  USART_Cmd(USART1, ENABLE);
}

void vTask1(void *pvParameters)
{
  for(;;)
  {
    printf("Task1 running\n");
    printf("Time idle = %d\n", ulIdleCycleCount);
    vTaskDelay(1000/portTICK_RATE_MS);
  }
}

void vTask2(void *pvParameters)
{
  for(;;)
  {
    printf("Task2 running\n");
    printf("Time idle = %d\n", ulIdleCycleCount);
    vTaskDelay(1000/portTICK_RATE_MS);
  }
}

/**
* @brief  Retargets the C library printf function to the USART.
* @param  None
* @retval None
*/
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);
  
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}
  
  return ch;
}
#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/* Idle hook functions MUST be called vApplicationIdleHook(), 
  take no parameters, and return void;
*/
void vApplicationIdleHook(void)
{
  /* This hook functions does nothing but increment a counter*/
  ulIdleCycleCount++;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
