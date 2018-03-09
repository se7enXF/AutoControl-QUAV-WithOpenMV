/***************************************************
 *����ң�������ճ��򣬰���GPIO��ʼ����������⣬��������
 *���һ������������ʾ��LED��LED��˸֤��������һֱ����
 ****************************************************/

#include "yaokongqi.h"
#include "public.h"
#include "apm_function.h"

int key_status[2]={0};													//2����������״̬
int temp=1;

void yaokongqi_init(void)												//ң��������IO�ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure;								//GPIO��ʼ�����������ṹ��																	//��ʼ��ϵͳʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);				//��GPIOGʱ��,����ʱ��
	
	/*---------PG9,����D0----------*/
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//������Ƶ��
	GPIO_InitStructure.GPIO_Pin=D0;										//�ܽ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;							//��������
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	/*---------PG10,����D1---------*/
	GPIO_InitStructure.GPIO_Pin=D1;										//�ܽ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;							//��������
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	/*---------PG14��LED2������ϵͳ����������ʾ----*/
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;						//������Ƶ��
	GPIO_InitStructure.GPIO_Pin=LED2;									//�ܽ�
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;						//�������
	GPIO_Init(GPIOG,&GPIO_InitStructure);		
}

void key_test(void)
{
	int t;
	if(GPIO_ReadInputDataBit(GPIOG, D0) == 1 || GPIO_ReadInputDataBit(GPIOG, D1) == 1)
	{
		delay_ms(5);
		
		/*------keyA------*/
		if(GPIO_ReadInputDataBit(GPIOG, D0) == 1)
			key_status[0]=1;
		else
			key_status[0]=0;
		/*------keyB------*/
		if(GPIO_ReadInputDataBit(GPIOG, D1) == 1)
			key_status[1]=1;
		else
			key_status[1]=0;
	}
	else
	{
		for(t=0;t<2;t++)
		{
			key_status[t]=0;
		}
	}
}

void LED_display(void)
{
	if(temp == 1)
		GPIO_WriteBit(GPIOG, LED2, Bit_SET);
	else
		GPIO_WriteBit(GPIOG, LED2, Bit_RESET);
	temp = -temp;
}

