SET PATH=D:\software\keil\ARM\BIN40\;C:\Program Files\Dell\DW WLAN Card;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;c:\Program Files\WIDCOMM\Bluetooth Software\;c:\Program Files\WIDCOMM\Bluetooth Software\syswow64;C:\Program Files (x86)\Common Files\Roxio Shared\OEM\DLLShared\;C:\Program Files (x86)\Common Files\Roxio Shared\OEM\DLLShared\;C:\Program Files (x86)\Common Files\Roxio Shared\OEM\12.0\DLLShared\;C:\Program Files (x86)\Roxio\OEM\AudioCore\;C:\Program Files (x86)\Common Files\Thunder Network\KanKan\Codecs;D:\Matlab\bin\win32;D:\software\Doxygen\bin;
SET ARMCC41INC=D:\software\keil\ARM\RV31\INC
SET ARMCC41LIB=D:\software\keil\ARM\RV31\LIB
SET CPU_TYPE=STM32F103ZE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\main.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_it.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\rcc_gpio.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\misc.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_adc.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_gpio.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_rcc.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_tim.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\stm32f10x_flash.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\core_cm3.__i"
"D:\software\keil\ARM\BIN40\ArmCC" --Via ".\obj\system_stm32f10x.__i"
"D:\software\keil\ARM\BIN40\ArmAsm" --Via ".\obj\startup_stm32f10x_hd._ia"
"D:\software\keil\ARM\BIN40\ArmLink" --Via ".\Obj\waterCooling.lnp"
D:\software\keil\ARM\BIN40\fromelf.exe ".\Obj\waterCooling.axf" --i32combined --output ".\Obj\waterCooling.hex"
