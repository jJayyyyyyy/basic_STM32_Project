/* 基于nRF24L01与STM32的无线通信
 * 版本 v0.3，可以通过输出PWM给L298驱动的INx，然后输出OUTy驱动控制减速电机，进而遥控小车
 * by 楼基颉
 * MDK v4.22打开会乱码，需要npp之类的文本编辑器打开
 * 
 * This is a nRF24L01-and-STM32-based wireless communication project.
 * Version 0.3. In this version you can wirelessly control your little toy car by using PWM.
 * You may need the driver-L298 to drive the gear-motors on your toy car.
 * by Steve Lou.
 * better to open this docs using npp/gedit/vi or some editor with UTF-8. Or there may be gibberish characters :(
*/


0. STM32f107VCT6
	晶振25M
	通过分频器与锁相环，使系统时钟为72M		
	注：	STM32F10X_CL代表的是使用了
			STM32互联系列微处理器(芯片选型 STM32F10x Connectivity Line Flash, 256k)
			也就是STM32F105和STM32F107系列处理器


