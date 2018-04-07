/*********************************************************
 *���ǳ���������ļ�������GPIO��ʼ������ʱ����ʼ�������ж�����
 ********************************************************/
 
#include "chaoshengbo.h"
#include "public.h"

u16 overcount=0;

/*----�ж�����----*/
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructer;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructer.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructer);
}

/*-----�˿ڳ�ʼ������ʱ����ʼ��-----*/
void sr04_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	/*TRIG�����ź�*/
	GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructer.GPIO_Pin=Trig;
	GPIO_Init(GPIOB,&GPIO_InitStructer);

	/*ECOH�����ź�*/
	GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructer.GPIO_Pin=Echo;
	GPIO_Init(GPIOB,&GPIO_InitStructer);

	/*��ʱ��TIM4��ʼ��*/
	TIM_DeInit(TIM4);
	TIM_TimeBaseInitStructer.TIM_Period=999;						//��ʱ����Ϊ1000
	TIM_TimeBaseInitStructer.TIM_Prescaler=71; 						//��Ƶϵ��72
	TIM_TimeBaseInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;		//����Ƶ
	TIM_TimeBaseInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructer);

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);						//���������ж�
	NVIC_Config();
	TIM_Cmd(TIM4,DISABLE);											//�رն�ʱ��ʹ��
}


/*-------���������������ź�-------*/
void trig_signal(void)
{
	GPIO_WriteBit(GPIOB,Trig,Bit_SET);
	delay_us(20);
	GPIO_WriteBit(GPIOB,Trig,Bit_RESET);
}

/*-------��������-----------------*/
float get_hight(void)
{
	float length=0,sum=0;
	u16 i=0;
	/*��5�����ݼ���һ��ƽ��ֵ*/
	while(i!=5)
	{
		TIM4->CNT=0;  											//��TIM2�����Ĵ����ļ���ֵ����
		trig_signal();
		
		while(GPIO_ReadInputDataBit(GPIOB,Echo)==RESET);		//�ȴ������ź�
		TIM_Cmd(TIM4,ENABLE);									//�����źŵ�����������ʱ������
		i+=1; 													//ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
		while(GPIO_ReadInputDataBit(GPIOB,Echo)==SET);			//�����ź���ʧ
		TIM_Cmd(TIM4,DISABLE);									//�رն�ʱ��

		length=(TIM_GetCounter(TIM4)+overcount*1000)/58.0;		//ͨ�������źż������,��λcm
		sum=length+sum;
		overcount=0;  											//�ж������������
		delay_ms(100);
	}
	return length=sum/5;												//������Ϊ��������ֵ
}


/*�жϣ��������źźܳ�ʱ������ֵ������ظ����������ж��������������*/
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)				//�Ƿ�Ϊ��ʱ��4�����ж�
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);				//����жϱ�־
		overcount++;
	}
}

