/********************************************************************
 * M8266HostIf.c                                                    *
 * .Description                                                     *
 *     Source file of M8266WIFI Host Interface                      *
 * .Copyright(c) Anylinkin Technology 2015.5-                       *
 *     IoT@anylinkin.com                                            *
 *     http://www.anylinkin.com                                     *
 *     http://anylinkin.taobao.com                                  *
 *  Author                                                          *
 *     anylinkin                                                    *
 *  Date                                                            *
 *  Version                                                         *
 ********************************************************************/
//#include "sys.h"
//#include "delay.h"
#include "brd_cfg.h"
#include "M8266WIFIDrv.h"
#include "M8266HostIf.h"

#include "main.h"
#include "spi.h"
/***********************************************************************************
 * M8266HostIf_GPIO_SPInCS_nRESET_Pin_Init                                         *
 * Description                                                                     *
 *    To initialise the GPIOs for SPI nCS and nRESET output for M8266WIFI module   *
 *    You may update the macros of GPIO PINs usages for nRESET from brd_cfg.h      *
 *    You are not recommended to modify codes below please                         *
 * Parameter(s):                                                                   *
 *    None                                                                         *
 * Return:                                                                         *
 *    None                                                                         *
 ***********************************************************************************/
void M8266HostIf_GPIO_CS_RESET_Init(void)
{
//  GPIO_InitTypeDef  GPIO_InitStructure;

//	//Initial STM32's GPIO for M8266WIFI_SPI_nCS
//  M8266WIFI_SPI_nCS_GPIO_RCC_CLOCK_EN;  														// enable nCS GPIO clock
//	GPIO_OUTPUT_HIGH(M8266WIFI_SPI_nCS_GPIO,M8266WIFI_SPI_nCS_PIN);		// nCS output high initially	
//	GPIO_InitStructure_AS_GPIO_OUTPUT(M8266WIFI_SPI_nCS_GPIO,M8266WIFI_SPI_nCS_PIN);
//	
//	//Initial STM32's GPIO for M8266WIFI_nRESET
//  M8266WIFI_nRESET_GPIO_RCC_CLOCK_EN;  															// enable nRESET GPIO clock
//	GPIO_OUTPUT_HIGH(M8266WIFI_nRESET_GPIO,M8266WIFI_nRESET_PIN);		  // nRESET output high initially	
//	GPIO_InitStructure_AS_GPIO_OUTPUT(M8266WIFI_nRESET_GPIO,M8266WIFI_nRESET_PIN);
}
/***********************************************************************************
 * M8266HostIf_SPI_Init                                                            *
 * Description                                                                     *
 *    To initialise the SPI Interface for M8266WIFI module                         *
 *    You may update the macros of SPI usages for nRESET from brd_cfg.h            *
 *    You are not recommended to modify codes below please                         *
 * Parameter(s):                                                                   *
 *    None                                                                         *
 * Return:                                                                         *
 *    None                                                                         *
 ***********************************************************************************/

void M8266HostIf_SPI_Init(void)
{
}/***********************************************************************************
 * M8266HostIf_SPI_SetSpeed                                                        *
 * Description                                                                     *
 *    To setup the SPI Clock Speed for M8266WIFI module                            *
 * Parameter(s):                                                                   *
 *    SPI_BaudRatePrescaler: SPI BaudRate Prescaler                                *
 * Return:                                                                         *
 *    None                                                                         *
 ***********************************************************************************/
//SPI_HandleTypeDef hspi;
void M8266HostIf_SPI_SetSpeed(u32 SPI_BaudRatePrescaler)
{

	__HAL_SPI_DISABLE(&hspi3);
	SPI3->CFG1 &= ~(7UL<<28);
	SPI3->CFG1 |= SPI_BaudRatePrescaler;
  __HAL_SPI_ENABLE(&hspi3);

} 

/***********************************************************************************
 * M8266HostIf_Init                                                                *
 * Description                                                                     *
 *    To initialise the Host interface for M8266WIFI module                        *
 * Parameter(s):                                                                   *
 *    baud: baud rate to set                                                       *
 * Return:                                                                         *
 *    None                                                                         *
 ***********************************************************************************/ 
void M8266HostIf_Init(void)
{
	 M8266HostIf_GPIO_CS_RESET_Init();
	
	 M8266HostIf_SPI_Init();
//	 M8266HostIf_SPI_SetSpeed(SPI_BaudRatePrescaler_8);
	
}

//////////////////////////////////////////////////////////////////////////////////////
// BELOW FUNCTIONS ARE REQUIRED BY M8266WIFIDRV.LIB. 
// PLEASE IMPLEMENTE THEM ACCORDING TO YOUR HARDWARE
//////////////////////////////////////////////////////////////////////////////////////
/***********************************************************************************
 * M8266HostIf_Set_nRESET_Pin                                                      *
 * Description                                                                     *
 *    To Outpout HIGH or LOW onto the GPIO pin for M8266WIFI nRESET                *
 *    You may update the macros of GPIO PIN usages for nRESET from brd_cfg.h       *
 *    You are not recommended to modify codes below please                         *
 * Parameter(s):                                                                   *
 *    1. level: LEVEL output to nRESET pin                                         *
 *              0 = output LOW  onto nRESET                                        *
 *              1 = output HIGH onto nRESET                                        *
 * Return:                                                                         *
 *    None                                                                         *
 ***********************************************************************************/
void M8266HostIf_Set_nRESET_Pin(u8 level)
{
	  if(level!=0)
		//GPIO_SetBits(M8266WIFI_nRESET_GPIO, M8266WIFI_nRESET_PIN);
			HAL_GPIO_WritePin(M8266WIFI_nRESET_GPIO_Port,M8266WIFI_nRESET_Pin, GPIO_PIN_SET);

		else
		//GPIO_ResetBits(M8266WIFI_nRESET_GPIO, M8266WIFI_nRESET_PIN);
			HAL_GPIO_WritePin(M8266WIFI_nRESET_GPIO_Port,M8266WIFI_nRESET_Pin, GPIO_PIN_RESET);
}
/***********************************************************************************
 * M8266HostIf_Set_SPI_nCS_PIN                                                     *
 * Description                                                                     *
 *    To Outpout HIGH or LOW onto the GPIO pin for M8266WIFI SPI nCS               *
 *    You may update the macros of GPIO PIN usages for SPI nCS from brd_cfg.h      *
 *    You are not recommended to modify codes below please                         *
 * Parameter(s):                                                                   *
 *    1. level: LEVEL output to SPI nCS pin                                        *
 *              0 = output LOW  onto SPI nCS                                       *
 *              1 = output HIGH onto SPI nCS                                       *
 * Return:                                                                         *
 *    None                                                                         *
 ***********************************************************************************/
void M8266HostIf_Set_SPI_nCS_Pin(u8 level)
{
	  if(level!=0)
		//GPIO_SetBits(M8266WIFI_SPI_nCS_GPIO, M8266WIFI_SPI_nCS_PIN);
			HAL_GPIO_WritePin(M8266WIFI_SPI_nCS_GPIO_Port,M8266WIFI_SPI_nCS_Pin, GPIO_PIN_SET);

		else
		//GPIO_ResetBits(M8266WIFI_SPI_nCS_GPIO, M8266WIFI_SPI_nCS_PIN);
			HAL_GPIO_WritePin(M8266WIFI_SPI_nCS_GPIO_Port,M8266WIFI_SPI_nCS_Pin, GPIO_PIN_RESET);
}


static uint32_t ticks_per_us=400;
void delay_us(uint8_t nus)  
{                            

	/*
	   In a multiple-task system, please add function of lock schedule at beginning to aviod influence to the delay accuracy 
	   (Chinese: 在多任务系统里，请在这个函数实现的一开始处加上临时关闭任务调度，避免任务调度对延时精度的影响)
	*/
	
   uint32_t  start, now, delta, reload;
   start = SysTick->VAL;
   reload = SysTick->LOAD;		
	 do                                          
   {
        now = SysTick->VAL;
        delta = start >= now ? start - now : reload + start - now;
   }
   while (delta < ticks_per_us * nus);
	 
	 	/*
	   In a multiple-task system, remember to unlock schedule here before return from the function
	   (Chinese: 在多任务系统里，在退出这个函数前，记得要重新恢复任务调度)
	*/
}
/***********************************************************************************
 * M8266WIFIHostIf_delay_us                                                        *
 * Description                                                                     *
 *    To loop delay some micro seconds.                                            *
 * Parameter(s):                                                                   *
 *    1. nus: the micro seconds to delay                                           *
 * Return:                                                                         *
 *    none                                                                         *
 ***********************************************************************************/
void M8266HostIf_delay_us(u8 nus)
{
   delay_us(nus);
}

/***********************************************************************************
 * M8266HostIf_SPI_ReadWriteByte                                                   *
 * Description                                                                     *
 *    To write a byte onto the SPI bus from MCU MOSI to the M8266WIFI module       *
 *    and read back a byte from the SPI bus MISO meanwhile                         *
 *    You may update the macros of SPI usage from brd_cfg.h                        *
 * Parameter(s):                                                                   *
 *    1. TxdByte: the byte to be sent over MOSI                                    *
 * Return:                                                                         *
 *    1. The byte read back from MOSI meanwhile                                    *                                                                         *
 ***********************************************************************************/
u8 M8266HostIf_SPI_ReadWriteByte(u8 TxdByte)
{

  u8 Rxdata;
  if(HAL_SPI_TransmitReceive(&hspi3, &TxdByte, &Rxdata, 1,0xFFFFFF)!=HAL_OK)
		return 0;   
 	return Rxdata; 

}
