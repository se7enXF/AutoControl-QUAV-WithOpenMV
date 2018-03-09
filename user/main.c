#include "public.h"
#include "channel.h"
#include "apm_function.h"
#include "yaokongqi.h"
#include "chaoshengbo.h"
#include "openmv.h"

int main()
{
	SystemInit();					//ϵͳʱ�ӳ�ʼ��
	channel_init();					//PWM�����ʼ��
	yaokongqi_init();				//ң������ʼ��
	sr04_init();					//����������ʼ��
	openmv_init();					//openmv���ճ�ʼ��
	delay_s(2);						//��ʱ2��
	
	while(1)
	{
		key_test();
		if (key_status[0] == 1)
			ALT_HOLD();
		
		delay_ms(10);
		LED_display();
	}	
}


