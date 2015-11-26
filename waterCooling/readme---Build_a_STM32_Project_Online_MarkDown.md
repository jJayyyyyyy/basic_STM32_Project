* [STM32标准库版本为V3.5.0]
* [Keil uVision4, 版本为MDK-ARM Standard Version: 4.22]

#一、新建一个基于MDK的STM32工程  

### 1.新建4个文件夹；Lib MDK User Utilities

### 2.拷贝\stm32标准库\Libraries\的<CMSIS>和<STM32F10x_StdPeriph_Driver>两个文件夹，粘贴到<\Lib>文件夹

### 3.拷贝 \stm32标准库\Project\STM32F10x_StdPeriph_Examples\ADC\3ADCs_DMA  
###　中的所有文件，粘贴到<\User>文件夹  
* 注1：后面根据实际需要修改这些.c .h  
* 注2：system_stm32f10x.c文件定义了系统时钟等参数并完成微控制器的初始化，标准外设库中已经有了，这里可以不拷贝  
　　 (路径：\Lib\CMSIS\CM3\DeviceSupport\ST\STM32F10x)。

### 4.启动keil4，新建工程，保存位置\MDK  
* 由于芯片型号为STM32F103ZET6，因此选择芯片STMicroelectronics-->STM32F103ZE。  
* 接下来的弹出框，选No，不要拷贝启动代码并添加到工程，库函数已经有了，我们来手动添加。


### 5.右键Target1-->Manage Components，在Groups处双击添加四个组：
* `User， Lib， CMSIS， StartUp`  

##### 接下来添加Files  
* User：添加`\User`文件夹下所有文件，包括`.c` 和 `.h`<br/><br/>  
* Lib：添加`\Lib\STM32F10x_StdPeriph_Driver\src`文件夹下所有文件，只有`.c`文件  
（这个组的文件可以根据程序功能和需求来进行删减）<br/><br/>  
* CMSIS：添加`\LIB\CMSIS\CM3\CoreSupport`文件夹下的`core_cm3.c`文件和`\LIB\CMSIS\CM3\DeviceSupport\ST\STM32F10x`文件夹下的`system_stm32f10x.c`文件。(参考第3点的注2)<br/><br/>  
* StartUp：添加`\LIB\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm`文件夹下的`startup_stm32f10x_hd.s`文件。此文件根据芯片的所属类型来选择，STM32F103ZE为大容量器件，所以选择hd结尾的启动文件。<br/>  
至此，已经将对应的文件全部加入工程中，点击OK保存。


### 6.参数设置  
* 右键`Target1`->`Options for Target ‘Target1’`  
* `Output`选项卡-> `Select Folder for Objects` -> `\MDK\Obj`。然后下方勾选`Create HEX File`。
* `Listing`选项卡-> `Select Folder for Listings` -> `\MDK\List`。
* `C/C++`选项卡->  
    * `Define` ->  
	`USE_STDPERIPH_DRIVER, STM32F10X_HD, USE_STM3210C_EVAL`<br/><br/>
	* `Include Paths` ->  
	`\User`  
	`\Lib\STM32F10x_StdPeriph_Driver\inc`  
    `\Lib\CMSIS\CM3\CoreSupport`  
	`\Lib\CMSIS\CM3\DeviceSupport\ST\STM32F10x`  
	`\Utilities\STM32_EVAL`  
	`\Utilities\STM32_EVAL\Common`  
	`\Utilities\STM32_EVAL\STM3210C_EVAL`  
	(添加头文件路径。要把当前工程目录中包含头文件的路径都include添加进去)
	
<br/>
### 7. 程序调试与下载设置(下载器根据实际选择)
* `Debug`选项卡->  
    * `Use Cortex-M/R J-Link/J-Trace`  
    * 点击 `Settings` -> `Flash Download`选项卡，选中`Reset and Run`，再`Add`芯片类型`STM32F10x High-density Flash, On-chip Flash, 512k`  
* `Utilities`选项卡 ->  
	* 同样选择`Cortex-M/R J-Link/J-Trace`  
<br/><br/>  

##### 基本配置完成，相比参考博客，可读性稍强，方便参阅
<br/><br/>  

##### （下面再加入初始化设置）

# 二、系统初始化

### 1. 函数定义，声明，调用，源文件的连接
* 以adc.c为例  
    * 在`main.c`中  
            #include "stm32f10x.h"  
            #include "adc.h"`  
    * 在`adc.c`中  
            #include "adc.h"  
    然后<实现> （可以先把空的函数放着，后面再来<定义>，把代码补充完整）  
            void func(void){  
            //TODO:  
            
            }  
    * 在`adc.h`中声明`func()`  
            void func(void);  

* 现在`main.c`中可以调用`func()`了  

    注：这种方法可以按照自己的需求来进行，另外一种方法就是，  
        #include <stm32f10x_lib.h>  
    这个 `stm32f10x_lib.h` 的路径是 `<\keil安装目录>\keil\ARM\INC\ST\STM32F10x`  
    对于 `adc`, `stm32f10x_lib.h`里面有这段代码  
        #ifdef _ADC  
        　　#include "stm32f10x_adc.h"  
        #endif /*_ADC */  
<br/><br/><br/><br/>

### 2.系统初始化函数  
* `main.c`中  
        void System_Init(void);

        void System_Init(void){
        //...do something to initialize the system
        
        }


### 3. 配置系统时钟  
* 新建 `rcc_gpio.c`，右键`User`把这个`.c`文件`add`进来  
* 新建 `rcc_gpio.h`  
* `rcc_gpio.c`中  
        #include "stm32f10x_rcc.h"  
        #include "rcc_gpio.h"  
        
        void RCC_Configuration(void){  
		//...详见rcc_gpio.c  
        }  
	
* `rcc_gpio.h`中  
        void RCC_Configuration(void);  

* `main.c`中  
       #include "rcc_gpio.h"  

* 现在`System_Init()` 中便可调用 `RCC_Configuration()`，来对系统时钟初始化。  
要用什么功能，就在`RCC_Configuration()`的定义中，使能相应总线和端口的时钟。


### 4.GPIO
* `rcc_gpio.c`中  
        void GPIO_Configuration(void){  
            //...详见rcc_gpio.c  
            //以配置LED为例，端口参考硬件手册  
        }  
	
* `rcc_gpio.h`中  
        void GPIO_Configuration(void);  
	
* 现在System_Init()中便可调用RCC_Configuration();来进行GPIO初始化<br/><br/>  
	
### 5. 下载程序，测试
由于手头刚好有`J-Link`，因此直接焊上10*2的排插当作`J-Link插座`进行下载与调试  
注：板上的ST-Link还未测试

### 6. 验证
一般来说，新建一个工程或者一个小程序，都是从hello world开始。  
但是无论是8051单片机还是ARM、DSP、FPGA的学习，通常第一个程序的首选都是点亮一盏LED，因此对于玩单片机的人也有“一灯大师”的戏称。  
这里，对于STM32来说，GPIO的控制是最简单的，而且也最容易验证。  
下面就用LED灯来测试之前这些步骤是否有问题（工程创建，系统、参数配置，初始化，程序下载等方面）。

* `rcc_gpio.c`中  
        void RCC_Configuration(void){  
            //...配置  
            
            //开发板LED对应PE2 PE3 PE4 PE5，于是使能GPIOE的时钟  
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  
        }
        
        void GPIO_Configuration(void){  
            GPIO_InitTypeDef GPIO_InitStructure;  
            
            GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4;  
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//LED用PP,推挽输出  
            GPIO_Init(GPIOE, &GPIO_InitStructure);  
        }

* `rcc_gpio.h`中  
        #define LED1	GPIO_Pin_5  
        #define LED2	GPIO_Pin_4  
        #define LED3	GPIO_Pin_3  
        #define LED4	GPIO_Pin_2

* `main.c`详见文件代码

* 接上J-Link，显示可以下载。将工程编译并下载到ROM，下载未出现错误。按下开发板上的reset键，可以观察到LED1 LED2 LED3 LED4均开始闪烁，测试成功。


<br/><br/><br/>
##### 至此，从新建一个STM32工程，到系统配置及初始化，均已初步测试通过。在此基础上可以开始进一步的开发。


//TODO
main.c, readme.md文档注释

TIM
PWM




	
[参考1](http://www.cnblogs.com/emouse/archive/2012/03/01/2375146.html)  
[参考2](http://www.ichanging.org/)  

`[附注]`  
> stm32的使用和51单片机不同，单片机接上晶振接上电源 直接就可以操作io口，但是stm32的时钟是经过了倍频器放大频率的，然后再由锁相环输出稳定的时钟频率。  
这么做的带来了很多好处，虽然stm32的外部时钟只有8Mhz ，经过倍频器后就可以得到好几种的时钟频率给不同的外设提供不同的时钟频率。
所以stm32有很多总线，这些总线的频率是不同的。  
而且在使用前，总线是关闭的，使用外设前必须使能其对应的总线，以此降低STM32的功耗。  
<br/><br/><br/><br/>


Edit by [Steve](https://github.com/jJayyyyyyy)  
Online-MarkDown from [MaHua](http://mahua.jser.me)