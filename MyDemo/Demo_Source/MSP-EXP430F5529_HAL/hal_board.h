/**********************************************************************//**
    Filename: hal_board.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_BOARD_H
#define HAL_BOARD_H

/* MSP430F5529: LED_1 is P1.0, LED_2 is P4.7  */
#define LED_PORT1_DIR     P1DIR
#define LED_PORT1_OUT     P1OUT
#define LED_PORT4_DIR     P4DIR
#define LED_PORT4_OUT     P4OUT
#define LED_1             BIT0
#define LED_2             BIT7

//  ACLK outputs on P1.0(led on launch pad) , SMCLK on P2.2, MCLK on P7.7(pin not available)
#define ACLK_PORT_DIR     P1DIR
#define ACLK_PORT_OUT     P1OUT
#define ACLK_PORT_SEL     P1SEL
#define SMCLK_PORT_DIR    P2DIR
#define SMCLK_PORT_OUT    P2OUT
#define SMCLK_PORT_SEL    P2SEL

/*----------------------------------------------------------------
 *                  Function Prototypes
 *----------------------------------------------------------------
 */
static void halBoardGetSystemClockSettings(unsigned char systemClockSpeed, 
                                           unsigned char *setDcoRange,
                                           unsigned char *setVCore,
                                           unsigned int  *setMultiplier);

extern void halBoardOutputSystemClock(void);
extern void halBoardStopOutputSystemClock(void);
extern void halBoardInit(void);
void hal430SetSystemClock(unsigned long req_clock_rate, unsigned long ref_clock_rate);

#endif /* HAL_BOARD_H */
