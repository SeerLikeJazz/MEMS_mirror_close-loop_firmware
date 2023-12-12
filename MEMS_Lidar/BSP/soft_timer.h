/* soft_timer.c/h  3.0 */

#ifndef _SOFT_TIMER_H
#define _SOFT_TIMER_H

#include "stdint.h"

#define  tickCnt_Get()   HAL_GetTick()

/* �����ʱ��ʱ�ӽ��ĵ�λ */
#define TIME_BASE_MS			          1    //1ms

/* �����ʱ������ */
#define TIMER_NUM                   5

/* ��ʱ��ID */
#define TMR_WIFI_BLINKY             0
#define TMR_SHUTDOWN_CHARGING       1
#define TMR_SEND_DATA               2
#define TMR_Period_Task             3
//#define TMR_xxx                   4


typedef void callback(void *argv, uint16_t argc);

typedef struct softTimer {
	uint8_t state;           //״̬
	uint8_t mode;            //ģʽ
	uint32_t match;          //����ʱ��
	uint32_t period;         //��ʱ����
	callback *cb;            //�ص�����ָ��
	void *argv;              //����ָ��
	uint16_t argc;           //��������
}softTimer;

typedef enum tmrState {
	SOFT_TIMER_STOPPED = 0,  //ֹͣ
	SOFT_TIMER_RUNNING,      //����
	SOFT_TIMER_TIMEOUT       //��ʱ
}tmrState;

typedef enum tmrMode {
	MODE_ONE_SHOT = 0,       //����ģʽ
	MODE_PERIODIC,           //����ģʽ
}tmrMode;


//void tickCnt_Update(void);
//uint32_t tickCnt_Get(void);
void softTimer_Init(void);
uint8_t softTimer_GetState(uint16_t id);
void softTimer_Start(uint16_t id, tmrMode mode, uint32_t delay, callback *cb, void *argv, uint16_t argc);
void softTimer_Stop(uint16_t id);
void softTimer_Update(void);

#endif //_SOFT_TIMER_H
