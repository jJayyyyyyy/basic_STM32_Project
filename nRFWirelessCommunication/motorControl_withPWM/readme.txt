/*
 * This is the v0.3 of nRFWirelessCommunication Project.
 * In <motorControl_withPWM> you can use your STM32 and nRF24L01 to control your little toy car using 
 * 	gear-motor(some kind of DC-motor).
 * Use PWM to control its direction and speed.
*/


/* 基于nRF24L01与STM32的无线通信
 * 版本 v0.3
 * by 楼基颉
 * readme使用UTF-8，MDK v4.22因为使用ANSI，在工程中打开readme会乱码，需要npp之类的文本编辑器打开
*/

0. STM32f107VCT6
	晶振25M
	通过分频器与锁相环，使系统时钟为72M		
	注：	STM32F10X_CL代表的是使用了
			STM32互联系列微处理器(芯片选型 STM32F10x Connectivity Line Flash, 256k)
			也就是STM32F105和STM32F107系列处理器

1. 修改stm32f10x_it.c中
		Increment_High / Increment_Low 的数据类型
	改成	__IO uint16_t 

2. 增加文件pwm_control.c / .h

3. 为了两路PWM的两路控制，可能还需要增加个2个Increment变量

4. 不要过早优化，先跑起来再说

	最麻烦(手工)连线的地方，比如这个小电机的接线柱，就以最简单的方式连 < 次麻烦的地方，驱动接线柱，虽然可能难看一点，但是总比掰断小电机的接线柱要好 < 软件进行修改，底层的，封装好接口就好了，里面的实现不要暴露出来
	
5. 遥控



//TODO:
0.		markdowng格式的readme

1. 	
		·控制逻辑+方便用户操作的接口
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

