#ifndef openmv_h
#define openmv_h
#include "stm32f10x.h"

#define IN_PORT	GPIOE		//�˿�
#define	IN1 GPIO_Pin_8		//PE8,
#define IN2 GPIO_Pin_9		//PE9,
#define IN3 GPIO_Pin_10		//PE10,
#define IN4 GPIO_Pin_11		//PE11,

void openmv_init(void);
void openmv_test(void);
	
#endif
