/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/*脑电盒状态*/
typedef enum
{
    IMPEDANCING    = 'Z',
    WAVE           = 'W',
    INTERNALSHORT  = 'S',
    TESTSIGAL      = 'T',
    STOP           = 'R'
} EEG_StateTypeDef ;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/** 一帧发送的长度*/
#define  Frame_len  1024
/* 是否使用printf */
//#define DEBUG_OUT
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define UserLed_Pin GPIO_PIN_13
#define UserLed_GPIO_Port GPIOC
#define PGOOD_Pin GPIO_PIN_1
#define PGOOD_GPIO_Port GPIOC
#define CHG_Pin GPIO_PIN_2
#define CHG_GPIO_Port GPIOC
#define EN_MOTOR_Pin GPIO_PIN_3
#define EN_MOTOR_GPIO_Port GPIOC
#define WKUP_Pin GPIO_PIN_0
#define WKUP_GPIO_Port GPIOA
#define WKUP_EXTI_IRQn EXTI0_IRQn
#define BAT_STATE1_Pin GPIO_PIN_1
#define BAT_STATE1_GPIO_Port GPIOA
#define BAT_STATE2_Pin GPIO_PIN_2
#define BAT_STATE2_GPIO_Port GPIOA
#define WIFI_LED_Pin GPIO_PIN_3
#define WIFI_LED_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define ADS_DRDY_Pin GPIO_PIN_4
#define ADS_DRDY_GPIO_Port GPIOC
#define ADS_DRDY_EXTI_IRQn EXTI4_IRQn
#define EN_5V_Pin GPIO_PIN_5
#define EN_5V_GPIO_Port GPIOC
#define ICM_INT_Pin GPIO_PIN_1
#define ICM_INT_GPIO_Port GPIOB
#define ICM_INT_EXTI_IRQn EXTI1_IRQn
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define NIRQ_Pin GPIO_PIN_6
#define NIRQ_GPIO_Port GPIOC
#define NIRQ_EXTI_IRQn EXTI9_5_IRQn
#define EN_3V3_Pin GPIO_PIN_7
#define EN_3V3_GPIO_Port GPIOC
#define M8266WIFI_SPI_nCS_Pin GPIO_PIN_15
#define M8266WIFI_SPI_nCS_GPIO_Port GPIOA
#define M8266WIFI_nRESET_Pin GPIO_PIN_6
#define M8266WIFI_nRESET_GPIO_Port GPIOB
#define NOTIFY_Pin GPIO_PIN_7
#define NOTIFY_GPIO_Port GPIOB
#define NOTIFY_EXTI_IRQn EXTI9_5_IRQn
#define EN_DCDC_Pin GPIO_PIN_8
#define EN_DCDC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
