/* 基于nRF24L01与STM32的无线通信
 * 版本 v0.2
 * by 楼基颉
 * MDK v4.22打开会乱码，需要npp之类的文本编辑器打开
*/

0. STM32f107VCT6
	晶振25M
	通过分频器与锁相环，使系统时钟为72M		
	注：	STM32F10X_CL代表的是使用了
			STM32互联系列微处理器(芯片选型 STM32F10x Connectivity Line Flash, 256k)
			也就是STM32F105和STM32F107系列处理器

1. SPI3的实现(配置及重映射)
	(1)
			· nss是从器件使能信号，由主器件控制,有的IC会标注为CS(Chip select)
			
			· 要实现主从数据交换，在时钟信号前，主机 从机都必须先将数据写入数据寄存器，并且从机必须在主机前写入，然后由主机的SCLK时钟驱动发送。 
			这样的全双工、同步传输完全依赖于 主机控制的时钟线SCLK，而且SCLK上只有数据传输的时候才有时钟信号。主机向从机发送数据不会有问题，但是如果从机主动向主机发送数据呢？ 
			从机要发送数据，必须要有SCLK的时钟，所以只能主机发送一个DUMMY（哑巴）字节，产生时钟，来实现和从机的数据交换。 从设备只能被动发送数据，无法主动发送数据。
			
			因此(以SPI1与SPI2通信为例，注意上机测试的时候必须将SPI1与SPI2的相关管脚用导线连起来)
			//必须先将从设备数据写入数据寄存器，等待时钟同步
			SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
			//主设备将数据写入数据寄存器，触发同步时钟，让主从数据寄存器由此时钟发送
			SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx]);
			
			在SPI1(主机) 开始发送的时候，有了同步时钟，此时SPI2一直在等待状态，因此这个同步时钟也触发了SPI2的数据发送
	
	
	(2)重映射函数原型：
			void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState)
			STM32f107vct6不是FPGA，重映射是固定的，无法自行指定，要查表，看看映射到了哪

			比如SPI3，查询datasheet(好好利用ctrl+f)后可知
				Alternate function SPI3_REMAP = 0 SPI3_REMAP = 1
				SPI3_NSS 			PA15 					PA4
				SPI3_SCK 				PB3 						PC10
				SPI3_MISO 			PB4 						PC11
				SPI3_MOSI			PB5 						PC12
	
	(3)非常重要！remap一定要在时钟使能之后配置，否则无效

			重映射步骤：
			· (1)使能被重新映射到的I/O端口时钟
			　　RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			· (2)使能被重新映射的外设时钟
			　　RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
			· (3)使能AFIO功能的时钟
			　　RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
			· (4)进行重映射
			　　GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

			注：
				· (1)(2)(3)顺序可换，
				· 或者，在APB2总线上的设备，用 或( | ) 一起进行时钟使能，
			　　   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
				  但一定要在(4)之前。否则remap无法配置成功　　

		(4).更多参见spi.c及其注释
		
		
2.	nRF的SPI接口速率: 0~8Mbps

3.	无线通信实现

	nRF24L01
			模块配置
			通信协议实现
				SPI
				基于SPI，写入配置、指令、数据到nRF，使其正常工作的格式
			数据收发，双向调试
			使用while(1)
			...
			





//TODO：
0.		markdowng格式的readme
					
1. 	
		· 控制逻辑+方便用户操作的接口
		· 控制小车
		· PC上位机
				C# + VS
		· 自动避障(遇到障碍物停下)，回传遇到障碍物的信息
		· 传图
		
		
		接收板的PWM
		电池给298供电，298可以输出5V，给单片机供电(无线模块和红外模块由单片机供电
		298的OUT给电机转动供电以及提供逻辑
		
		做个表格
		L298N
				ENA一直使能
				IN1 IN2 提供前进、停、后退的逻辑以及速度
				同侧轮子行为相同
		
		//整理思路，待修改完善
		void forward(){
			//left
			IN1=1;占空比=40;
			IN2=0;

			//right
			IN3=1;占空比=40;
			IN4=0;
		}
		
		void backward(){	
			//left
			IN1=0;
			IN2=1;占空比=20;	//慢慢退

			//right
			IN3=0;
			IN4=1;占空比=20;
		}
		
		void leftforward(){
			//left
			IN1=0;
			IN2=0;

			//right
			IN3=1;占空比=40;
			IN4=0;
		}
		
		void rightforward(){
			//left
			IN1=1;占空比=40;
			IN2=0;

			//right
			IN3=0;
			IN4=0;
		}
				
2.
		USART串口
			USART:(Universal Synchronous/Asynchronous Receiver/Transmitter) 通用同步/异步串行接收/发送器
		
			串口使用只需要开始串口时钟，设置相应的I/O口模式，
			配置波特率、数据位长度、奇偶校验位等信息就可以使用了。
		
		void leftbackward(){
		}
		
		void rightbackward(){
		}

