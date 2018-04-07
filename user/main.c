#include "public.h"
#include "channel.h"
#include "apm_function.h"
#include "yaokongqi.h"
#include "openmv.h"
#include "chaoshengbo.h"

int main()
{
	SystemInit();					//ϵͳʱ�ӳ�ʼ��
	channel_init();					//PWM�����ʼ��
	yaokongqi_init();				//ң������ʼ��
	openmv_init();					//openmv���ճ�ʼ��
	sr04_init();					//��������ʼ��
	delay_s(2);						//��ʱ2��
	
	while(1)
	{
		
		key_test();
		if (key_status[0] == 1)
			ALT_HOLD();
		delay_ms(10);
		LED_display();
		delay_ms(20);
	}	
}


