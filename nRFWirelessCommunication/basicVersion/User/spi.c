#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "spi.h"

void SPI_Configuration(){
	SPI_InitTypeDef	SPI_InitStructure;
	
	//全双工
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//SPI3是主机
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	//8个bit 每帧
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	//时钟空闲保持为低
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	//第一个时钟沿开始数据采样
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	//NSS信号由软件(使用SSI位)管理
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	//SPI波特率预分频为8
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	//数据传输从MSB开始
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	//CRC多项式
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	//写入配置并使能
	SPI_Init(SPI3, &SPI_InitStructure);
	SPI_Cmd(SPI3, ENABLE);
}

/* @brief  发送一个数据TxData，同时接收数据(MISO收到的，相当于RxData)，并作为返回值返回
 * @param  参数是TxData, 类型是uint_8, 也就是unsigned char
 * 向从机发数据后，SCK会触发从机的数据发送，主机同时收发，全双工模式
*/
uint8_t	SPI_ReadWriteByte(uint8_t TxData){
	uint8_t retry=0;

	/* Loop while DR register in not emplty */
	//等待，直到SPI3的Tx buffer为空，参数是TXE: Transmit buffer empty flag
	//若上一个包还没发完就等着，发送成功后退出循环
	while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){		
		retry++;
		if(retry > 200){
			//重发等待超过200个周期，没有发送成功，返回0
			return 0;
		}
	}
	/* Send byte through the SPI1 peripheral */
	//通过SPI3发送TxData
	SPI_I2S_SendData(SPI3, TxData);
	retry=0;

	/* Wait to receive a byte */
	//等到 SPI3接收完数据，参数RXNE: Receive buffer not empty flag
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET){
		retry++;
		if(retry>200){
			return 0;
		}
	}  						    	
	/* Return the byte read from the SPI bus */
	//返回收到的数据
	return SPI_I2S_ReceiveData(SPI3);        
}
