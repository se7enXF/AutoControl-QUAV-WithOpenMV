#include "sonar.h"
#include "public.h"

int distance;
int overcount;
int key = 0 ;
void Sonar_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
    //PA4TRAG
	GPIO_InitStructure.GPIO_Pin = TRIG_PIN;						//PA4��TRIG
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  	//��Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
	GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	               	//��ʼ������GPIO 

	//PA7ECHO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 		//��Ϊ��������
	GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				    
	GPIO_Init(ECHO_PORT,&GPIO_InitStructure);					//��ʼ��GPIOA7
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);	//���ж���PA7
	//�жϳ�ʼ��
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_Init(&EXTI_InitStructure);	
	
	/*��ʱ��TIM4��ʼ��*/
	TIM_DeInit(TIM4);
	TIM_TimeBaseInitStructer.TIM_Period=999;						//��ʱ����Ϊ1000
	TIM_TimeBaseInitStructer.TIM_Prescaler=71; 						//��Ƶϵ��72
	TIM_TimeBaseInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;		//����Ƶ
	TIM_TimeBaseInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructer);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);						//���������ж�
	TIM_Cmd(TIM4,ENABLE);											//�򿪶�ʱ��
		
	//����ECHO�ж�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				
  	NVIC_Init(&NVIC_InitStructure);  	
	//����TIMER�����ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);  
}

void UltrasonicWave_StartMeasure(void)
{
	*(__IO uint16_t *) (EXTI_RTSR_TR7) = 1;	//��EXTI7�����ش���
	*(__IO uint16_t *) (EXTI_FTSR_TR7) = 0;	//�ر�EXTI7�½��ش���
	
	overcount=0;
	key=0;
	GPIO_SetBits(TRIG_PORT,TRIG_PIN);	//��>10US�ĸߵ�ƽ
	delay_us(10);
	GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	
	TIM_SetCounter(COUNT_TIMER,0);		//��ʱ��������0
}



void EXTI9_5_IRQHandler(void)		//ECHO�����жϳ���
{
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{		          
		if(key == 0)
		{
			TIM_Cmd(COUNT_TIMER, ENABLE); 		//�򿪶�ʱ��
			
			*(__IO uint16_t *) (EXTI_RTSR_TR7) = 0;	//�ر�EXTI7�����ش���
			*(__IO uint16_t *) (EXTI_FTSR_TR7) = 1;	//��EXTI7�½��ش���
			
			distance = TIM_GetCounter(COUNT_TIMER);						
			EXTI_ClearITPendingBit(EXTI_Line7); 
			key = 1;
		}	
		else
		{
			distance = (TIM_GetCounter(TIM4)+overcount*1000)/58.0;
		}
	}

}

void TIM4_IRQHandler(void)   
{
    if (TIM_GetITStatus(COUNT_TIMER, TIM_IT_Update) != RESET)  	//���TIM4�����жϷ������
	{
		TIM_ClearITPendingBit(COUNT_TIMER, TIM_IT_Update);  	//���TIMx�����жϱ�־ 
		GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
		overcount++;
	}
}

