#include "stm32f10x.h"
#include "stm32f107.h"
#include <string.h>

volatile unsigned int  CAN_ID;		//unsigned int为32位的 unsigned short int为16位的
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
	CAN_InitStructure.CAN_TTCM = DISABLE; /* 时间触发禁止, 时间触发：CAN硬件的内部定时器被激活，并且被用于产生时间戳 */
	CAN_InitStructure.CAN_ABOM = DISABLE; /* 自动离线禁止，自动离线：一旦硬件监控到128次11个隐性位，就自动退出离线状态。在这里要软件设定后才能退出 */
	CAN_InitStructure.CAN_AWUM = DISABLE; /* 自动唤醒禁止，有报文来的时候自动退出休眠	*/
	CAN_InitStructure.CAN_NART = DISABLE; /* 报文重传, 如果错误一直传到成功止，否则只传一次 */
	CAN_InitStructure.CAN_RFLM = DISABLE; /* 接收FIFO锁定, 1--锁定后接收到新的报文摘不要，0--接收到新的报文则覆盖前一报文	*/
	CAN_InitStructure.CAN_TXFP = ENABLE;  /* 发送优先级  0---由标识符决定  1---由发送请求顺序决定	*/
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /* 模式	*/

	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
	CAN_InitStructure.CAN_Prescaler=9;        //我的时钟是PLL 72M,那么CAN应该是36M了吧?这样就是36/((1+8+7)*9)=250K	

	if (CAN_Init(CAN1,&CAN_InitStructure) == CANINITFAILED) 		
	{
		
		/* 初始化时先设置CAN_MCR的初始化位 */  														
		/* 然后查看硬件是否真的设置了CAN_MSR的初始化位来确认是否进入了初始化模式  */		 													                  
	}
	
	if (CAN_Init(CAN2,&CAN_InitStructure) == CANINITFAILED) 		
	{
		
		/* 初始化时先设置CAN_MCR的初始化位 */ 												
		/* 然后查看硬件是否真的设置了CAN_MSR的初始化位来确认是否进入了初始化模式  */		 													                  
	}	

	Filter_List();//为0时不过滤任何ID
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);   /* 挂号中断, 进入中断后读fifo的报文函数释放报文清中断标志 */
	CAN_ITConfig(CAN2,CAN_IT_FMP0, ENABLE);   /* 挂号中断, 进入中断后读fifo的报文函数释放报文清中断标志 */
	
}

/*******************************************************************************
can1一共可以设置14个过滤器组.can1的过滤器号从0开始到13结束。can2从13开始到27结束
*******************************************************************************/
void  Filter_List(void)
{
	unsigned int temp_id = 0;

	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/******can1第0组过滤器设置*******/
	temp_id = 0x18400000;
	CAN_FilterInitStructure.CAN_FilterNumber = 0;     ///* 过滤器组 */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//CAN_FilterMode_IdList;//CAN_FilterMode_IdMask;  /* 屏敝模式 */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; ///* 32位 */
	CAN_FilterInitStructure.CAN_FilterIdHigh = (temp_id<<3)>>16;//(id<<3)>>16;  
	CAN_FilterInitStructure.CAN_FilterIdLow = (temp_id<<3)|CAN_ID_EXT|CAN_RTR_DATA;//扩展帧
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffff;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xffff;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;  ///* 能够通过该过滤器的报文存到fifo0中 */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);	
//	
	/******can2第1组过滤器设置*******/
	temp_id = 0x18412345;
	CAN_FilterInitStructure.CAN_FilterNumber = 14;     ///* 过滤器组 */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//CAN_FilterMode_IdList;//CAN_FilterMode_IdMask;  /* 屏敝模式 */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; ///* 32位 */
	CAN_FilterInitStructure.CAN_FilterIdHigh = (temp_id<<3)>>16;//(id<<3)>>16;  
	CAN_FilterInitStructure.CAN_FilterIdLow = (temp_id<<3)|CAN_ID_EXT|CAN_RTR_DATA;//扩展帧
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xffff;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xffff;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;  ///* 能够通过该过滤器的报文存到fifo0中 */
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
		
}

void Can1_WriteData(unsigned int ID, unsigned char *txbuf)
{		
	unsigned char i;
	CanTxMsg TxMessage;

	TxMessage.ExtId = ID;
	TxMessage.IDE = CAN_ID_EXT;
	TxMessage.RTR = CAN_RTR_DATA; /* 设置为数据帧 */
	TxMessage.DLC = 8;            /* 数据长度, can报文规定最大的数据长度为8字节 */

	for(i = 0;i < 8; i ++)
	{
		CAN1_DATA[i] = txbuf[i];
		TxMessage.Data[i] = CAN1_DATA[i];//can_send_data[i];
	}
	CAN_Transmit(CAN1,&TxMessage);  /* 返回这个信息请求发送的邮箱号0,1,2或没有邮箱申请发送no_box */	
}


//CAN2中断程序
int CAN2_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage; 
	unsigned char i;
	int j=0;

	CAN_Receive(CAN2,CAN_FIFO0, &RxMessage);  /* 此函数包含释放提出报文了的,在非必要时,不需要自己释放 */
	//CAN_ID = RxMessage.ExtId;
	for(i = 0;i < 8; i ++)
	{
		CAN1_DATA[i] = RxMessage.Data[i];
	}
	CAN_ClearITPendingBit(CAN2,CAN_IT_FMP0);  /* 清除挂起中断 */
	
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
