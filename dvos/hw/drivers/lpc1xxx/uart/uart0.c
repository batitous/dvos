
#include "../../kernel/include/kernel-dvos.h"
#include "../include/libs-hardware.h"



//--------------------- private configuration:

#ifdef MCU_IS_LPC1311

void setUartIoCon(void)
{
    CLRBITS(LPC_IOCON->PIO1_6,7);
    LPC_IOCON->PIO1_6 |= 1;
    
    CLRBITS(LPC_IOCON->PIO1_7,7);
    LPC_IOCON->PIO1_7 |= 1;
    
    PowerOnUART0();
}
#endif

#ifdef MCU_IS_LPC1315

void setUartIoCon(void)
{
    CLRBITS(LPC_IOCON->PIO0_19,7);
    LPC_IOCON->PIO0_19 |= 1;
    
    CLRBITS(LPC_IOCON->PIO0_18,7);
    LPC_IOCON->PIO0_18 |= 1;
    
    PowerOnUART0();
}
#endif

#ifdef MCU_IS_LPC13XX

#       ifdef HARDWARE_IS_LPC13XX_EMOX_IO
//115200
#               define setBaudrate()    LPC_UART0->DLL = 39; LPC_UART0->DLM = 0;
//57600
//#               define setBaudrate()    LPC_UART0->DLL = 78; LPC_UART0->DLM = 0;
#       else
//115200
#               define setBaudrate()    LPC_UART0->DLL = 39; LPC_UART0->DLM = 0;
#endif

//38400
//#       define setBaudrate()    LPC_UART0->DLL = 117; LPC_UART0->DLM = 0;
#endif  

#ifdef MCU_IS_LPC17XX

void setUartIoCon(void)
{
    // how to compute uart baudrate:
    //
    // uartbaudrate = PCLK / ( 16 x ( 256 x UART0_DLM + UART0_DLL ) )
    // with PCLK = 72MHz
    
    LPC_PINCON->PINSEL0  |= 0x50;
}

#       define setBaudrate()    LPC_UART0->DLL = 27; LPC_UART0->DLM = 0;

#endif


#ifdef HARDWARE_IS_LPC13XX_EMOX_IO
#       define UART_BUFFER_SIZE    128
#else
#       define UART_BUFFER_SIZE    64
#endif


//--------------------- private variables:

static volatile KIOStream * uartStream;



//--------------------- private functions:

void UART0_IRQHandler(void)
{
    UInt32 status = LPC_UART0->IIR;
        
    //Check if interrupt is pending
    if( (status & 1)==0)
    {
        status = (status >> 1) & 0x07;

        //Receive Data Available
        if(status==0x02)
        {   
            SetByteToStream((KIOStream *)uartStream,LPC_UART0->RBR);
            IrqWakeUpTaskFromStream((KIOStream *)uartStream);
        }
    }
}

//--------------------- public functions:

void PowerOnUART0(void)
{
     // enable uart clock
#ifdef MCU_IS_LPC13XX
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,12);    
    LPC_SYSCON->UARTCLKDIV = 1;
#endif
}

void PowerOffUART0(void)
{
#ifdef MCU_IS_LPC13XX
    CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,12);
    LPC_SYSCON->UARTCLKDIV = 0;
#endif
}

void InitUART0(void)
{
    setUartIoCon();
    
    LPC_UART0->FCR = 0x7;   // enable and reset fifos
    LPC_UART0->LCR = 0x83;	// 8 bits; enable divisor latches

    setBaudrate();
    
    LPC_UART0->LCR=3;

    LPC_UART0->IER = BIT(0);    // enable receive interrupt

    
    NVIC_SetPriority(UART0_IRQn, 0x04);
    NVIC_EnableIRQ(UART0_IRQn); // enable NVIC UART0 Interrupt

    uartStream = NewInputOutputStream(UART_BUFFER_SIZE);
}

void SendByteToUART0(UInt8 byte)
{
	while( (LPC_UART0->LSR & BIT(5) ) ==0 );

	// test bit-band memory : LSR register is at +0x14 from the base UART memory
//	while( ( BITBAND( LPC_UART0_BASE + 0x14, 5) )  == 0 );

	LPC_UART0->THR=byte;
}

void SendBufferToUART0(UInt8 * Buffer,UInt32 Count)
{
    UInt32 i;

    for(i=0;i<Count;i++)
    {
        SendByteToUART0(Buffer[i]);
    }
}


Bool GetBufferFromUART0(UInt8 * buffer, UInt32 len)
{
    return GetBufferFromStream((KIOStream *)uartStream,buffer,len,30);
}

Bool GetByteFromUART0(UInt8 *Data)
{
    return GetByteFromStream((KIOStream *)uartStream, Data);
}

void WaitDataFromUART0(void)
{
    WaitDataFromStream((KIOStream *)uartStream);
}

/*
UInt32 GetAllBufferFromUART0(UInt8 *buffer, UInt32 len)
{
    WaitDataFromStream(uartStream);

    return GetAllBufferFromStream(uartStream,buffer, len);
}
 */
