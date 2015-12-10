#include "stm32f10x.h"
#include "stm32f107.h"
#include <string.h>

volatile unsigned int  CAN_ID;		//unsigned intΪ32λ�� unsigned short intΪ16λ��
unsigned char CAN1_DATA[8] = {'a','a','a','a','a','a','a','a'};
const unsigned char flag[8] = {'1','a','a','a','a','a','a','a'};
volatile unsigned char CanRec_flag = 0;
volatile unsigned char enable_meter_flag = 0;
volatile unsigned char disable_meter_flag = 0;

void NVIC_Configuration(void); 
void GPIO_Configuration(void);
void Filter_List(void);


void CAN_Configuration(void)
{
	CAN_InitTypeDef        CAN_InitStructure;	
	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE; /* ʱ�䴥����ֹ, ʱ�䴥����CANӲ�����ڲ���ʱ����������ұ����ڲ���ʱ��� */
	CAN_InitStructure.CAN_ABOM = DISABLE; /* �Զ����߽�ֹ���Զ����ߣ�һ��Ӳ����ص�128��11������λ�����Զ��˳�����״̬��������Ҫ����趨������˳� */
	CAN_InitStructure.CAN_AWUM = DISABLE; /* �Զ����ѽ�ֹ���б�������ʱ���Զ��˳�����	*/
	CAN_InitStructure.CAN_NART = DISABLE; /* �����ش�, �������һֱ�����ɹ�ֹ������ֻ��һ�� */
	CAN_InitStructure.CAN_RFLM = DISABLE; /* ����FIFO����, 1--��������յ��µı���ժ��Ҫ��0--���յ��µı����򸲸�ǰһ����	*/
	CAN_InitStructure.CAN_TXFP = ENABLE;  /* �������ȼ�  0---�ɱ�ʶ������  1---�ɷ�������˳�����	*/
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /* ģʽ	*/

	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=9;        //�ҵ�ʱ����PLL 72M,��ôCANӦ����36M�˰�?��������36/((1+8+7)*9)=250K	

	if (CAN_Init(CAN1,&CAN_InitStructure) == CANINITFAILED) 		
	{
		
		/* ��ʼ��ʱ������CAN_MCR�ĳ�ʼ��λ */  														
		/* Ȼ��鿴Ӳ���Ƿ����������CAN_MSR�ĳ�ʼ��λ��ȷ���Ƿ�����˳�ʼ��ģʽ  */		 													                  
	}
	
	if (CAN_Init(CAN2,&CAN_InitStructure) == CANINITFAILED) 		
	{
		
		/* ��ʼ��ʱ������CAN_MCR�ĳ�ʼ��λ */ 												
		/* Ȼ��鿴Ӳ���Ƿ����������CAN_MSR�ĳ�ʼ��λ��ȷ���Ƿ�����˳�ʼ��ģʽ  */		 													                  
	}	

	Filter_List();//Ϊ0ʱ�������κ�ID
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);   /* �Һ��ж�, �����жϺ��fifo�ı��ĺ����ͷű������жϱ�־ */
	CAN_ITConfig(CAN2,CAN_IT_FMP0, ENABLE);   /* �Һ��ж�, �����жϺ��fifo�ı��ĺ����ͷű������жϱ�־ */
	
}

/*******************************************************************************
can1һ����������14����������.can1�Ĺ������Ŵ�0��ʼ��13������can2��13��ʼ��27����
*******************************************************************************/
void  Filter_List(void)
{
	unsigned int temp_id = 0;

	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/******can1��0�����������*******/
	temp_id = 0x18400000;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;     ///* �������� */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//CAN_FilterMode_IdList;//CAN_FilterMode_IdMask;  /* ����ģʽ */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; ///* 32λ */
	CAN_FilterInitStructure.CAN_FilterIdHigh = (temp_id<<3)>>16;//(id<<3)>>16;  
	CAN_FilterInitStructure.CAN_FilterIdLow = (temp_id<<3)|CAN_ID_EXT|CAN_RTR_DATA;//��չ֡
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffff;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xffff;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;  ///* �ܹ�ͨ���ù������ı��Ĵ浽fifo0�� */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);	
//	
	/******can2��1�����������*******/
	temp_id = 0x18412345;
	CAN_FilterInitStructure.CAN_FilterNumber = 14;     ///* �������� */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//CAN_FilterMode_IdList;//CAN_FilterMode_IdMask;  /* ����ģʽ */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; ///* 32λ */
	CAN_FilterInitStructure.CAN_FilterIdHigh = (temp_id<<3)>>16;//(id<<3)>>16;  
	CAN_FilterInitStructure.CAN_FilterIdLow = (temp_id<<3)|CAN_ID_EXT|CAN_RTR_DATA;//��չ֡
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffff;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xffff;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;  ///* �ܹ�ͨ���ù������ı��Ĵ浽fifo0�� */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
		
}

void Can1_WriteData(unsigned int ID, unsigned char *txbuf)
{		
	unsigned char i;
	CanTxMsg TxMessage;

	TxMessage.ExtId = ID;
	TxMessage.IDE = CAN_ID_EXT;
	TxMessage.RTR = CAN_RTR_DATA; /* ����Ϊ����֡ */
	TxMessage.DLC = 8;            /* ���ݳ���, can���Ĺ涨�������ݳ���Ϊ8�ֽ� */

	for(i = 0;i < 8; i ++)
	{
		CAN1_DATA[i] = txbuf[i];
		TxMessage.Data[i] = CAN1_DATA[i];//can_send_data[i];
	}
	CAN_Transmit(CAN1,&TxMessage);  /* ���������Ϣ�����͵������0,1,2��û���������뷢��no_box */	
}


//CAN2�жϳ���
int CAN2_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage; 
	unsigned char i;
	int j=0;

	CAN_Receive(CAN2,CAN_FIFO0, &RxMessage);  /* �˺��������ͷ���������˵�,�ڷǱ�Ҫʱ,����Ҫ�Լ��ͷ� */
	//CAN_ID = RxMessage.ExtId;
	for(i = 0;i < 8; i ++)
	{
		CAN1_DATA[i] = RxMessage.Data[i];
	}
	CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);  /* ��������ж� */
	
	for(i=0; i<8; i++){
		if(CAN1_DATA[i] == flag[i])		j++;
	}
	if(j==8){
		j=0;
		CAN1_DATA[0]=0;
		One_LED_ON('1');
		delay_ms(500);
		One_LED_ON(2);
		delay_ms(500);
		return 1;
	}
	j=0;
	return 0;
}
