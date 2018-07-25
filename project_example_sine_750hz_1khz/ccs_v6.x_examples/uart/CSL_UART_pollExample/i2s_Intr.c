#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "csl_i2s.h"
#include "csl_intc.h"
#include <csl_general.h>
#include "csl_sysctrl.h"
#include "evm5515.h"

#define CSL_TEST_FAILED         (1)
#define CSL_TEST_PASSED         (0)
#define	CSL_I2S_BUF_LEN			(4)

#define Rcv 0x08
#define Xmit 0x20

CSL_IrqDataObj  CSL_IrqData;
//Uint16 i2sIntcWriteBuff[CSL_I2S_BUF_LEN];
//Uint16 i2sIntcReadBuff[CSL_I2S_BUF_LEN];
CSL_I2sHandle	i2sHandle;
Uint16 writeCompete = 0;
Uint16 readComplete = 0;
extern void VECSTART(void);
extern short SigQ0[];
extern short g_SigQ_Buff[2][480];
extern short SigQ_Unit;
extern short SigQ_Pos;
extern short SigQ_Flg;
extern short SigQ_Valid_Flg;
//volatile Uint16 rxisrcntr = 0, txisrcntr=0;

interrupt void i2s_rxIsr();
interrupt void i2s_txIsr();

Int16 I2s_Init(void)
{
    Int16           status = CSL_TEST_FAILED;
    Int16           result;
    I2S_Config      hwConfig;
//    CSL_IRQ_Config      rxconfig;
    CSL_IRQ_Config      txconfig;


//   Open the device with instance 0
    i2sHandle = I2S_open(I2S_INSTANCE2, I2S_INTERRUPT, I2S_CHAN_STEREO);
    if(NULL == i2sHandle)
    {
        status = CSL_TEST_FAILED;
        return (status);
    }
    else
    {
        UART_PRINT("I2S Module Instance Open Successful\r\n");
    }
//    result = SYS_setEBSR(CSL_EBSR_FIELD_SP0MODE,
//                         CSL_EBSR_SP0MODE_1);

//    result =  SYS_setEBSR(CSL_EBSR_FIELD_PPMODE, CSL_EBSR_PPMODE_4);    //i2s2 mode setup
//    if(CSL_SOK != result)
//    {
//        UART_PRINT("SYS_setEBSR failed\r\n");
//        return (result);
//    }

//   Set the value for the configure structure
    hwConfig.dataType           = I2S_STEREO_ENABLE;
    hwConfig.loopBackMode       = I2S_LOOPBACK_ENABLE;
    hwConfig.fsPol              = I2S_FSPOL_LOW;
    hwConfig.clkPol             = I2S_FALLING_EDGE;
    hwConfig.datadelay          = I2S_DATADELAY_ONEBIT;
    hwConfig.datapack           = I2S_DATAPACK_ENABLE;
    hwConfig.signext            = I2S_SIGNEXT_DISABLE;
    hwConfig.wordLen            = I2S_WORDLEN_16;
    hwConfig.i2sMode            = I2S_MASTER;
    hwConfig.clkDiv             = I2S_CLKDIV64; //I2S_CLKDIV4
    hwConfig.fsDiv              = I2S_FSDIV16;  //I2S_FSDIV64 //I2S_FSDIV32
    hwConfig.FError             = I2S_FSERROR_ENABLE;
    hwConfig.OuError            = I2S_OUERROR_ENABLE;

//   Configure hardware registers
    result = I2S_setup(i2sHandle, &hwConfig);

    if(result != CSL_SOK)
    {
        status = CSL_TEST_FAILED;
        return (status);
    }
    else
    {
        UART_PRINT("I2S Module Configuration Successful\r\n");
    }

//   Clear any pending interrupts
    IRQ_clearAll();

//     Disable all the peripheral interrupts
    IRQ_disableAll();

    IRQ_setVecs((Uint32)(&VECSTART));

//   Configuring Interrupt
    txconfig.funcAddr = &i2s_txIsr;
    IRQ_plug(XMT2_EVENT, txconfig.funcAddr);
//     Enabling Interrupt
    //IRQ_enable(XMT2_EVENT);
    IRQ_globalEnable();

    I2S_transEnable(i2sHandle, TRUE);
#if 0
    rxconfig.funcAddr = &i2s_rxIsr;
    IRQ_plug (RCV2_EVENT, rxconfig.funcAddr);
//   Enabling Interrupt
    IRQ_enable(RCV2_EVENT);

    IRQ_globalEnable();
    result = I2S_transEnable(i2sHandle, TRUE);
    while(readComplete != 1);
    IRQ_globalDisable();
    result = I2S_transEnable(i2sHandle, FALSE);
#endif

#if 0
//   Reset the registers
    result = I2S_reset(i2sHandle);

    if(result != CSL_SOK)
    {
        return (CSL_TEST_FAILED);
    }
    else
    {
        UART_PRINT("I2S Reset Successful\r\n");
    }

//   Close the operation
    result = I2S_close(i2sHandle);

    if(result != CSL_SOK)
    {
        status = CSL_TEST_FAILED;
        return (status);
    }
    else
    {
        UART_PRINT("I2S Close Successful\r\n");
    }

//   Clear any pending interrupts
    IRQ_clearAll();

//   Disable all the peripheral interrupts
    IRQ_disableAll();

#endif
    return (CSL_TEST_PASSED);
}

interrupt void i2s_txIsr()
{
#if 1
    if(SigQ_Valid_Flg == 1)
    {
//        I2S2_W1_MSW_W = (-1) * (g_SigQ_Buff[SigQ_Unit][SigQ_Pos++]);
        I2S2_W1_MSW_W = (g_SigQ_Buff[SigQ_Unit][SigQ_Pos++]);
//        SigQ_Pos = SigQ_Pos % 48;
        if(SigQ_Pos == 480)
        {
            SigQ_Pos = 0;
            SigQ_Unit = (SigQ_Unit + 1) % 2;
            SigQ_Flg = 1;
        }
    }
    else
    {
        I2S2_W1_MSW_W = 0;
    }
#endif
}

#if 0
interrupt void i2s_rxIsr()
{
#if 1
    Int16           result;

    IRQ_disable(RCV2_EVENT);
    /** Read data from register and buffered                    */
    result = I2S_read(i2sHandle, i2sIntcReadBuff, CSL_I2S_BUF_LEN);
    if(result == CSL_SOK)
    {
        UART_PRINT("I2S Read Successful\r\n");
        readComplete = 1;
    }
#endif

#if 0
    Int16   result = 0;

    IRQ_globalDisable();
    result = I2S_read(i2sHandle, WriteBuff, 4);
    if(result == CSL_SOK)
    {
        UART_PRINT("I2S Read Successful\r\n");
        readComplete = 1;
    }
/*    if(isrcntr==7000)
    {
        SaveData[0]=ReadData[0];
        SaveData[1]=ReadData[1];
        SaveData[2]=ReadData[2];
        SaveData[3]=ReadData[3];
    }*/
    isrcntr++;
    IRQ_globalEnable();
#endif

}
#endif



