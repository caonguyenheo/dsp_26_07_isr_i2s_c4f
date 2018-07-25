//#include <corazon.h>
#include <stdio.h>
//#include <std.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"
#include "lcdFontTable2.h"
#include "register_LCD.h"
#include "lcd.h"
#include "oled.h"
#include "evm5517.h"
#include "evm5517_i2cgpio.h"
#include "spi.h"

#define CMD     0x000
#define DATA    0x100
static Uint16 writeBuff[64];

void oledWrite( Uint16 type, Uint16 val)
{
	writeBuff[0] = val | type;  // Command Lock
	spi_cycle(writeBuff, 1);

	return;
}


void wait(Uint32 count)
{
	int i;
	
	for(i=0;i<count;i++)
	asm("	nop");
}

void  cmdWrite(Uint16 cmd, Uint16 cs_flag)
{ 
    oledWrite(cmd, CMD);
}      

void  dataWrite(Uint16 data, Uint16 cs_flag)
{
    oledWrite(data, DATA);
} 

void draw_font(Uint16 startc, Uint16 startl, Uint16 font,Uint16 Color)
{
    Uint16 cs_flag=0,  i, j,bit;
    unsigned char *pData, data;
    
    pData = lcdFontTable;

 
    for(i=0; i<8; i++)
    {
        data = *(pData + (font - ' ')*8  + i);         
        for(j=0; j<8; j++)
        {

			cmdWrite(0x15, cs_flag); 
			dataWrite(startc+j, cs_flag);
			dataWrite(startc+j, cs_flag);
			wait(10);
			cmdWrite(0x75, cs_flag); 
			dataWrite(startl+i, cs_flag);
			dataWrite(startl+i, cs_flag);
			wait(10);
			cmdWrite(0x5c, cs_flag);  // Enable MCU to Write into RAM

            bit = data&(0x80>>j);
            if(bit == 0)
            {

				dataWrite(0, cs_flag);
				dataWrite(0, cs_flag);
				dataWrite(0, cs_flag);
            }
            else
            {
            	dataWrite( ((Color & 0x0002) << 4) | 0x0f, cs_flag);
            	dataWrite( ((Color & 0x001c) << 1) | 0x07, cs_flag);
            	dataWrite( ((Color & 0x00e0) >> 2) | 0x07, cs_flag);
            }
		    
        }

    }

}

void draw_string (Uint16 startc, Uint16 startl, char *pData,Uint16 Color)
{
    Uint16 font, i=0;
    
    
	font = strlen(pData);
    if(i > 8)
        return;
        
    while(1)
    {
        font = *(pData+i);
        if(font != 0)
        {
            draw_font(startc+i*7,startl,font,Color);
            i++;
        }
        else
        {
            break;
        }
    }
}

void init_LCD(Uint16 cs_flag)      
{
	Uint16 val;
	
    /* Setup MUX for LCD SPI */
	EVM5517_I2CGPIO_configLine( 6, 0 );
	EVM5517_I2CGPIO_writeLine(  6, 1 );
	EVM5517_I2CGPIO_configLine( 5, 0 );
	EVM5517_I2CGPIO_writeLine(  5, 0 );

	/* Reset LCD module */
    EVM5517_I2CGPIO_configLine( 7, 0 );
	EVM5517_I2CGPIO_writeLine(  7, 0 );
	EVM5517_I2CGPIO_writeLine(  7, 1 );
	EVM5517_waitusec(10000);

	/* Initialize SPI */
	spi_init( );

    cmdWrite(0xAE, cs_flag);    // sleep mode on
#if(0)
	//*(ioport volatile unsigned *)0x1c00=0x2<<10;  // Select GPIO11  
	val = *(ioport volatile unsigned *)0x1c06;  //GPIO0
	val |= 0x0800;
	*(ioport volatile unsigned *)0x1c06 = val;      //Set GPIO0 as output
	wait(10);
	val = *(ioport volatile unsigned *)0x1c0A;
	val &= 0xF7FF;
	*(ioport volatile unsigned *)0x1c0A = val;      //Set GPIO0 = 0
	wait(100);
	val = *(ioport volatile unsigned *)0x1c0A;
	val |= 0x0800;
	*(ioport volatile unsigned *)0x1c0A = val;      //Set GPIO0 = 1		
	wait(5000);
#endif

	cmdWrite(0xfd, cs_flag);    // Command Lock
	dataWrite(0x12, cs_flag);   //	
	cmdWrite(0xfd, cs_flag);    // Command Lock
	dataWrite(0xB1, cs_flag);   //	
	cmdWrite(0xAE, cs_flag);    // Sleep mode on
	cmdWrite(0xB3, cs_flag);    // Set Display freq/div
	dataWrite(0xF1, cs_flag);   //		
	cmdWrite(0xCA, cs_flag);    // Set Multiplex ratio
	dataWrite(0x7F, cs_flag);   //
	cmdWrite(0xA2, cs_flag);    // Set Display offset
	dataWrite(0x00, cs_flag);   //
	cmdWrite(0xA1, cs_flag);    // Set Display start line
	dataWrite(0x00, cs_flag);   //		
	cmdWrite(0xA0, cs_flag);    // Set Remap and color depth
	dataWrite(0xb1, cs_flag);   //
	cmdWrite(0xB5, cs_flag);    // Set GPIO
	dataWrite(0x00, cs_flag);   //		
	cmdWrite(0xAB, cs_flag);    // Function slelction
	dataWrite(0x01, cs_flag);   //			
	cmdWrite(0xB4, cs_flag);    // Set segment low voltage
	dataWrite(0xA0, cs_flag);   //				
	dataWrite(0xB5, cs_flag);   // 
	dataWrite(0x55, cs_flag);   //			
	cmdWrite(0xC1, cs_flag);    // Set contrast current
	dataWrite(0xC8, cs_flag);   //				
	dataWrite(0x80, cs_flag);    // 
	dataWrite(0xC8, cs_flag);   //		
	cmdWrite(0xC7, cs_flag);    // Set Master current control
	dataWrite(0x0F, cs_flag);   //			
	cmdWrite(0xB8, cs_flag);    // Gamma lookup table	
	dataWrite(0x2, cs_flag);   //34
	dataWrite(0x3, cs_flag);   //34
	dataWrite(0x4, cs_flag);   //34
	dataWrite(0x5, cs_flag);   //34
	dataWrite(0x6, cs_flag);   //34
	dataWrite(0x7, cs_flag);   //34
	dataWrite(0x8, cs_flag);   //34
	dataWrite(0x9, cs_flag);   //34
	dataWrite(0xa, cs_flag);   //34
	dataWrite(0xb, cs_flag);   //34
	dataWrite(0xc, cs_flag);   //34
	dataWrite(0xd, cs_flag);   //34
	dataWrite(0xe, cs_flag);   //34
	dataWrite(0xf, cs_flag);   //34
	dataWrite(0x10, cs_flag);   //34
	dataWrite(0x11, cs_flag);   //34
	dataWrite(0x12, cs_flag);   //34
	dataWrite(0x13, cs_flag);   //34
	dataWrite(0x15, cs_flag);   //34
	dataWrite(0x17, cs_flag);   //34
	dataWrite(0x19, cs_flag);   //34
	dataWrite(0x1B, cs_flag);   //34
	dataWrite(0x1D, cs_flag);   //34
	dataWrite(0x1F, cs_flag);   //34
	dataWrite(0x21, cs_flag);   //34
	dataWrite(0x23, cs_flag);   //34
	dataWrite(0x25, cs_flag);   //34
	dataWrite(0x27, cs_flag);   //34
	dataWrite(0x2A, cs_flag);   //34
	dataWrite(0x2D, cs_flag);   //34
	dataWrite(0x30, cs_flag);   //34
	dataWrite(0x33, cs_flag);   //34
	dataWrite(0x36, cs_flag);   //34
	dataWrite(0x39, cs_flag);   //34
	dataWrite(0x3C, cs_flag);   //34
	dataWrite(0x3F, cs_flag);   //34
	dataWrite(0x42, cs_flag);   //34
	dataWrite(0x45, cs_flag);   //34
	dataWrite(0x48, cs_flag);   //34
	dataWrite(0x4C, cs_flag);   //34
	dataWrite(0x50, cs_flag);   //34
	dataWrite(0x54, cs_flag);   //34
	dataWrite(0x58, cs_flag);   //34
	dataWrite(0x5C, cs_flag);   //34
	dataWrite(0x60, cs_flag);   //34
	dataWrite(0x64, cs_flag);   //34
	dataWrite(0x68, cs_flag);   //34
	dataWrite(0x6C, cs_flag);   //34
	dataWrite(0x70, cs_flag);   //34
	dataWrite(0x74, cs_flag);   //34
	dataWrite(0x78, cs_flag);   //34
	dataWrite(0x7D, cs_flag);   //34
	dataWrite(0x82, cs_flag);   //34
	dataWrite(0x87, cs_flag);   //34
	dataWrite(0x8C, cs_flag);   //34
    dataWrite(0x91, cs_flag);   //34
	dataWrite(0x96, cs_flag);   //34
	dataWrite(0x9B, cs_flag);   //34
	dataWrite(0xA0, cs_flag);   //34
	dataWrite(0xA5, cs_flag);   //34
	dataWrite(0xAA, cs_flag);   //34
	dataWrite(0xAF, cs_flag);   //34
	dataWrite(0xB4, cs_flag);   //34

	cmdWrite(0xB1, cs_flag);    // Set Phase lenth
	dataWrite(0x32, cs_flag);   //		
	cmdWrite(0xB2, cs_flag);    // Enhance driving scheme capability
	dataWrite(0xA4, cs_flag);   //				
	dataWrite(0x00, cs_flag);    // 
	dataWrite(0x00, cs_flag);   //				
	cmdWrite(0xBB, cs_flag);    // Set precharge voltage
	dataWrite(0x17, cs_flag);   // 
	cmdWrite(0xB6, cs_flag);    // Set second precharge period	
	dataWrite(0x01, cs_flag);   //			
	cmdWrite(0xBE, cs_flag);    // Set VCOMH voltage
	dataWrite(0x05, cs_flag);   //
	cmdWrite(0xA6, cs_flag);    // Set Display Mode	


	cmdWrite(0xAF, cs_flag);    // Set Display Mode	 
    return;	
}

void lcd_clear(void)
{
    int i, j;

    cmdWrite(0x15, 0); 				// Set Column Address
    dataWrite(0x00, 0);	     		//   Default => 0x00 (Start Address)
    dataWrite(0x7f, 0); 			//   Default => 0x7F (End Address)
		
    cmdWrite(0x75, 0);				// Set Row Address
	dataWrite(0x00, 0);				//   Default => 0x00 (Start Address)
	dataWrite(0x7f, 0);				//   Default => 0x7F (End Address)
    	
	cmdWrite(0x5c, 0);				// Enable MCU to Write into RAM

	for(i=0;i<128;i++)
	{
		for(j=0;j<128;j++)
		{
			dataWrite(0, 0);		// Black
			dataWrite(0, 0);
			dataWrite(0, 0);
		}
	}
}

extern Int16 XmitL_Sine_1K[48];
extern Int16 XmitL_Sine_2K[48];

void draw_line(void)
{
    Uint16 x=10;
    int y=100;
	
    menu2_on_LCD();			

	draw_string(3, 76,"Press key!",0x1C);
	
    for(x = 10 ;x <(10+48);x++)
	{
		cmdWrite(0x15, 0); /* x address */
		dataWrite(x, 0);
		dataWrite(x, 0);
    
		cmdWrite(0x75, 0); /* y address */
		dataWrite(y, 0);
		dataWrite(y, 0);
    
    	cmdWrite(0x5C, 0);  /* draw pixel */

	    dataWrite(0x1c, 0);
	    dataWrite(0x1c, 0);
	   	dataWrite(0x1c, 0);
	}

    for(x = 58 ;x <(58+48);x++)
	{
		cmdWrite(0x15, 0); /* x address */
		dataWrite(x, 0);
		dataWrite(x, 0);

		cmdWrite(0x75, 0); /* y address */
		dataWrite(y, 0);
		dataWrite(y, 0);
    
    	cmdWrite(0x5C, 0); /* draw pixel */
	    dataWrite(0x1c, 0);
	    dataWrite(0x1c, 0);
	   	dataWrite(0x1c, 0);
	}    
}


void draw_sine_1k(void)
{
    Uint16 x=10;
    int value_start, value_move;
    int diff, y=100;
	
    menu2_on_LCD();
    value_start = XmitL_Sine_1K[0];

    for(x = 10 ;x <(10+48);x++)
	{
		cmdWrite(0x15, 0); /* x address */
		dataWrite(x, 0);
		dataWrite(x, 0);
    
        value_move = XmitL_Sine_1K[x-10];
		diff = (value_move -value_start)/1000; 
	    diff = y-diff;
		cmdWrite(0x75, 0); /* y address */
		dataWrite(diff, 0);
		dataWrite(diff, 0);
    
    	cmdWrite(0x5C, 0); /* draw pixel */
	    dataWrite(0, 0);
	    dataWrite(63, 0);
	    dataWrite(0, 0);
	}

    for(x = 58 ;x <(58+48);x++)
	{
		cmdWrite(0x15, 0); /* x address */
		dataWrite(x, 0);
		dataWrite(x, 0);

        value_move = XmitL_Sine_1K[x-58];
		diff = (value_move -value_start)/1000; 
	    diff = y-diff;
		cmdWrite(0x75, 0); /* y address */
		dataWrite(diff, 0);
		dataWrite(diff, 0);
    
    	cmdWrite(0x5C, 0); /* draw pixel */
	    dataWrite(0, 0);
	    dataWrite(63, 0);
	    dataWrite(0, 0);
	}
}

void draw_sine_2k(void)
{
    Uint16 x=10;
    int value_start, value_move;
    int diff, y=100;
	
    menu2_on_LCD();	
    value_start = XmitL_Sine_1K[0];
    	    
    for(x = 10 ;x <(10+48);x++)
	{
		cmdWrite(0x15, 0); /* x address */
		dataWrite(x, 0);
		dataWrite(x, 0);

        value_move = XmitL_Sine_2K[x-10];
		diff = (value_move -value_start)/1000; 
	    diff = y-diff;
		cmdWrite(0x75, 0); /* y address */
		dataWrite(diff, 0);
		dataWrite(diff, 0);
    
    	cmdWrite(0x5C, 0); /* draw pixel */
	    dataWrite(0, 0);
	    dataWrite(63, 0);
	    dataWrite(0, 0);
	}

    for(x = 58 ;x <(58+48);x++)
	{
		cmdWrite(0x15, 0); /* x address */
		dataWrite(x, 0);
		dataWrite(x, 0);

        value_move = XmitL_Sine_2K[x-58];
		diff = (value_move -value_start)/1000; 
	    diff = y-diff;
		cmdWrite(0x75, 0); /* y address */
		dataWrite(diff, 0);
		dataWrite(diff, 0);
    
    	cmdWrite(0x5C, 0); /* draw pixel */
	    dataWrite(0, 0);
	    dataWrite(63, 0);
	    dataWrite(0, 0);
	}
}

void menu1_on_LCD(void)
{

	lcd_clear();
	draw_string(15, 6,"5517 EVM Demo",0xF0);
	draw_string(3, 26,"SW14:LED Blink On",0x0F);		// SW12 --> SW16
	draw_string(3, 36,"SW15:LED Blink Off",0x0F);		// SW11 --> SW15
	draw_string(3, 46,"SW16:RTC Reset",0x0F);			// SW7  --> SW9
	draw_string(3, 56,"SW9: Tone Menu",0x0F);			// SW13 --> SW17
	
	draw_string(6,82,"Year",0x2F);		
	draw_string(45,82,"Month",0x2F);		
	draw_string(85,82,"Day",0x2F);		
	draw_string(6,107,"Hour",0x2F);		
	draw_string(45,107,"Min",0x2F);		
	draw_string(85,107,"Sec",0x2F);			    
}


void menu2_on_LCD(void)
{
	lcd_clear();
	draw_string(20, 6,"<Tone Demo>",0xF0);

	draw_string(3, 26,"SW14: Codec1 1KHz",0x0F);
	draw_string(3, 36,"SW15: Codec2 1KHz",0x0F);
//	draw_string(3, 46,"SW16: Stop Audio",0x0F);
	draw_string(3, 46,"SW18: Main Menu ",0x0F);
	
}
