/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   SPI配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */


#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__


#include "main.h"



#define spi_set_nss_high( )			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port,SPI2_CS_Pin,GPIO_PIN_SET)								//片选置高
#define spi_set_nss_low( )			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port,SPI2_CS_Pin,GPIO_PIN_RESET)	//片选置低




uint8_t drv_spi_read_write_byte( uint8_t TxByte );
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );





#endif

