#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "spi.h"

void SPI_Configuration(){
	SPI_InitTypeDef	SPI_InitStructure;
	
	//ȫ˫��
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//SPI3������
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	//8��bit ÿ֡
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	//ʱ�ӿ��б���Ϊ��
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	//��һ��ʱ���ؿ�ʼ���ݲ���
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	//NSS�ź������(ʹ��SSIλ)����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	//SPI������Ԥ��ƵΪ8
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	//���ݴ����MSB��ʼ
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	//CRC����ʽ
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	//д�����ò�ʹ��
	SPI_Init(SPI3, &SPI_InitStructure);
	SPI_Cmd(SPI3, ENABLE);
}

/* @brief  ����һ������TxData��ͬʱ��������(MISO�յ��ģ��൱��RxData)������Ϊ����ֵ����
 * @param  ������TxData, ������uint_8, Ҳ����unsigned char
 * ��ӻ������ݺ�SCK�ᴥ���ӻ������ݷ��ͣ�����ͬʱ�շ���ȫ˫��ģʽ
*/
uint8_t	SPI_ReadWriteByte(uint8_t TxData){
	uint8_t retry=0;

	/* Loop while DR register in not emplty */
	//�ȴ���ֱ��SPI3��Tx bufferΪ�գ�������TXE: Transmit buffer empty flag
	//����һ������û����͵��ţ����ͳɹ����˳�ѭ��
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){		
		retry++;
		if(retry > 200){
			//�ط��ȴ�����200�����ڣ�û�з��ͳɹ�������0
			return 0;
		}
	}
	/* Send byte through the SPI1 peripheral */
	//ͨ��SPI3����TxData
	SPI_I2S_SendData(SPI3, TxData);
	retry=0;

	/* Wait to receive a byte */
	//�ȵ� SPI3���������ݣ�����RXNE: Receive buffer not empty flag
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){
		retry++;
		if(retry>200){
			return 0;
		}
	}  						    	
	/* Return the byte read from the SPI bus */
	//�����յ�������
	return SPI_I2S_ReceiveData(SPI3);        
}
