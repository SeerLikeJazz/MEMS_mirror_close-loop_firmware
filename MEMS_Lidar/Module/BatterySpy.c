#include "BatterySpy.h"
#include "Led.h"


extern uint8_t ADC_Cplt_Flag;
uint32_t  Bat_Sum;
extern uint16_t AD_Value[50] __attribute__ ((at(0x30000000)));//SRAM1

extern volatile uint8_t eCon_Message[150];

uint32_t GetBatAvr(uint16_t * p_bat_data, uint8_t length)
{
	uint32_t sum=0;
	for(uint8_t i=0;i<length;i++)
	{
        sum += * p_bat_data++;
	}
	sum /= length;
	return sum;
}

void bat_capacity_process()
{
	if(ADC_Cplt_Flag) {
		ADC_Cplt_Flag = 0;
		Bat_Sum = GetBatAvr(&AD_Value[10],BatLength);//只计算中间30个
        if(Bat_Sum >= 38726){//大于3.9V->3.9/2/3.3*4096=2420
            eCon_Message[100] = 100;
            yellow_led_on();
        }
        else if((Bat_Sum >= 38086) && (Bat_Sum < 38486)){//90-3.83V
            eCon_Message[100] = 90;
            yellow_led_on();
        }
        else if((Bat_Sum >= 37446) && (Bat_Sum < 37846)){//80-3.77V
            eCon_Message[100] = 80;
            yellow_led_on();
        }
        else if((Bat_Sum >= 36806) && (Bat_Sum < 37206)){//70
            eCon_Message[100] = 70;
            yellow_led_on();
        }
        else if((Bat_Sum >= 36166) && (Bat_Sum < 36566)){//60
            eCon_Message[100] = 60;
            orange_led_on();
        }
        else if((Bat_Sum >= 35526) && (Bat_Sum < 35926)){//50-3.58V
            eCon_Message[100] = 50;
            orange_led_on();
        }
        else if((Bat_Sum >= 34886) && (Bat_Sum < 35286)){//40-3.51V
            eCon_Message[100] = 40;
            orange_led_on();
        }
        else if((Bat_Sum >= 34246) && (Bat_Sum < 34646)){//30-3.45V
            eCon_Message[100] = 30;
            red_led_on();
        }
        else if((Bat_Sum >= 33606) && (Bat_Sum < 34006)){//20-3.38V
            eCon_Message[100] = 20;
            red_led_on();
        }
        else if((Bat_Sum >= 32966) && (Bat_Sum < 33366)){//10-3.32V
            eCon_Message[100] = 10;
            red_led_on();
        }
        else{}
	}

}

void bat_capacity_1st()
{

		Bat_Sum = GetBatAvr(&AD_Value[10],BatLength1st);
        if(Bat_Sum >= 38726){//大于3.9V->3.9/2/3.3*65535=38725
            eCon_Message[100] = 100;
            yellow_led_on();
        }
        else if((Bat_Sum >= 38086) && (Bat_Sum < 38726)){//90-3.83V
            eCon_Message[100] = 90;
            yellow_led_on();
        }
        else if((Bat_Sum >= 37446) && (Bat_Sum < 38086)){//80-3.77V
            eCon_Message[100] = 80;
            yellow_led_on();
        }
        else if((Bat_Sum >= 36806) && (Bat_Sum < 37446)){//70-3.71V
            eCon_Message[100] = 70;
            yellow_led_on();
        }
        else if((Bat_Sum >= 36166) && (Bat_Sum < 36806)){//60-3.64V
            eCon_Message[100] = 60;
            orange_led_on();
        }
        else if((Bat_Sum >= 35526) && (Bat_Sum < 36166)){//50-3.58V
            eCon_Message[100] = 50;
            orange_led_on();
        }
        else if((Bat_Sum >= 34886) && (Bat_Sum < 35526)){//40-3.51V
            eCon_Message[100] = 40;
            orange_led_on();
        }
        else if((Bat_Sum >= 34246) && (Bat_Sum < 34886)){//30-3.45V
            eCon_Message[100] = 30;
            red_led_on();
        }
        else if((Bat_Sum >= 33606) && (Bat_Sum < 34246)){//20-3.38V
            eCon_Message[100] = 20;
            red_led_on();
        }
        else if((Bat_Sum >= 32966) && (Bat_Sum < 33606)){//10-3.32V
            eCon_Message[100] = 10;
            red_led_on();
        }
        else{//5
            eCon_Message[100] = 5;
            red_led_on();
        }

}











