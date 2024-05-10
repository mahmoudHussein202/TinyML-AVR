#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_
#include "../Interfaces/sw_interface.h"
/*************************************************
**************** Memory Mapping******************
*************************************************/
#define MCUCSR *((volatile unsigned char*)0x54)
#define WDTCR *((volatile unsigned char*)0x41)
/*************************************************
******************** APIS ***********************
*************************************************/
//[1] Flags
#define WD_reset_flag_read  read_pin(MCUCSR,3)
//[2] prescalar
/*-------------
WDP2     WDP1       WDP0          Number of WDT           Typical Time-out    Typical Time-out 
                                 Oscillator Cycles        at VCC = 5.0V       at VCC = 3.0V

0         0           0            16K (16,384)             17.1 ms             16.3 ms
0         0           1            32K (32,768)             34.3 ms             32.5 ms
0         1           0            64K (65,536)             68.5 ms             65 ms
0         1           1            128K (131,072)           0.14 s              0.13 s
1         0           0            256K (262,144)           0.27 s              0.26 s
1         0           1            512K (524,288)           0.55 s              0.52 s
1         1           0            1,024K (1,048,576)       1.1 s               1.0 s
1         1           1            2,048K (2,097,152)       2.2 s               2.1 s
*/
#define WD_TimeOut_17_ms            0b000
#define WD_TimeOut_34_ms            0b001
#define WD_TimeOut_68_ms            0b010
#define WD_TimeOut_140_ms           0b011
#define WD_TimeOut_270_ms           0b100
#define WD_TimeOut_550_ms           0b101
#define WD_TimeOut_1_s              0b110
#define WD_TimeOut_2_s              0b111
#define WD_set_TimeOut(time_out)    set_multiple_pins(WDTCR,0,time_out)
//[3]WatchDog Enable
#define WD_Enable()                   set_pin(WDTCR,3)
#define WD_Clear()                    {\
                                        set_pin(WDTCR,3);\
                                        set_pin(WDTCR,4);\
                                        clear_pin(WDTCR,3);\
                                      }                    
#endif