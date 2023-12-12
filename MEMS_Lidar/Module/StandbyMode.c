#include "StandbyMode.h"
#include "tim.h"
#include "Led.h"
#include "adc.h"
#include "soft_timer.h"
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
PWREx_WakeupPinTypeDef sPinParams;
/* Private define ------------------------------------------------------------*/
#define PWR_WAKEUP_PIN_FLAGS  (PWR_WAKEUP_FLAG1 | PWR_WAKEUP_FLAG2 | PWR_WAKEUP_FLAG3 | \
                               PWR_WAKEUP_FLAG4 | PWR_WAKEUP_FLAG5 | PWR_WAKEUP_FLAG6)

/*待机模式*/
void StandbyMode_Measure(void)
{
	{
//		__disable_irq();
//		HAL_GPIO_DeInit(GPIOC,GPIO_PIN_4);//1299
//		HAL_NVIC_DisableIRQ(EXTI4_IRQn);
//		
//		__HAL_GPIO_EXTI_CLEAR_IT(NIRQ_Pin);//SI4432
//		__HAL_GPIO_EXTI_CLEAR_IT(NOTIFY_Pin);//WIFI
//		NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
//		
//		__HAL_GPIO_EXTI_CLEAR_IT(ADS_DRDY_Pin);//1299
//		NVIC_ClearPendingIRQ(EXTI4_IRQn);
//		
//		__HAL_GPIO_EXTI_CLEAR_IT(WKUP_Pin);//Wakeup
//		NVIC_ClearPendingIRQ(EXTI0_IRQn);
	}
	HAL_NVIC_DisableIRQ(USART1_IRQn);
	__HAL_UART_CLEAR_FLAG(&huart1, UART_CLEAR_IDLEF);	
	NVIC_ClearPendingIRQ(USART1_IRQn);
	
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
	__HAL_GPIO_EXTI_CLEAR_IT(NIRQ_Pin);//SI4432
	__HAL_GPIO_EXTI_CLEAR_IT(NOTIFY_Pin);//WIFI
	NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
	
	HAL_NVIC_DisableIRQ(DMA1_Stream0_IRQn);
	NVIC_ClearPendingIRQ(DMA1_Stream0_IRQn);
	
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	__HAL_GPIO_EXTI_CLEAR_IT(WKUP_Pin);
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);
	__HAL_GPIO_EXTI_CLEAR_IT(ADS_DRDY_Pin);
	NVIC_ClearPendingIRQ(EXTI4_IRQn);
	
	HAL_NVIC_DisableIRQ(SysTick_IRQn);
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	
  /* Disable used wakeup source: PWR_WAKEUP_PIN1 */
  HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN1);

  /* Clear all related wakeup flags */
  HAL_PWREx_ClearWakeupFlag(PWR_WAKEUP_FLAG_ALL);

  /* Enable WakeUp Pin PWR_WAKEUP_PIN1 connected to PA.00 */
  sPinParams.WakeUpPin    = PWR_WAKEUP_PIN1;
  sPinParams.PinPolarity  = PWR_PIN_POLARITY_HIGH;
  sPinParams.PinPull      = PWR_PIN_NO_PULL;
  HAL_PWREx_EnableWakeUpPin(&sPinParams);

  /* Enter the Standby mode */
  HAL_PWR_EnterSTANDBYMode();
}

/*充电指示*/
void ChargingState(void)
{
	while(1) {	

		/*充电时读取PGOOD引脚，检测充电器拔出*/
		if(HAL_GPIO_ReadPin(PGOOD_GPIO_Port, PGOOD_Pin) == GPIO_PIN_SET) {
			StandbyMode_Measure();
		}
		/*充电时读取CHG引脚，检测是否充满*/
		if(HAL_GPIO_ReadPin(CHG_GPIO_Port, CHG_Pin) == GPIO_PIN_SET) {
			//此时电源指示灯保持常亮 
			yellow_led_on();	
		}
		else {
			HAL_Delay(500);
			red_led_toggle();	
		}
	}
}

extern volatile uint8_t Charging_Flag;
void Charging_process(void)
{
		if(Charging_Flag) {
			Charging_Flag = 0;
			/*充电的时候关闭用不到的外设，测试一下充电时的功耗*/
			{
				led_off();
				softTimer_Stop(TMR_WIFI_BLINKY);
				wifi_led_off();//熄灭蓝牙灯
				/*！！！关闭3V3电源时，会产生5-9中断，进入4432中断，导致死机*/
				HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
				__HAL_GPIO_EXTI_CLEAR_IT(NIRQ_Pin);//SI4432
				__HAL_GPIO_EXTI_CLEAR_IT(NOTIFY_Pin);//WIFI
				NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
				
				HAL_NVIC_DisableIRQ(EXTI4_IRQn);
				__HAL_GPIO_EXTI_CLEAR_IT(ADS_DRDY_Pin);
				NVIC_ClearPendingIRQ(EXTI4_IRQn);
				
				HAL_NVIC_DisableIRQ(EXTI0_IRQn);
				__HAL_GPIO_EXTI_CLEAR_IT(WKUP_Pin);
				NVIC_ClearPendingIRQ(EXTI0_IRQn);
				/*5V,3V3，WIFI电源关闭*/	
				HAL_GPIO_WritePin(EN_5V_GPIO_Port, EN_5V_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(EN_3V3_GPIO_Port, EN_3V3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(EN_DCDC_GPIO_Port, EN_DCDC_Pin, GPIO_PIN_RESET);
				HAL_TIM_Base_Stop(&htim8);
				HAL_ADC_Stop_DMA(&hadc1);//电池指示灯关闭
			}
			ChargingState();
		}
}








