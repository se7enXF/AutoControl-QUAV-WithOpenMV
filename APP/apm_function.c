/***************************************************
 *���ǿ���APM�ĸ��ֺ���
 ****************************************************/
#include "apm_function.h"
#include "public.h"
#include "string.h"
#include "yaokongqi.h"
#include "openmv.h"
#include "chaoshengbo.h"

/*************************************
#define ch1 GPIO_Pin_0//PA0��TIM2ͨ��1
#define ch2 GPIO_Pin_1//PA1��TIM2ͨ��2
#define ch3 GPIO_Pin_2//PA2��TIM2ͨ��3
#define ch4 GPIO_Pin_3//PA3��TIM2ͨ��4
#define ch5 GPIO_Pin_6//PA6��TIM3ͨ��1
**************************************/

/*---------------------------------------------------------------------------------
ͨ��ռ�ձ����ã���һ������Ϊͨ��CH1~CH5���ڶ�����������ֵ1000~2000��Ӧռ�ձ�5%~10%
----------------------------------------------------------------------------------*/
void change_ch_value(char* ch,int x)
{
	if(strcmp(ch,"ch1") == 0)
		TIM_SetCompare1(TIM2,x);
	else if(strcmp(ch,"ch2") == 0)
		TIM_SetCompare2(TIM2,x);
	else if(strcmp(ch,"ch3") == 0)
		TIM_SetCompare3(TIM2,x);
	else if(strcmp(ch,"ch4") == 0)
		TIM_SetCompare4(TIM2,x);
	else if(strcmp(ch,"ch5") == 0)
		TIM_SetCompare1(TIM3,x);
}


void unlock(void)				//�����ɿ�
{
	change_ch_value(CH3,1000);	//1000~2000
	change_ch_value(CH4,2000);
	delay_s(5);
	change_ch_value(CH4,1500);
}

void lock(void)					//�����ɿ�
{
	change_ch_value(CH3,1000);
	change_ch_value(CH4,1000);
	delay_s(5);
	change_ch_value(CH4,1500);
}

void MOD_ALT_HOLD(void)			//�л�������ģʽ
{
	change_ch_value(CH5,1500);
	delay_ms(10);
}

void MOD_Stable(void)			//�л�������ģʽ���ɿ�����ǰ�����ڴ�ģʽ��
{
	change_ch_value(CH5,1000);
	delay_ms(10);
}


void ALT_HOLD(void)
{
	int overtime=0;
	int fix_ch1 = 1000+1000*0.48;
	int fix_ch2 = 1000+1000*0.48;
	
	unlock();												//����
	delay_ms(1000);
	MOD_ALT_HOLD();											//�л�������ģʽ

	change_ch_value(CH3,1500);
	/**********�����ɻ���ˮƽ************************/
	change_ch_value(CH2,fix_ch2);							//��������Y��ǰС���
	change_ch_value(CH1,fix_ch1);							//�������X����С�Ҵ�
 
	/*********�߶ȱ���*******************************/
	while(1)
	{
		key_test();											//�������
		openmv_test();										//openmv������
		if(key_status[1] == 1)
			break;
		
		if(get_hight()<60)									//�߶�С��100cm����
		{
			change_ch_value(CH3,1000+1000*0.65);			//UP
			if(openmv_status[0] == 1)
				change_ch_value(CH1,fix_ch1-1000*0.2);	//L
			else if(openmv_status[1] == 1)
				change_ch_value(CH1,fix_ch1+1000*0.2);	//R
			if(openmv_status[2] == 1)
				change_ch_value(CH2,fix_ch2+1000*0.2);	//F
			else if(openmv_status[3] == 1)
				change_ch_value(CH2,fix_ch2-1000*0.2);	//B
				
			delay_ms(20);
			change_ch_value(CH3,1500);
			change_ch_value(CH1,fix_ch1);
			change_ch_value(CH2,fix_ch2);
		}
		else if(get_hight()>70)							//�߶ȴ���120cm����
		{
			change_ch_value(CH3,1000+1000*0.45);		//DOWN
			if(openmv_status[0] == 1)
				change_ch_value(CH1,fix_ch1-1000*0.2);	//L
			else if(openmv_status[1] == 1)
				change_ch_value(CH1,fix_ch1+1000*0.2);	//R
			if(openmv_status[2] == 1)
				change_ch_value(CH2,fix_ch2+1000*0.2);	//F
			else if(openmv_status[3] == 1)
				change_ch_value(CH2,fix_ch2-1000*0.2);	//B	
			
			delay_ms(20);
			change_ch_value(CH3,1500);
			change_ch_value(CH1,fix_ch1);
			change_ch_value(CH2,fix_ch2);
		}
		
	}

	/*************����**********************************/
	while(get_hight() > 20)								//�߶ȴ���20cm���ż�С����
	{	
		overtime++;
		change_ch_value(CH3,1000+1000*0.35);			//����
		if(overtime>1000)
			break;
	}
	
	delay_ms(100);
	change_ch_value(CH3,1000);							//��غ�������С
	MOD_Stable();										//�л�����ģʽ
	lock();												//����
}	


