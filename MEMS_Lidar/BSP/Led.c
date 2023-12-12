#include "Led.h"


//void debug_led_on()
//{
//	HAL_GPIO_WritePin(UserLed_GPIO_Port, UserLed_Pin, GPIO_PIN_RESET);
//}
//
//void debug_led_toggle()
//{
//	HAL_GPIO_TogglePin(UserLed_GPIO_Port, UserLed_Pin);
//}
//
//void debug_led_off()
//{
//	HAL_GPIO_WritePin(UserLed_GPIO_Port, UserLed_Pin, GPIO_PIN_SET);
//}

void yellow_led_on()
{
	HAL_GPIO_WritePin(BAT_STATE1_GPIO_Port, BAT_STATE1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BAT_STATE2_GPIO_Port, BAT_STATE2_Pin, GPIO_PIN_SET);
}

void red_led_on()
{
	HAL_GPIO_WritePin(BAT_STATE2_GPIO_Port, BAT_STATE2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BAT_STATE1_GPIO_Port, BAT_STATE1_Pin, GPIO_PIN_SET);
}


void orange_led_on()
{
	HAL_GPIO_WritePin(BAT_STATE1_GPIO_Port, BAT_STATE1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BAT_STATE2_GPIO_Port, BAT_STATE2_Pin, GPIO_PIN_RESET);
}
void led_off()
{
	HAL_GPIO_WritePin(BAT_STATE1_GPIO_Port, BAT_STATE1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(BAT_STATE2_GPIO_Port, BAT_STATE2_Pin, GPIO_PIN_SET);
}


void red_led_toggle()
{
	HAL_GPIO_TogglePin(BAT_STATE2_GPIO_Port, BAT_STATE2_Pin);
	HAL_GPIO_WritePin(BAT_STATE1_GPIO_Port, BAT_STATE1_Pin, GPIO_PIN_SET);
}

void yellow_led_toggle()
{
	HAL_GPIO_TogglePin(BAT_STATE1_GPIO_Port, BAT_STATE1_Pin);
	HAL_GPIO_WritePin(BAT_STATE2_GPIO_Port, BAT_STATE2_Pin, GPIO_PIN_SET);
}

void wifi_led_on()
{
	HAL_GPIO_WritePin(WIFI_LED_GPIO_Port, WIFI_LED_Pin, GPIO_PIN_RESET);//�����Ƴ���
}

void wifi_led_off()
{
	HAL_GPIO_WritePin(WIFI_LED_GPIO_Port, WIFI_LED_Pin, GPIO_PIN_SET);//Ϩ��������
}

void wifi_led_toggle()
{
	HAL_GPIO_TogglePin(WIFI_LED_GPIO_Port, WIFI_LED_Pin);
}







