/*******************************************************************************
    Filename: hal_buttons.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_BUTTONS_H
#define HAL_BUTTONS_H

//  use 5529 S1 and S2 button only
//  S1: P2.1, S2: P1.1
#define BUTTON_S1_DIR   P2DIR
#define BUTTON_S1_SEL   P2SEL
#define BUTTON_S1_OUT   P2OUT
#define BUTTON_S1_REN   P2REN
#define BUTTON_S1_IE    P2IE
#define BUTTON_S1_IES   P2IES
#define BUTTON_S1_IFG   P2IFG
#define BUTTON_S1_IN    P2IN

#define BUTTON_S2_DIR   P1DIR
#define BUTTON_S2_SEL   P1SEL
#define BUTTON_S2_OUT   P1OUT
#define BUTTON_S2_REN   P1REN
#define BUTTON_S2_IE    P1IE
#define BUTTON_S2_IES   P1IES
#define BUTTON_S2_IFG   P1IFG
#define BUTTON_S2_IN    P1IN

#define BUTTON_S1         BIT1
#define BUTTON_S2         BIT1

extern volatile unsigned char buttonsPressed;

/*-------------------------------------------------------------
 *                  Function Prototypes 
 * ------------------------------------------------------------*/ 
extern void halButtonsInit(void);
extern unsigned char halButtonsPressed(void);
extern void halButtonsInterruptEnable(void);
extern void halButtonsInterruptDisable(void);
extern void halButtonsShutDown(void);

#endif /* HAL_BUTTONS_H */
