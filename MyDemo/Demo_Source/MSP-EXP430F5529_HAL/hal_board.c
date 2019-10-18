/**
 * @file  hal_board.c
 *
 * Copyright 2010 Texas Instruments, Inc.
******************************************************************************/
#include "msp430.h"
#include "hal_MSP-EXP430F5529.h"

/**********************************************************************//**
 * @brief  Initializes ACLK, SMCLK outputs on P1.0, and P2.2,           *
 *          , respectively. MCLK P7.7 is not available on launch pad
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void halBoardOutputSystemClock(void) //outputs clock to testpoints
{
    /*
    *    Led1 and ACLK both use P1.0, we use P1.0 for Led1
    */
  /*
  ACLK_PORT_DIR |= 0x01;
  ACLK_PORT_SEL |= 0x01;
  */

  SMCLK_PORT_DIR |= 0x04;
  SMCLK_PORT_SEL |= 0x04;
}

/**********************************************************************//**
 * @brief  Stops the output of ACLK, MCLK, SMCLK on P11.0, P11.1, and P11.2.
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void halBoardStopOutputSystemClock(void)
{

    /*
  ACLK_PORT_OUT &= ~0x01;
  ACLK_PORT_DIR |= 0x01;
  ACLK_PORT_SEL &= ~0x01;
    */
  SMCLK_PORT_OUT &= ~0x04;
  SMCLK_PORT_DIR |= 0x04;
  SMCLK_PORT_SEL &= ~0x04;

}

/**********************************************************************//**
 * @brief  Initializes all GPIO configurations.
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void halBoardInit(void)
{
  //Tie unused ports
  PAOUT  = 0;
  PADIR  = 0xFFFF;
  PASEL  = 0;
  PBOUT  = 0;
  PBDIR  = 0xFFFF;
  PBSEL  = 0;
  PCOUT  = 0;
  PCDIR  = 0xFFFF;
  PCSEL  = 0;
  PDOUT  = 0;
  PDDIR  = 0xFFFF;
  PDSEL  = 0x0003;

  PJOUT  = 0;
  PJDIR  = 0xFF;

  // Configure for LED_1 and LED_2
  LED_PORT1_DIR |= LED_1;
  LED_PORT4_DIR |= LED_2;
}

/**********************************************************************//**
 * @brief  Set function for MCLK frequency.
 *
 *
 * @return none
 *************************************************************************/
void hal430SetSystemClock(unsigned long req_clock_rate, unsigned long ref_clock_rate)
{
  /* Convert a Hz value to a KHz value, as required
   *  by the Init_FLL_Settle() function. */
  unsigned long ulCPU_Clock_KHz = req_clock_rate / 1000UL;

  //Make sure we aren't overclocking
  if(ulCPU_Clock_KHz > 25000L)
  {
    ulCPU_Clock_KHz = 25000L;
  }

  //Set VCore to a level sufficient for the requested clock speed.
  if(ulCPU_Clock_KHz <= 8000L)
  {
    SetVCore(PMMCOREV_0);
  }
  else if(ulCPU_Clock_KHz <= 12000L)
  {
    SetVCore(PMMCOREV_1);
  }
  else if(ulCPU_Clock_KHz <= 20000L)
  {
    SetVCore(PMMCOREV_2);
  }
  else
  {
    SetVCore(PMMCOREV_3);
  }

  //Set the DCO
  Init_FLL_Settle( ( unsigned short )ulCPU_Clock_KHz, req_clock_rate / ref_clock_rate );
}
