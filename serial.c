#include "serial.h"
#include "Cypress/Fx2.h"
#include "Cypress/fx2regs.h"

unsigned int counter = 0;
unsigned short txbuf;
unsigned char sendcount;
unsigned char is_sending;

void boad_generator(void) interrupt 1 using 1
{
    TR0 = 0;
    TH0 = BODE_CNT_VALUE / 256;
    TL0 = BODE_CNT_VALUE % 256;
    TR0 = 1;

    if (!is_sending)
        return;
    
    IOA = txbuf & 0x01;
    txbuf >>= 1;
    if(!--sendcount)
    {
        is_sending = 0;
    }            
}

void uart_init()
{
        
    TMOD = 0x01;                /* Enable Timer0 in 16 bit mode */
    CKCON |= bmBIT3;            /* CLKOUT/4  for TMR0 */    
    
    TH0 = BODE_CNT_VALUE / 256;
    TL0 = BODE_CNT_VALUE % 256;
    
    TR0 = 1;
    ET0 = 1;
    PT0 = 0;
    
    OEA = 0x03;                 /* PA.0 and PA.1 as output */
    EA = 1;
}

void printchar(char c)
{
    while(is_sending);
    txbuf = (c << 1) | 0x200;
    sendcount = 10;
    is_sending = 1;
    EA = 1;    
}

void print(char *msg)
{
    while(*msg)
    {
        printchar(*msg);
        msg++;
    }
}

void println(char *msg)
{
    while(*msg)
    {
        printchar(*msg);
        msg++;
    } 
    printchar(13);
}
 