# FreeRTOS-demo-for-MSP4305529LP
FreeRTOS demo for MSP4305529LP. Use Nokia 5110 LCD
Source code modified from MSP430FR5969 FreeRTOS demo.

Here is the major change list:

1. Remove peripherals that do not exist on MSP430F5529LP. For example: Port E and Port 11.
2. Map peripherals' pin assignments to correct pins. Ex: S1 uses  P2.1, S2 uses P1.1, LED1 uses P1.0, LED2 uses P4.7. 
3. Only SMCLK and ACLK are available on MSP430F5529. However, ACLK and LED1 both use P1.0, we only have SMCLK available for demo
4. We don't need to adjust clock, so remove calling hal430SetSystemClock and LFXT(high mode is not supported anyways!)
5. Add my own 8x5 fonts and modify lcd module to work with Nokia 5110 LCD . Use USCI B1 (Port 4) instead of using Port 8 and Port9
6. Since MSP430F5529 only has 8KB RAM and the program will not fit into it, I removed three demo tasks: vAltStartComTestTasks, vRegTest1Task, and vRegTest2Task. It is up to you which task you want to run

You can find my blog here: https://elliotsmicro.blogspot.com/2019/10/freertos-port-to-msp430f5529-with-nokia.html
