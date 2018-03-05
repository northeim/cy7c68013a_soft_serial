#include "Cypress/Fx2.h"
#include "Cypress/fx2regs.h"
#include "serial.h"
//static float a = 2.0;

unsigned int tick = 0;
unsigned int tickH = 0;
unsigned char clockupdate = 0;

#pragma OT(0)
void timer_1(void) interrupt 3
{
    TH1 = 55535 / 256;
    TL1 = 55535 % 256;
    
    tick++;
    clockupdate = 1; 
    if (tick == 0)
    {
        tickH++;
    }
    
    
}
#pragma OT(0)
int getTick()
{
    unsigned int tmpTick;
    do
    {
        clockupdate = 0;
        tmpTick = tick;
    } while (clockupdate);
        
    return tmpTick;
}
#pragma OT(0)
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}


unsigned long i;
volatile float a;
unsigned int before;
unsigned int after;
char num_str[30];

#pragma OT(0)
void main(void)
{   
    uart_init();
    print_debug("Uart init.Ok.");
    
    TMOD |= (1 << 4);                /* Enable Timer0 in 16 bit mode */
    
    TH1 = 55535 / 256;
    TL1 = 55535 % 256;
    
    TR1 = 1;
    ET1 = 1;
    PT1 = 0;
    
    //a = 1.025;
    before = getTick();
    i = 10000000000;
    while(--i)
    {
        a = a + 0.25;
    }
    
    
    
    after = getTick();
    
    tostring(num_str, after-before);
    print_debug(num_str);
    tostring(num_str, tickH);
    print_debug(num_str);
    
    //init_clock();    
    //IOA = 0x00;
    print_debug("Entering while.ok.");
    
    while(1)
    {
        print_debug("Hello");
        
        
    }
    
}