/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   SI4432配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */



#ifndef __DRV_SI4432_H__
#define __DRV_SI4432_H__


#include "drv_spi.h"


#define SI4432_DATA_LEN_MAX			64			//自定义数据最大长度，最大为64


/** SI4432硬件接口IO定义 */
//#define SI4432_SDN_PORT				GPIOF									
//#define SI4432_SDN_CLK				RCC_APB2Periph_GPIOF
//#define SI4432_SDN_PIN				GPIO_Pin_13

//#define SI4432_IRQ_PORT				GPIOF									
//#define SI4432_IRQ_CLK				RCC_APB2Periph_GPIOF
//#define SI4432_IRQ_PIN				GPIO_Pin_14

//#define SI4432_GPIO0_PORT			GPIOF									
//#define SI4432_GPIO0_CLK			RCC_APB2Periph_GPIOF
//#define SI4432_GPIO0_PIN			GPIO_Pin_12

//#define SI4432_GPIO1_PORT			GPIOF								
//#define SI4432_GPIO1_CLK			RCC_APB2Periph_GPIOF
//#define SI4432_GPIO1_PIN			GPIO_Pin_11

//#define SI4432_GPIO2_PORT			GPIOB								
//#define SI4432_GPIO2_CLK			RCC_APB2Periph_GPIOB
//#define SI4432_GPIO2_PIN			GPIO_Pin_1



//IO操作函数定义
//#define SI_SET_SDN_HIGH( )			SI4432_SDN_PORT->ODR |= SI4432_SDN_PIN
//#define SI_SET_SDN_LOW( )			SI4432_SDN_PORT->ODR &= (uint32_t)((uint32_t)( ~SI4432_SDN_PIN ))

#define SI_SET_CSN_HIGH( )			spi_set_nss_high( )
#define SI_SET_CSN_LOW( )			spi_set_nss_low( )

//#define SI_GET_IRQ_STATUS( )		(( SI4432_IRQ_PORT->IDR & SI4432_IRQ_PIN ) != SI4432_IRQ_PIN ) ? 0 : 1
#define SI_GET_IRQ_STATUS( )     (HAL_GPIO_ReadPin(NIRQ_GPIO_Port,NIRQ_Pin) == 0)? 0 : 1
//#define SI_GET_GPIO0_STATUS( )		(( SI4432_GPIO0_PORT->IDR & SI4432_GPIO0_PIN ) != SI4432_GPIO0_PIN ) ? 0 : 1
//#define SI_GET_GPIO1_STATUS( )		(( SI4432_GPIO1_PORT->IDR & SI4432_GPIO1_PIN ) != SI4432_GPIO1_PIN ) ? 0 : 1
//#define SI_GET_GPIO2_STATUS( )		(( SI4432_GPIO2_PORT->IDR & SI4432_GPIO2_PIN ) != SI4432_GPIO2_PIN ) ? 0 : 1


#define SI4432_Tx_Byte( TxByte )	drv_spi_read_write_byte( TxByte )
#define SI4432_Rx_Byte( )			drv_spi_read_write_byte( 0x55 )	



uint8_t SI4432_Read_Reg( uint8_t ReadAddr );
void SI4432_Write_Reg( uint8_t WriteAddr, uint8_t WriteValue );
uint8_t SI4432_Get_It_Status1( void );
uint8_t SI4432_Get_It_Status2( void );
void SI4432_SW_Reset( void );
void SI4432_Set_Sync( uint16_t SyncValue );
void SI4432_Clear_Rx_FIFO( void );
void SI4432_Start_Tx( void );
void SI4432_Start_Rx( void );
void SI4432_Tx_Packet( uint8_t *pTxBuff, uint8_t TxLength );
uint8_t SI4432_Rx_Packet( uint8_t *pRxBuff );
void SI4432_Gpio_Init( void );
void SI4432_Init( void );



#endif
