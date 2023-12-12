/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   SI4432配置C文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */


#include "drv_SI4432.h"
//#include "drv_delay.h"


uint8_t g_Status1 = 0, g_Status2 = 0;

  
/**
  * @brief :SI4432读寄存器 
  * @param :
  *			@ReadAddr：读寄存器地址
  * @note  :无
  * @retval:寄存器值
  */
uint8_t SI4432_Read_Reg( uint8_t ReadAddr )
{
	uint8_t l_ReadValue = 0;
	
	SI_SET_CSN_LOW( );
	
	SI4432_Tx_Byte( ReadAddr );
	l_ReadValue = SI4432_Rx_Byte( );
	
	SI_SET_CSN_HIGH( );
	
	return l_ReadValue;
}

/**
  * @brief :SI4432写寄存器 
  * @param :
  *			@WriteAddr：寄存器地址
  *			@WriteValue：写入值
  * @note  :无
  * @retval:无
  */
void SI4432_Write_Reg( uint8_t WriteAddr, uint8_t WriteValue )
{
	SI_SET_CSN_LOW( );
	
	SI4432_Tx_Byte( WriteAddr | 0x80 );
	SI4432_Tx_Byte( WriteValue );
	
	SI_SET_CSN_HIGH( );
}

/**
  * @brief :SI4432读中断状态1
  * @param :无
  * @note  :无
  * @retval:中断状态寄存器1值
  */
uint8_t SI4432_Get_It_Status1( void )
{
	return ( SI4432_Read_Reg( 0x03 ));
}

/**
  * @brief :SI4432读中断状态2
  * @param :无
  * @note  :无
  * @retval:中断状态寄存器2值
  */
uint8_t SI4432_Get_It_Status2( void )
{
	return ( SI4432_Read_Reg( 0x04 ));
}

/**
  * @brief :SI4432 SW复位
  * @param :无
  * @note  :无
  * @retval:
  */
void SI4432_SW_Reset( void )
{
	SI4432_Write_Reg( 0x07, 0x80 );
}

/**
  * @brief :SI4432设置同步字段
  * @param :
  *			@SyncValue：同步字段字符
  * @note  :无
  * @retval:
  */
void SI4432_Set_Sync( uint16_t SyncValue )
{
	SI4432_Write_Reg( 0x36, (uint8_t)( SyncValue >> 8 ));				
	SI4432_Write_Reg( 0x37, (uint8_t)SyncValue );
}

/**
  * @brief :SI4432清RX FIFO
  * @param :无
  * @note  :无
  * @retval:无
  */
void SI4432_Clear_Rx_FIFO( void )
{
	SI4432_Write_Reg(0x08, 0x02);										
	SI4432_Write_Reg(0x08, 0x00);
}

/**
  * @brief :SI4432开始发送
  * @param :无
  * @note  :无
  * @retval:无
  */
void SI4432_Start_Tx( void )
{
	SI4432_Write_Reg( 0x07, 0x09 );
}

/**
  * @brief :SI4432启动接收通道
  * @param :无
  * @note  :无
  * @retval:无
  */
void SI4432_Start_Rx( void )
{
	SI4432_Write_Reg( 0x07, 0x05 );
}

/**
  * @brief :SI4432发送数据
  * @param :
  *			@pTxBuff：发送数据缓冲区首地址
  *			@TxLength：数据长度
  * @note  :无
  * @retval:无
  */
void SI4432_Tx_Packet( uint8_t *pTxBuff, uint8_t TxLength )
{
	uint16_t i = 0;
	
	SI4432_Write_Reg( 0x07, 0x01 );			//关接收通道
	SI4432_Write_Reg( 0x3E, TxLength );		//写入发送数据个数
	
	while( TxLength-- )
	{
		SI4432_Write_Reg( 0x7F, *pTxBuff );	//写入发送数据
		pTxBuff++;
	}
	
	//关闭其他中断，仅使能发送完成中断
	SI4432_Write_Reg( 0x05, 0x04 );			
	SI4432_Write_Reg( 0x06, 0x00 );
	
	//读中断中断，清除所有中断挂起
	g_Status1 = SI4432_Get_It_Status1( );								
	g_Status2 = SI4432_Get_It_Status2( );
	
	SI4432_Write_Reg( 0x07, 0x09 );			//启动发送
	
	while( 1 == SI_GET_IRQ_STATUS( ))		//等IRQ状态为,发送完成标志
	{
//		HAL_Delay( 1 );
//		if( 500 == i++ )
//		{
//			i = 0;
//			SI4432_Init( );
//			break;
//		}
	}
	//清中断状态
	g_Status1 = SI4432_Get_It_Status1( );
	g_Status2 = SI4432_Get_It_Status2( );
	
//	HAL_Delay( 20 );
	//使能接收中断  和 CRC错误中断
	SI4432_Write_Reg( 0x05, 0x03 ); 					
	SI4432_Write_Reg( 0x06, 0x00 );
	//清中断标志位
	g_Status1 = SI4432_Get_It_Status1( );
	g_Status2 = SI4432_Get_It_Status2( );
	
	SI4432_Write_Reg( 0x07, 0x05 );			//使能接收通道
	
}

/**
  * @brief :SI4432发送数据
  * @param :
  *			@pRxBuff：接收数据存放缓冲区首地址
  * @note  :无
  * @retval:接收数据个数
  */
uint8_t SI4432_Rx_Packet( uint8_t *pRxBuff )
{
	uint8_t i = 0, l_Length = 0;
	uint16_t NonRxPacket_Ms = 0;
	
//	if( 0 == SI_GET_IRQ_STATUS( ))
	{
		SI4432_Write_Reg( 0x07, 0x01 );				//关接收通道
		
		//清中断标志
		g_Status1 = SI4432_Get_It_Status1( );
		g_Status2 = SI4432_Get_It_Status2( );		
		
		if(( g_Status1 & 0x01) == 0x01 )
		{
			//CRC错误中断标志位置1 清RX FIFO 
			SI4432_Write_Reg(0x08, 0x02);										
			SI4432_Write_Reg(0x08, 0x00);							
		}
		
		if(( g_Status1 & 0x02) == 0x02 )
		{
			//接收中断标志位置1
			l_Length = SI4432_Read_Reg( 0x4B );
			
			if( l_Length < SI4432_DATA_LEN_MAX )
			{
				for( i = 0; i < l_Length; i++ )
				{
					pRxBuff[ i ] = SI4432_Read_Reg( 0x7F );
				}
			}
		}
		
		//清RX FIFO
		SI4432_Write_Reg( 0x08, 0x02 );													
		SI4432_Write_Reg( 0x08, 0x00 );									
		
		SI4432_Write_Reg( 0x07, 0x05 );			//开启接收通道
	}
//	else
//	{
//		drv_delay_ms( 1 );
//		if( 3000 == NonRxPacket_Ms++ )
//		{
//			SI4432_Init( );	
//		}
//	}
	
	return l_Length;
}

/**
  * @brief :SI4432引脚初始化 
  * @param :无
  * @note  :无
  * @retval:无
  */
//void SI4432_Gpio_Init( void )
//{
//	GPIO_InitTypeDef	GpioInitStructer;
//	
//	//打开端口时钟
//	RCC_APB2PeriphClockCmd( SI4432_SDN_CLK | SI4432_IRQ_CLK | SI4432_GPIO1_CLK | SI4432_GPIO2_CLK | SI4432_GPIO0_CLK, ENABLE );	
//	
//	//SDN 配置为推挽输出
//	GpioInitStructer.GPIO_Speed = GPIO_Speed_2MHz;
//	GpioInitStructer.GPIO_Mode = GPIO_Mode_Out_PP;
//	GpioInitStructer.GPIO_Pin = SI4432_SDN_PIN;
//	GPIO_Init( SI4432_SDN_PORT, &GpioInitStructer );
//	GPIO_ResetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN );	//置低使能设备
////	SI_SET_SDN_LOW( );

//	//IRQ GPIO0~2配置为上拉输入
//	GpioInitStructer.GPIO_Mode = GPIO_Mode_IPU;
//	GpioInitStructer.GPIO_Pin = SI4432_IRQ_PIN;
//	GPIO_Init( SI4432_IRQ_PORT, &GpioInitStructer );		//IRQ
//	
//	GpioInitStructer.GPIO_Pin = SI4432_GPIO0_PIN;
//	GPIO_Init( SI4432_GPIO0_PORT, &GpioInitStructer );		//GPIO0
//	
//	GpioInitStructer.GPIO_Pin = SI4432_GPIO1_PIN;
//	GPIO_Init( SI4432_GPIO1_PORT, &GpioInitStructer );		//GPIO1
//	
//	GpioInitStructer.GPIO_Pin = SI4432_GPIO2_PIN;
//	GPIO_Init( SI4432_GPIO2_PORT, &GpioInitStructer );		//GPIO2
//}

/**
  * @brief :SI4432初始化 
  * @param :无
  * @note  :无
  * @retval:无
  */
	void SI4432_Init( void )
{
	uint8_t i = 0;
	
//	SI4432_Gpio_Init( );	//引脚初始化
	HAL_Delay( 50 );
	
	g_Status1 = SI4432_Get_It_Status1( );
	g_Status2 = SI4432_Get_It_Status2( );
	
	SI4432_SW_Reset( );		//SW复位
	while( 1 == SI_GET_IRQ_STATUS( ))		//等IRQ状态为0
	{
	}
	g_Status1 = SI4432_Get_It_Status1( );
	g_Status2 = SI4432_Get_It_Status2( );
	
	while( 1 == SI_GET_IRQ_STATUS( ))		//查看是否释放
	{
	}
	g_Status1 = SI4432_Get_It_Status1( );
	g_Status2 = SI4432_Get_It_Status2( );
	
	//设置中心频率，434M
	SI4432_Write_Reg( 0x75, 0x53 );
	SI4432_Write_Reg( 0x76, 0x64 );
	SI4432_Write_Reg( 0x77, 0x00 );
	
	//AFC 限制
	SI4432_Write_Reg( 0x2A, 0x14 );
	
	//设置通信速率  (xxkbps)	
	SI4432_Write_Reg( 0x6E, 0x0A );
	SI4432_Write_Reg( 0x6F, 0x3D );
	SI4432_Write_Reg( 0x70, 0x0C );//0x_C
	
	//设置TX 偏差 +-45kHz
    SI4432_Write_Reg(0x72, 0x38);	

	//设置 IF 带宽 时钟 AFC等参数
	SI4432_Write_Reg( 0x1C, 0x05 );						
	SI4432_Write_Reg( 0x20, 0x64 );					
	SI4432_Write_Reg( 0x21, 0x01 );					
	SI4432_Write_Reg( 0x22, 0x47 );					
	SI4432_Write_Reg( 0x23, 0xAE );						
	SI4432_Write_Reg( 0x24, 0x02 );						
	SI4432_Write_Reg( 0x25, 0xEF );					
	SI4432_Write_Reg( 0x1D, 0x44 );						
	SI4432_Write_Reg( 0x1E, 0x0A );					
	SI4432_Write_Reg( 0x2A, 0x2D );					
	
	SI4432_Write_Reg( 0x34, 0x0A );				//前导码长度
	SI4432_Write_Reg( 0x35, 0x2A );				//前导码检测阀值20个字节 			
	SI4432_Write_Reg( 0x33, 0x02 );				//关闭发送接收头 设置同步字段长度为3 和 2 	  

	//设置同步字段
	SI4432_Write_Reg( 0x36, 0x2D );				
	SI4432_Write_Reg( 0x37, 0xD4 );				

	
	SI4432_Write_Reg( 0x30, 0x8D );				//使能TX RX CRC16校验				
	SI4432_Write_Reg( 0x32, 0x00 );				//关闭头检测         
	SI4432_Write_Reg( 0x71, 0x63 );				//使能FIFO模式 使能GFSK调制模式

	//设置GPIO0 GPIO1属性 分别代表TX RX 状态
	SI4432_Write_Reg( 0x0B, 0x12 );				
	SI4432_Write_Reg( 0x0C, 0x15 );								
	
	SI4432_Write_Reg( 0x09, 0xD7 );				//设置电容				
	SI4432_Write_Reg( 0x69, 0x60 );				//设置自动增益控制

	SI4432_Write_Reg( 0x6d, 0x1f );				//设置最大发送功率 20dbm 	 
	SI4432_Write_Reg( 0x07, 0x05 );				//使能接收通道
	
	//使能RX（有效数据包）中断，CRC错误中断
	SI4432_Write_Reg( 0x05, 0x03 ); 			
	SI4432_Write_Reg( 0x06, 0x00 ); 			
	//清所有中断挂起
	g_Status1 = SI4432_Get_It_Status1( );		
	g_Status2 = SI4432_Get_It_Status2( );		
    
	SI4432_Write_Reg( 0x07, 0x05 );	
	SI4432_Write_Reg( 0x0d, 0xf4 );	

}
//void SI4432_Init( void )
//{
//	uint8_t i = 0;
//	
////	SI4432_Gpio_Init( );	//引脚初始化
//	HAL_Delay( 50 );
//	
//	g_Status1 = SI4432_Get_It_Status1( );
//	g_Status2 = SI4432_Get_It_Status2( );
//	
//	SI4432_SW_Reset( );		//SW复位
//	while( 1 == SI_GET_IRQ_STATUS( ))		//等IRQ状态为0
//	{
//	}
//	g_Status1 = SI4432_Get_It_Status1( );
//	g_Status2 = SI4432_Get_It_Status2( );
//	
//	while( 1 == SI_GET_IRQ_STATUS( ))		//查看是否释放
//	{
//	}
//	g_Status1 = SI4432_Get_It_Status1( );
//	g_Status2 = SI4432_Get_It_Status2( );
//	
//	//设置中心频率，434M
//	SI4432_Write_Reg( 0x75, 0x53 );
//	SI4432_Write_Reg( 0x76, 0x64 );
//	SI4432_Write_Reg( 0x77, 0x00 );
//	
//	//AFC 限制
//	SI4432_Write_Reg( 0x2A, 0x14 );
//	
//	//设置通信速率
//	SI4432_Write_Reg( 0x6E, 0x09 );
//	SI4432_Write_Reg( 0x6F, 0xd5 );
//	SI4432_Write_Reg( 0x70, 0x2C );
//	
//	//设置TX 偏差 +-45kHz
//    SI4432_Write_Reg(0x72, 0x38);	//(1.2kbps)	

//	//设置 IF 带宽 时钟 AFC等参数
//	SI4432_Write_Reg( 0x1C, 0x1b );						
//	SI4432_Write_Reg( 0x20, 0x83 );					
//	SI4432_Write_Reg( 0x21, 0xc0 );					
//	SI4432_Write_Reg( 0x22, 0x13 );					
//	SI4432_Write_Reg( 0x23, 0xa9 );						
//	SI4432_Write_Reg( 0x24, 0x00 );						
//	SI4432_Write_Reg( 0x25, 0x03 );					
//	SI4432_Write_Reg( 0x1D, 0x40 );						
//	SI4432_Write_Reg( 0x1E, 0x0A );					
//	SI4432_Write_Reg( 0x2A, 0x14 );					
//	
//	SI4432_Write_Reg( 0x34, 0x0A );				//前导码长度
//	SI4432_Write_Reg( 0x35, 0x2A );				//前导码检测阀值20个字节 			
//	SI4432_Write_Reg( 0x33, 0x02 );				//关闭发送接收头 设置同步字段长度为3 和 2 	  

//	//设置同步字段
//	SI4432_Write_Reg( 0x36, 0x2D );				
//	SI4432_Write_Reg( 0x37, 0xD4 );				

//	
//	SI4432_Write_Reg( 0x30, 0x8D );				//使能TX RX CRC16校验				
//	SI4432_Write_Reg( 0x32, 0x00 );				//关闭头检测         
//	SI4432_Write_Reg( 0x71, 0x63 );				//使能FIFO模式 使能GFSK调制模式

//	//设置GPIO0 GPIO1属性 分别代表TX RX 状态
//	SI4432_Write_Reg( 0x0B, 0x12 );				
//	SI4432_Write_Reg( 0x0C, 0x15 );								
//	
//	SI4432_Write_Reg( 0x09, 0xD7 );				//设置电容				
//	SI4432_Write_Reg( 0x69, 0x60 );				//设置自动增益控制

//	SI4432_Write_Reg( 0x6d, 0x1f );				//设置最大发送功率 20dbm 	 
//	SI4432_Write_Reg( 0x07, 0x05 );				//使能接收通道
//	
//	//使能RX（有效数据包）中断，CRC错误中断
//	SI4432_Write_Reg( 0x05, 0x03 ); 			
//	SI4432_Write_Reg( 0x06, 0x00 ); 			
//	//清所有中断挂起
//	g_Status1 = SI4432_Get_It_Status1( );		
//	g_Status2 = SI4432_Get_It_Status2( );		
//    
//	SI4432_Write_Reg( 0x07, 0x05 );	
//	SI4432_Write_Reg( 0x0d, 0xf4 );	

//}

