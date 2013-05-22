
#include "../include/libs-hardware.h"


#define SPI_SCK_PIN		15	// Clock        P0.15 out	(PINSEL0)
//#define SPI_SSEL_PIN		16	// Card-Select	P0.16 GPIO out	(PINSEL1)
#define SPI_MISO_PIN		17	// from Card	P0.17 in	(PINSEL1)
#define SPI_MOSI_PIN		18	// to Card	P0.18 out       (PINSEL1)

#define CPHA    3
#define CPOL    4
#define MSTR    5
#define SPIE	7
#define SPIF	7

void InitSPI(void)
{
	// Turn on the power
        SETBIT(LPC_SC->PCONP, 8);

	//clock
        CLRBIT(LPC_SC->PCLKSEL0, 17);
        SETBIT(LPC_SC->PCLKSEL0, 16);

	// setup GPIO
        SETBIT(LPC_GPIO0->FIODIR, SPI_SCK_PIN);
        SETBIT(LPC_GPIO0->FIODIR, SPI_MOSI_PIN);
//        SETBIT(LPC_GPIO0->FIODIR, SPI_SSEL_PIN);
        CLRBIT(LPC_GPIO0->FIODIR, SPI_MISO_PIN);
        
        //SCK
        SETBIT(LPC_PINCON->PINSEL0, 30);
        SETBIT(LPC_PINCON->PINSEL0, 31);
        
        //SSEL ???
        //CLRBIT(LPC_PINCON->PINSEL1, 0);
        //CLRBIT(LPC_PINCON->PINSEL1, 1);
        
        // MISO
        SETBIT(LPC_PINCON->PINSEL1, 2);
        SETBIT(LPC_PINCON->PINSEL1, 3);
        
        // MOSI
        SETBIT(LPC_PINCON->PINSEL1, 4);
        SETBIT(LPC_PINCON->PINSEL1, 5);
        
        //set speed (8 is max: ~12,5Mhz)
        LPC_SPIF->SPCCR = 8;
        

        SETBIT(LPC_SPIF->SPCR, MSTR);   // 0=slave, 1=master 
        CLRBIT(LPC_SPIF->SPCR, CPHA);   // 0=first clock edge, 1=second clock edge
        CLRBIT(LPC_SPIF->SPCR, CPOL);   // 0=sck active high, 1=sck active low
        CLRBIT(LPC_SPIF->SPCR, SPIE);   // 0=no interrupt, 1=interrupt
 
        // Chip Select
        SetGpioDirection(GPIO1_0,GPIO_OUT);
        SetGpioValue(GPIO1_0,0);
        
}



UInt8 SendByteToSPI(UInt8 outgoing)
{
	UInt8 incoming;
	LPC_SPIF->SPDR = outgoing;
	while (!(LPC_SPIF->SPSR & BIT(SPIF)));
	incoming = LPC_SPIF->SPDR;
        
	return incoming;
}


void SendBufferToSPI(UInt8 * buffer, UInt32 length)
{
    UInt32 i;
    for(i=0; i<length; i++)
    {
        SendByteToSPI(buffer[i]);
    }
}


UInt8 GetByteFromSPI(void)
{
    return SendByteToSPI(0x00);
}

void GetBufferFromSPI(UInt8 * buffer, UInt32 size)
{
    UInt32 i;
    for (i=0; i<size; i++)
    {
        buffer[i] = GetByteFromSPI();
    }
}
