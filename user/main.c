#include "public.h"
#include "channel.h"
#include "apm_function.h"
#include "yaokongqi.h"
#include "chaoshengbo.h"
#include "openmv.h"

int main()
{
	SystemInit();					//系统时钟初始化
	channel_init();					//PWM输出初始化
	yaokongqi_init();				//遥控器初始化
	sr04_init();					//超声波测距初始化
	openmv_init();					//openmv接收初始化
	delay_s(2);						//延时2秒
	
	while(1)
	{
		key_test();
		if (key_status[0] == 1)
			ALT_HOLD();
		
		delay_ms(10);
		LED_display();
	}	
}


