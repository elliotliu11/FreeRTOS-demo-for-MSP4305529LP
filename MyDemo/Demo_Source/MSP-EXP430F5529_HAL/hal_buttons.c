/** 
 * @file  hal_buttons.c
 * 
 * Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#include "msp430.h"
#include "hal_MSP-EXP430F5529.h"

/*  S1 is used in button polling task, S2 is used in ISR */
/**********************************************************************//**
 * @brief  Initializes the GPIO ports to act as buttons. Use S1 & S2 only
 * 
 * @param  none
 * 
 * @return none
 *************************************************************************/   
void halButtonsInit(void)
{  
  BUTTON_S1_OUT |= BUTTON_S1;
  BUTTON_S1_DIR &= ~BUTTON_S1;
  BUTTON_S1_REN |= BUTTON_S1;
  BUTTON_S1_SEL &= ~BUTTON_S1;

  BUTTON_S2_OUT |= BUTTON_S1;
  BUTTON_S2_DIR &= ~BUTTON_S1;
  BUTTON_S2_REN |= BUTTON_S1;
  BUTTON_S2_SEL &= ~BUTTON_S1;
}

/**********************************************************************//**
 * @brief  Returns LOW for the buttons pressed.
 * 
 * @param  none
 * 
 * @return The buttons that have been pressed, identified by a bit = 0. 
 *************************************************************************/
unsigned char halButtonsPressed(void)
{
  unsigned char value;
  value = BUTTON_S1_IN;
  return (0xFF - value);                    //Low==ButtonPressed
}

/**********************************************************************//**
 * @brief  Enables button interrupt(s) with low to high transitions.
 *          Only S2 is used in ISR
 * 
 * @param  none
 * 
 * @return none
 *************************************************************************/
void halButtonsInterruptEnable(void)
{
  BUTTON_S2_IES &= ~BUTTON_S2;
  BUTTON_S2_IFG &= ~BUTTON_S2;
  BUTTON_S2_IE |= BUTTON_S2;
}

/**********************************************************************//**
 * @brief  Disables button interrupts for S2
 * 
 * @param  none
 * 
 * @return none
 *************************************************************************/
void halButtonsInterruptDisable(void)
{
  BUTTON_S2_IE &= ~BUTTON_S2;
}

/**********************************************************************//**
 * @brief  Clears the button GPIO settings, disables the buttons. 
 * 
 * @param  none
 *************************************************************************/
void halButtonsShutDown(void)
{
  //All output, outputting 0s
  BUTTON_S1_OUT &= ~(BUTTON_S1);
  BUTTON_S1_DIR |= BUTTON_S1;

  BUTTON_S2_OUT &= ~(BUTTON_S2);
  BUTTON_S2_DIR |= BUTTON_S2;
}
