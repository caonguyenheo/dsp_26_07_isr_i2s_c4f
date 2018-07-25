/* ============================================================================
 * Copyright (c) 2008-2016 Texas Instruments Incorporated.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/


/** @file csl_uart_polled_example.c
 *
 *  @brief UART example code to test the Polled mode functionality of CSL UART
 *
 *
 * \page    page18  CSL UART EXAMPLE DOCUMENTATION
 *
 * \section UART1   UART EXAMPLE1 - POLL MODE TEST
 *
 * \subsection UART1x    TEST DESCRIPTION:
 *		This test is to verify the CSL UART module operation in polled mode.
 * This test code communicates with the HyperTerminal on the host PC through
 * UART module on C5535/C5515 DSP operating in polled mode. UART peripheral is
 * configured by the test code to the following values
 * Baud Rate - 2400.
 * Data bits - 8.
 * Parity - None.
 * Stop bits - 1.
 * Flow control - None.
 * HyperTerminal on the host PC should be configured with the same values to
 * to proper communication with the C5535/C5515/C5517 EVM. C5535/C5515/C5517 EVM should be
 * connected to the host PC using an RS232 cable and HyperTerminal on the host
 * PC should be opened and connected.This test works at all the PLL frequencies.
 *
 * Upon running the test, a message prompting to enter the string size will be
 * displayed on HyperTerminal.Enter the string size which is greater than 1 and
 * less than 99. String length should be two characters and the numbers below
 * 10 should be preceded by 0(01,02,03...). After reading the string size
 * a message prompting to enter the string will be displayed on HyperTerminal.
 * Enter the string which is exactly of the length specified in the previous
 * query. Once the string of the specified size is entered, test code will
 * stop reading from the HyperTerminal and send message to inform that the
 * reading from HyperTerminal has been stopped. After reading the string
 * test code will send the same string back to the HyperTerminal.
 *
 * @verbatim
   Messages displayed on the HyperTerminal when entered a string
   "CSL UART TESTING" will be as shown below.

     ====================================================================
     ==                                                                ==
     ==  Enter the size of the string(min 01 to max 99)                ==
     ==  >> 16                                                         ==
     ==                                                                ==
     ==  Enter the string:                                             ==
     ==  >> CSL UART TESTING                                           ==
     ==                                                                ==
     ==  Please stop typing, reading already stopped...!!!             ==
     ==                                                                ==
     ==  YOU HAVE ENTERED: CSL UART TESTING                            ==
     ==                                                                ==
     ====================================================================

   @endverbatim
 * Manual inspection is required to verify the success of each step.
 * All the communication between UART and HyperTerminal will be displayed
 * on the CCS "stdout" window.
 *
 * NOTE: THIS TEST HAS BEEN DEVELOPED TO WORK WITH CHIP VERSIONS C5535. C5515
 * AND C5517. MAKE SURE THAT PROPER CHIP VERSION MACRO IS DEFINED IN THE FILE
 * c55xx_csl\inc\csl_general.h.
 *
 * \subsection UART1y    TEST PROCEDURE:
 *  @li Connect the RS232 cable; One end to the UART port on the C5535/C5515/C5517 EVM(J13/J1/J2)
 *      and other  to the COM port of the Windows Xp PC.
 *  @li Open the HyperTerminal on the Host PC. To open the HyperTerminal click
 *      on 'Start->Programs->Accessories->Communications->HyperTerminal�
 *  @li Disconnect the HyperTerminal by selecting menu Call->Disconnect
 *  @li Select Menu 'File->Properties' and click on the Button 'Configure'
 *      \n  Set 'Bits Per Second(Baud Rate)' to 2400.
 *      \n  Set 'Data bits' to 8.
 *      \n  Set 'Parity' to None.
 *      \n  Set 'Stop bits' to 1.
 *      \n  Set 'Flow control' to None.
 *      \n  Click on 'OK' button.
 *      \n  HyperTerminal is configured and ready for communication
 *  @li Connect the HyperTerminal by selecting menu Call->Call.
 *  @li Open the CCS and connect the target (C5535/C5515/C5517 EVM)
 *  @li Open the project "CSL_UART_pollExample.pjt" and build it
 *  @li Load the program on to the target
 *  @li Set the PLL frequency to 12.288MHz
 *  @li Run the program and observe the test result
 *  @li Repeat the test at the following PLL frequencies
 *      C5515: 60MHz and 100MHz
 *      C5517: 60MHz, 100MHz, 150MHz and 200MHz
 *      C5535 eZdsp: 60MHz and 100MHz
 *  @li Repeat the test in Release mode
 *
 * \subsection UART1z    TEST RESULT:
 *  @li All the CSL APIs should return success
 *  @li Data sent from the HyperTerminal should be read by the UART properly
 *  @li Data sent by the UART should be displayed on the HyperTerminal properly
 *
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ================
 * 16-Sep-2008 Created
 * 23-Jul-2012 Added C5517 Compatibility
 * 10-Mar-2016 Updates to header
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "csl_uart.h"
#include "csl_uartAux.h"
#include "csl_general.h"
#include "csl_sysctrl.h"
#include "evm5515.h"
#include "math.h"
#include <stdlib.h>
#include "csl_intc.h"
/* Global constants */
/* String length to be received and transmitted */
#define WR_STR_LEN    (80u)
#define RD_STR_LEN    (10u)

#define CSL_PLL_DIV_000    (0)
#define CSL_PLL_DIV_001    (1u)
#define CSL_PLL_DIV_002    (2u)
#define CSL_PLL_DIV_003    (3u)
#define CSL_PLL_DIV_004    (4u)
#define CSL_PLL_DIV_005    (5u)
#define CSL_PLL_DIV_006    (6u)
#define CSL_PLL_DIV_007    (7u)

#define CSL_PLL_CLOCKIN    (32768u)

#define PLL_CNTL1        *(ioport volatile unsigned *)0x1C20
#define PLL_CNTL2        *(ioport volatile unsigned *)0x1C21
#define PLL_CNTL3        *(ioport volatile unsigned *)0x1C22
#define PLL_CNTL4        *(ioport volatile unsigned *)0x1C23
#define MAX_WRITE_LEN (500)
#define APP_NAME   "DSP DEMO V_001.00.02"
Int32 C55x_msgWrite(const char *fmt, ...);
Int32 C55x_msgRead(Uint8 *data, Uint32 length);
static void DisplayBanner(char * AppName);

#if 0
extern Int16 aic3204_loop_stereo_in1();
extern Int16 aic3204_config_i2c();
extern int aic3204_init_set_parameter();
extern int aic3204_loop_mic_in();
#endif

static char write_buffer[MAX_WRITE_LEN];
/* Global data definition */
/* UART setup structure */
CSL_UartSetup uartSetup =
{
	/* Input clock freq in MHz */
    60000000,
	/* Baud rate */
    115200,
	/* Word length of 8 */
    CSL_UART_WORD8,
	/* To generate 1 stop bit */
    0,
	/* Disable the parity */
    CSL_UART_DISABLE_PARITY,
	/* Disable fifo */
	/* Enable trigger 14 fifo */
	CSL_UART_FIFO_DMA1_DISABLE_TRIG14,
//    0x00u,
	/* Loop Back enable */
    CSL_UART_NO_LOOPBACK,
	/* No auto flow control*/
	CSL_UART_NO_AFE ,
	/* No RTS */
	CSL_UART_NO_RTS ,
};

CSL_UartObj uartObj;
typedef enum {
    PLATFORM_WRITE_UART,
    /** <Write to the UART */
    PLATFORM_WRITE_PRINTF,
    /** <printf mapped output -- CCS console */
    PLATFORM_WRITE_ALL
    /** <write all - default configuration */
} WRITE_info;

typedef enum {
    PLATFORM_READ_UART,
    /** <Read from the UART */
    PLATFORM_READ_SCANF
    /** <Read from scanf -- CCS console */
} READ_info;
READ_info   read_type;
static WRITE_info   write_type;
/* UART data buffers */
//char rdbuffer[100];
//char wrbuffer[55] = "\r\nEnter the size of the string(min 01 to max 99)\r\n";

/**
 *  \brief  Tests CSL UART module in polled mode.
 *
 *  This functions sends and receives data from the HyperTerminal
 *  on the host PC.
 *
 *  \param  none
 *
 *  \return Test result
 */
CSL_Status CSL_uartInitialize(void);

/**
 *  \brief  Function to calculate the system clock
 *
 *  \param    none
 *
 *  \return   System clock value in Hz
 */
Uint32 getSysClk(void);

/**
 *  \brief  main function
 *
 *  This function calls UART test function and displays the test result
 *
 *  \param  none
 *
 *  \return none
 */

   /////INSTRUMENTATION FOR BATCH TESTING -- Part 1 --
   /////  Define PaSs_StAtE variable for catching errors as program executes.
   /////  Define PaSs flag for holding final pass/fail result at program completion.
volatile Int16 PaSs_StAtE = 0x0001; // Init to 1. Reset to 0 at any monitored execution error.
volatile Int16 PaSs = 0x0000; // Init to 0.  Updated later with PaSs_StAtE when and if
   /////                                  program flow reaches expected exit point(s).
   /////

extern int Pn9_Fsk();
extern Int16 I2s_Init(void);

extern int bit_pos;
extern int row_byte_pos;
extern int column_byte_pos;
extern short SigQ_Flg;
extern int  Make_Fsk();
 int CodecInit();
 extern short SigQ_Flg;

int main(void)
{
	CSL_Status    status;
    status = CSL_uartInitialize();

	if(status != CSL_SOK)
	{
	    UART_PRINT("\r\nCSL UART POLLED MODE TEST FAILED!!\r\n");
   /////INSTRUMENTATION FOR BATCH TESTING -- Part 2 --
   /////  Reseting PaSs_StAtE to 0 if error detected here.
        PaSs_StAtE = 0x0000; // Was intialized to 1 at declaration.
   /////
	}

    DisplayBanner(APP_NAME);

    //Init I2s Interrup
    status = I2s_Init();
    if(status != CSL_SOK)
    {
        UART_PRINT("\nCSL I2S INTERRUPT MODE TEST FAILED!!\r\n");
        PaSs_StAtE = 0x0000;
    }

    //Init Aic3204
    status = CodecInit();
    if(status != CSL_SOK)
    {
        UART_PRINT("\nCSL CODEC MODE INIT FAILED!!\r\n");
        PaSs_StAtE = 0x0000;
    }

    bit_pos = 0x08;
    row_byte_pos = 0;
    column_byte_pos = 0;

    //Implement Pn9 String
    status = Pn9_Fsk();
    if(status != CSL_SOK)
    {
        UART_PRINT("\nCSL Pn9_Fsk fail!!\r\n");
    }

    //Enable Interrup
    IRQ_enable(XMT2_EVENT);

    while(1)
    {

        if(SigQ_Flg == 1)
        {
          Make_Fsk();
          SigQ_Flg = 0;
        }

    }

   /////INSTRUMENTATION FOR BATCH TESTING -- Part 3 --
   /////  At program exit, copy "PaSs_StAtE" into "PaSs".
        PaSs = PaSs_StAtE; //If flow gets here, override PaSs' initial 0 with
   /////                   // pass/fail value determined during program execution.
   /////  Note:  Program should next exit to C$$EXIT and halt, where DSS, under
   /////   control of a host PC script, will read and record the PaSs' value.
   /////
}

/**
 *  \brief  Tests CSL UART module in polled mode.
 *
 *  This functions sends and receives data from the HyperTerminal
 *  on the host PC.
 *
 *  \param  none
 *
 *  \return Test result
 */
CSL_Status CSL_uartInitialize(void)
{
    CSL_UartHandle    hUart;
    CSL_Status        status;
//	Uint16            stringSize;
	Uint32            sysClk;

	sysClk = getSysClk();

	uartSetup.clkInput = sysClk;

    status = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE,
                         CSL_EBSR_PPMODE_1);
    if(CSL_SOK != status)
    {
        printf("SYS_setEBSR failed\n");
        return(status);
    }

    /* Loop counter and error flag */
    status = UART_init(&uartObj,CSL_UART_INST_0,UART_POLLED);
    if(CSL_SOK != status)
    {
        printf("UART_init failed error code %d\n",status);
        return(status);
    }
    else
    {
		printf("UART_init Successful\n");
	}

    status = SYS_setEBSR(CSL_EBSR_FIELD_PPMODE,
                         CSL_EBSR_PPMODE_1);
    if(CSL_SOK != status)
    {
        printf("SYS_setEBSR failed\n");
        return (status);
    }

    /* Handle created */
    hUart = (CSL_UartHandle)(&uartObj);

    /* Configure UART registers using setup structure */
    status = UART_setup(hUart,&uartSetup);
    if(CSL_SOK != status)
    {
        printf("UART_setup failed error code %d\n",status);
        return(status);
    }
    else
    {
		printf("UART_setup Successful\n");
	}
	return(CSL_SOK);
}
Int32 C55x_msgWrite(const char *fmt, ...)
{
    va_list         arg_ptr;
    Uint32          length;
    CSL_Status      retVal;
    CSL_UartHandle  hUart;

    /* Initial printf to temporary buffer.. at least try some sort of sanity check so we don't write all over
     * memory if the print is too large.
     */
    if (strlen(fmt) > MAX_WRITE_LEN)
    {
        printf("Exceed's the max write length\n");
        return (-1);
    }

    va_start( arg_ptr, fmt );
    length = vsprintf( (char *)write_buffer, fmt, arg_ptr );
    va_end( arg_ptr );
    length = length;

    if ((write_type == PLATFORM_WRITE_PRINTF) || (write_type == PLATFORM_WRITE_ALL))
    {
        /*Used to print on the CCS console*/
        UART_PRINT("%s", write_buffer);
        fflush(stdout);
    }

    /* Handle created */
    hUart = (CSL_UartHandle)(&uartObj);

    if ((write_type == PLATFORM_WRITE_UART) || (write_type == PLATFORM_WRITE_ALL))
    {
        /*Used to print on the serial console*/
        retVal = UART_fputs(hUart,write_buffer,0);
        if(CSL_SOK != retVal)
        {
            UART_PRINT("UART_fputs failed error code %d\n",retVal);
            return retVal;
        }
    }

    return retVal;

}
Int32 C55x_msgRead(Uint8 *data, Uint32 length)
{
    Uint32 index;

    *data = '\0';

    CSL_Status retVal = 0;

    if ((read_type == PLATFORM_READ_UART) || (read_type == PLATFORM_READ_SCANF))
    {
        CSL_UartHandle hUart;
        hUart = (CSL_UartHandle)(&uartObj);

        for (index = 0; index < length; index++)
        {
            retVal = UART_read(hUart, (char*)data, 1, 0);
            if(retVal)
            {
                break;
            }

            if((*data == 0xD) || (*data == 0x1B))
            {
                break;
            }

            UART_fputc(hUart, *data, 0);
            data++;
        }
    }

    if ((read_type == PLATFORM_READ_SCANF))
    {
        scanf("%s", data);
    }

    return retVal;

}
static void DisplayBanner(char * AppName)
{
    UART_PRINT("\n\n\n\r");
    UART_PRINT("\t\t *************************************************\n\r");
    UART_PRINT("\t\t **                                             **\n\r");
    UART_PRINT("\t\t **BORAD EV5517 %s APPLICATION**\n\r", AppName);
    UART_PRINT("\t\t **                                             **\n\r");
    UART_PRINT("\t\t *************************************************\n\r");
    UART_PRINT("\n\n\n\r");
    UART_PRINT("\r\nCSL UART MODE SUCCESS!!\r\n");
}
/**
 *  \brief  Function to calculate the clock at which system is running
 *
 *  \param    none
 *
 *  \return   System clock value in Hz
 */
#if (defined(CHIP_C5505_C5515) || defined(CHIP_C5504_C5514) || defined(CHIP_C5535) || defined(CHIP_C5545))

Uint32 getSysClk(void)
{
	Bool      pllRDBypass;
	Bool      pllOutDiv;
	Uint32    sysClk;
	Uint16    pllM;
	Uint16    pllRD;
	Uint16    pllOD;

	pllM = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR1, SYS_CGCR1_M);

	pllRD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDRATIO);
	pllOD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_ODRATIO);

	pllRDBypass = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDBYPASS);
	pllOutDiv   = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIVEN);

	sysClk = CSL_PLL_CLOCKIN;

	if (0 == pllRDBypass)
	{
		sysClk = sysClk/(pllRD + 4);
	}

	sysClk = (sysClk * (pllM + 4));

	if (1 == pllOutDiv)
	{
		sysClk = sysClk/(pllOD + 1);
	}

	/* Return the value of system clock in Hz */
	return(sysClk);
}

#elif (defined(CHIP_C5517))
Uint32 getSysClk(void)
{
	Uint32    sysClk;
	float    Multiplier;
	Uint16    OD;
	Uint16    OD2;
	Uint16    RD, RefClk;
	Uint32	  temp1, temp2, temp3, vco;
	//Uint16 DIV;

	temp2 =  PLL_CNTL2;
	temp3 =  (temp2 & 0x8000) <<1 ;
	temp1 = temp3 + PLL_CNTL1;
	Multiplier = temp1/256 +1;
	RD = (PLL_CNTL2 & 0x003F) ;

	RefClk = 12000/(RD+1);

	vco = Multiplier * (Uint32)RefClk;

	OD = (PLL_CNTL4 & 0x7);

	sysClk = vco/(OD+1);

	OD2 = ((PLL_CNTL4 >> 10) & 0x1F) ;

	if (PLL_CNTL3 & 0x8000)	// PLL Bypass
		sysClk = RefClk;
	else
		sysClk = vco/(OD+1);

	if ((PLL_CNTL4 & 0x0020) == 0)	/* OutDiv2 */
		sysClk = sysClk / ( 2*(OD2+1));

	/* Return the value of system clock in KHz */
	return(sysClk*1000);
}

#else

Uint32 getSysClk(void)
{
	Bool      pllRDBypass;
	Bool      pllOutDiv;
	Bool      pllOutDiv2;
	Uint32    sysClk;
	Uint16    pllVP;
	Uint16    pllVS;
	Uint16    pllRD;
	Uint16    pllVO;
	Uint16    pllDivider;
	Uint32    pllMultiplier;

	pllVP = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR1, SYS_CGCR1_MH);
	pllVS = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_ML);

	pllRD = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDRATIO);
	pllVO = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_ODRATIO);

	pllRDBypass = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR2, SYS_CGCR2_RDBYPASS);
	pllOutDiv   = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIVEN);
	pllOutDiv2  = CSL_FEXT(CSL_SYSCTRL_REGS->CGCR4, SYS_CGCR4_OUTDIV2BYPASS);

	pllDivider = ((pllOutDiv2) | (pllOutDiv << 1) | (pllRDBypass << 2));

	pllMultiplier = ((Uint32)CSL_PLL_CLOCKIN * ((pllVP << 2) + pllVS + 4));

	switch(pllDivider)
	{
		case CSL_PLL_DIV_000:
		case CSL_PLL_DIV_001:
			sysClk = pllMultiplier / (pllRD + 4);
		break;

		case CSL_PLL_DIV_002:
			sysClk = pllMultiplier / ((pllRD + 4) * (pllVO + 4) * 2);
		break;

		case CSL_PLL_DIV_003:
			sysClk = pllMultiplier / ((pllRD + 4) * 2);
		break;

		case CSL_PLL_DIV_004:
		case CSL_PLL_DIV_005:
			sysClk = pllMultiplier;
		break;

		case CSL_PLL_DIV_006:
			sysClk = pllMultiplier / ((pllVO + 4) * 2);
		break;

		case CSL_PLL_DIV_007:
			sysClk = pllMultiplier / 2;
		break;
	}

	/* Return the value of system clock in KHz */
	return(sysClk);
}

#endif

