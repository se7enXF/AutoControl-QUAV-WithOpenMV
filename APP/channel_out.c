/***************************************************
 *����5·PWM����ļ�������GPIO��ʼ������ʱ����ʼ��
 ****************************************************/

#include "channel.h"
#include "public.h"
#include "apm_function.h"

void CH_IO_INIT()																			//ͨ�����IO�ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;													//GPIO��ʼ�����������ṹ��
	//SystemInit();																			//��ʼ��ϵͳʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);				//��GPIOAʱ��,����ʱ��
	
	/*---------TIM2ͨ��1��2��3��4��ӦPA0,PA1,PA2,PA3��Ӧch1,ch2,ch3,ch4----------*/
	/*---------TIM3ͨ��1��ӦPA6��Ӧch5----------*/
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;											//������Ƶ��
	GPIO_InitStructure.GPIO_Pin=ch1|ch2|ch3|ch4|ch5;										//�ܽ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;											//�����������ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);													//��ʼ��				
}

void CH_TIM_INIT()																			//ͨ����ʱ����ʼ��
{
	TIM_TimeBaseInitTypeDef TIM_TimebaseInitStructure;										//��ʱ����ʼ�������ṹ��
	TIM_OCInitTypeDef TIM_OCInitStructure;													//PWM_OUT��ʼ�������ṹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3,ENABLE);					//��TIM2,3ʱ��
	/*----------------------TIM2,3��������-----------------------------*/
	TIM_TimebaseInitStructure.TIM_Period=20000-1;											//PWMƵ��1M/20000=50Hz
	TIM_TimebaseInitStructure.TIM_Prescaler=72-1;											//Ԥ��Ƶ72-1��ʱ��Ϊ72M/72=1M
	TIM_TimebaseInitStructure.TIM_ClockDivision=0x0;										//ʱ�ӷָ�
	TIM_TimebaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;							//���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimebaseInitStructure);										//��ʱ����ʼ��
	TIM_TimeBaseInit(TIM3,&TIM_TimebaseInitStructure);	
	/*---------------------TIM2,3PWM�������---------------------------*/
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;											//PWM1ģʽ
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;								//����OC���
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;									//�������
	TIM_OCInitStructure.TIM_Pulse=1500;														//����ֵ������ռ�ձ�=TIM_Pulse/TIM_Period
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);													//��ʱ��2ͨ��1��ʼ��
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);													//��ʱ��2ͨ��2��ʼ��
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);													//��ʱ��2ͨ��3��ʼ��
	TIM_OC4Init(TIM2,&TIM_OCInitStructure);													//��ʱ��2ͨ��4��ʼ��
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);										//ʹ��TIM2��CCR1�ϵ�Ԥװ�ڼĴ���
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);										//ʹ��TIM2��CCR1�ϵ�Ԥװ�ڼĴ���
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);										//ʹ��TIM2��CCR2�ϵ�Ԥװ�ڼĴ���
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);										//ʹ��TIM2��CCR3�ϵ�Ԥװ�ڼĴ���
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);										//ʹ��TIM2��CCR4�ϵ�Ԥװ�ڼĴ���
	TIM_Cmd(TIM2,ENABLE);																	//��ʱ��ʹ��
	TIM_Cmd(TIM3,ENABLE);	
	//TIM_SetCompare3(TIM2,1500);															//��������ֵ1000~2000,�ı�ռ�ձ�5%~10%
}

void channel_init(void)
{
	/*---��ʼ��IO�ڣ���ʱ���Լ�ͨ�����PWM*/
	CH_IO_INIT();
	CH_TIM_INIT();
	change_ch_value(CH1,1500);
	change_ch_value(CH2,1500);
	change_ch_value(CH3,1000);
	change_ch_value(CH4,1500);
	change_ch_value(CH5,1000);
}


