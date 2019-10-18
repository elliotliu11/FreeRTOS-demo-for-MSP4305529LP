/**
 * @file  hal_lcd.c
 *
 * Module to control the graphical Nokia 5110 LCD display.
 *              While the display is 84 pixels wide by 48 pixels high,
 *              this module reduces the usable area to 84x48pixels due
 *              to memory limitations (512B) of the MSP430G2553.
 * Author(s):   Elliot Liu(modified)
***************************************************************************/

#include "msp430.h"
#include "hal_MSP-EXP430F5529.h"
#include "hal_lcd_fonts.h"

//	a copy of LCD memory
//unsigned char displayData[LCD_NUM_BANK][LCD_NUM_COLUMNS];

/**********************************************************************//**
 * @brief  Sends wirte command or data to the LCD
 *
 * @param  Data[] Data array for transmission
 *
 * @return none
 *************************************************************************/
void halLcdSendCommand(char byte, char isData)
{
    // wait for completion just in case
    while(UCB1STAT & UCBUSY);

    // set data/command select pin (see data sheet page 11)
    if (isData)
        {
        P4OUT |= DC;
        }
    else
        {
        P4OUT &= ~DC;
        }

    // enable active low slave chip enable (CE)
    P4OUT &= ~CE;

    // transmit data byte
    UCB1TXBUF = byte;
}


/**********************************************************************//**
 * @brief  Initializes the USCI module in SPI mode, LCD device for communication.
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void halLcdInit(void)
{
  // place UCB1 in software reset
	UCB1CTL1 = UCSWRST;

	// configure UCB1 in SPI mode, 3-pin, 8-bit, MSB first, SPI master, SMCLK clock source, bit rate divisor = 1
	// Clock phase & polarity must be set correctly.
	// See section 35.3.6 of MSP family users guide and page 12 of Nokia display datasheet.
	UCB1CTL0 = UCSYNC | UCMSB | UCMST;	//	3pin, 8 bit by default, using default clock phase & polarity
	UCB1CTL1 |= UCSSEL__SMCLK;	//	use SMCLK
	UCB1BR0 = 1;	//	bit rate divisor = 1
	UCB1BR1 = 0;
	
	// clear software reset
	UCB1CTL1 &= ~UCSWRST;

	// set DC and CE pins as output and inactive (PxDIR, PxOUT)
	P4DIR |= DC | CE;
	P4OUT |= DC | CE;

	// select UCB1 SPI interface to control SIMO and CLK signals (PxSEL)
	P4SEL |= SIMO | CLK;
	UCB1IE |= UCTXIE;	//	add int

	__enable_interrupt();//	add int

	// send initialization sequence to LCD module
	halLcdSendCommand(LCD_EXTENDED_INSTR, CMD);
	halLcdSendCommand(LCD_SET_VOP, CMD);
	halLcdSendCommand(LCD_SET_TEMP, CMD);
	halLcdSendCommand(LCD_SET_BIAS, CMD);
	halLcdSendCommand(LCD_REG_INSTR, CMD);
	halLcdSendCommand(LCD_NORM_DISP, CMD);

}

/**********************************************************************//**
 * @brief  Clears entire LCD CGRAM as well as LCD_MEM.
 *
 * @param  none
 *
 * @return none
 *************************************************************************/
void halLcdClearScreen(void)
{
  unsigned char x, bank; // variables to track location in RAM

	// for each bank (group of 8 rows)
	for (bank = 0; bank < LCD_NUM_BANK; bank++) {

		// set the RAM address to start in the first column of the bank
		halLcdSendCommand(LCD_SET_X | 0, CMD);
		halLcdSendCommand(LCD_SET_Y | bank, CMD);

		// for each column
		for (x = 0; x < LCD_NUM_COLUMNS; x++) {
			halLcdSendCommand(0, DATA);         // clear pixels on display
		}
	}
}

/**********************************************************************//**
 * @brief  Displays a string on the LCD on the specified line.
 *
 * @param  String[]  The string to be displayed on LCD.
 *
 * @param  Line      The line on the LCD on which to print the string.
 *
 *
 * @return none
 *************************************************************************/
void halLcdPrintLine(char string[], unsigned char line)
{
    unsigned char count, i = 0;
    unsigned int font_idx;

    //  set address to the new line
    halLcdSendCommand(LCD_SET_X, CMD);
    halLcdSendCommand(LCD_SET_Y | line, CMD);

    while(string[i] != 0) {
        //  ensure font is available
        if ((string[i] < 0x20) || (string[i] >= 0x7F)){
            font_idx = 0;
        }
        else {
            font_idx = string[i] - 0x20;
        }

        //  copy font to memory
		font_idx *= 5;

        //  write font to lcd
        for (count = LCD_FONT_WIDTH; count > 0; count--) {
            halLcdSendCommand(fonts[font_idx++], DATA);
        }

        i++;
        //  too many chars, just cut off
        if (i >= LCD_FONT_NUM_PER_LINE) {
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////
// USCIB1_ISR - tx ISR, ignoring other interrupt
// Arguments: void
// Return Value: none
///////////////////////////////////////////////////////////////////////
#pragma vector=USCI_B1_VECTOR
__interrupt void USCIB1_ISR(void)
{
    switch(__even_in_range(UCB1IV, UCTXIFG))
	{
	case 4:	//	tx done
		// disable active low slave chip enable
		P4OUT |= CE;
	case 2:	//	rx done
	default:
		;//	do nothing
	}
}


