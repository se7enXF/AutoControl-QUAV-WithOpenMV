#ifndef yaokongqi_h
#define yaokongqi_h
#include "stm32f10x.h"

#define LED2 GPIO_Pin_14	//���İ��ϵ�LED D2������G14���ߵ�ƽ��
#define D0 GPIO_Pin_9		//PG9,��ƽ�����ź�D0
#define D1 GPIO_Pin_10		//PG10,��ƽ�����ź�D1

extern int key_status[2];
void yaokongqi_init(void);
void key_test(void);
void LED_display(void);
	
#endif
