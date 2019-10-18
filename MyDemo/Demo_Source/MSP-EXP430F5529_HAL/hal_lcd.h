/*******************************************************************************
    Filename: hal_lcd.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_LCD_H
#define HAL_LCD_H

#ifndef MIN
#define MIN(n,m)   (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n,m)   (((n) < (m)) ? (m) : (n))
#endif

#ifndef ABS
#define ABS(n)     (((n) < 0) ? -(n) : (n))
#endif

// mapping of the 5110 LCD signals to the MSP430 ports.
#define	CE   BIT0
#define SIMO BIT1
#define DC   BIT2
#define CLK  BIT3

// constants used to control "isData" argument of the lcdWrite function
#define CMD  0
#define DATA 1

// LCD instructions
#define LCD_EXTENDED_INSTR 0x21 // enable extended instruction set
#define LCD_SET_VOP        0xBF // set Vop (controls contrast)
#define LCD_SET_TEMP       0x06 // set temperature coefficient 2
#define LCD_SET_BIAS       0x13 // set bias mode 1:48
#define LCD_REG_INSTR      0x20 // enable regular commands
#define LCD_NORM_DISP      0x0C // display control - normal
#define LCD_SET_Y          0x40 // set Y address of RAM
#define LCD_SET_X          0x80 // set X address of RAM

#define LCD_FONT_WIDTH      5   //  5 bytes per font
#define LCD_FONT_NUM_PER_LINE   (LCD_NUM_COLUMNS/LCD_FONT_WIDTH)

#define LCD_NUM_COLUMNS 84	// number of columns on display
#define LCD_NUM_ROWS    48  // number of rows on display
#define LCD_NUM_BANK    6   // LCD_NUM_ROWS / ROWS_PER_BANK
#define ROWS_PER_BANK   8 // each bank represents 8 rows
/*-------------------------------------------------------------
 *                  Function Prototypes 
 * ------------------------------------------------------------*/ 
extern void halLcdInit(void);                   

extern void halLcdSendCommand(char byte, char isData);
//Clear LCD Screen  
extern void halLcdClearScreen(void);                    

//Invert black to white and vice versa
extern void halLcdReverse(void);

//Print String of Length starting at (x,y)
extern void halLcdPrintLine(char String[], unsigned char Line);  

#endif /* HAL_LCD_H */
