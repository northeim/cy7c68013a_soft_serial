//#define ALLOCATE_EXTERN

#include "Cypress/Fx2.h"
#include "Cypress/fx2regs.h"
#include "serial.h"
#include "float.h"
#include <limits.h>
#include <stdio.h>
#include "config.h"

#define TICKS_IN_SECOND 1000
#define TICK_1MS        (65535 - CPU_CLK/12/TICKS_IN_SECOND)

/* String constatnts */
#define FLOAT_MULTIPLICATION    "*** Float multiplicaion ***"
#define FLOAT_ADDITION          "*** Float addition ***"
#define FLOAT_SUBSTRUCTION      "*** Float substraction ***"
#define FLOAT_DIVISION          "*** Float division ***"
#define AVERAGE_FLOPS           "*** FLOPS avg ***"

#define NUM_ITERATION   10000

float mult_processing(float seed, long int iteration);
float add_processing(float seed, long int iteration);
float sub_processing(float seed, long int iteration);
float div_processing(float seed, long int iteration);

volatile BYTE CPUCS             _at_ 0xE600;

unsigned long int tick = 0;
unsigned int tickH = 0;
unsigned char clockupdate = 0;

/* Timer 1 interrupt handler */
void timer_1(void) interrupt 3
{
    TH1 = TICK_1MS / 256;
    TL1 = TICK_1MS % 256;
    
    tick++;
    clockupdate = 1; 
    if (tick == 0)
    {
        tickH++;
    }
}

/* Get value of current tick timer */
unsigned long int getTick()
{
    unsigned long int tmpTick;
    do
    {
        clockupdate = 0;
        tmpTick = tick;
    } while (clockupdate);
        
    return tmpTick;
}

unsigned long int before;
unsigned long int after;
char num_str[255];
float add_result;
float sub_result;
float mult_result;
float div_result;
float average;
long int ii;

void main(void)
{   
    CPUCS &= ~ (bmCLKSPD0 | bmCLKSPD1);
    CPUCS |= CPUPD;
    
    uart_init();
    
    TMOD |= (1 << 4);                   /* Enable timer 1 for count system ticks */
    TH1 = CPU_CLK_12MHZ / 256;          /* Set system tick = 1 ms */
    TL1 = CPU_CLK_12MHZ % 256;
    
    TR1 = 1;
    ET1 = 1;
    PT1 = 0;
    
    /* Measure value of FLOPS/s when there is float multiplication */
    
    println(FLOAT_ADDITION);  
    before = getTick();
    add_processing(1.3, NUM_ITERATION);
    after = getTick();    
    add_result = (((NUM_ITERATION*1.0)/(after-before)))*TICKS_IN_SECOND;
    sprintf(num_str, "FLOPS per second = %.2f flops/s", add_result);
    println(num_str); 
    
    println(FLOAT_SUBSTRUCTION);  
    before = getTick();
    sub_processing(1.3, NUM_ITERATION);
    after = getTick();
    sub_result = (((NUM_ITERATION*1.0)/(after-before)))*TICKS_IN_SECOND;
    sprintf(num_str, "FLOPS per second = %.2f flops/s", sub_result);
    println(num_str);
    
    println(FLOAT_MULTIPLICATION);
    before = getTick();
    mult_processing(0.2, NUM_ITERATION);
    after = getTick();
    mult_result = (((NUM_ITERATION*1.0)/(after-before)))*TICKS_IN_SECOND;
    sprintf(num_str, "FLOPS per second = %.2f flops/s", mult_result);
    println(num_str);
    
    println(FLOAT_DIVISION);  
    before = getTick();
    div_processing(20.0, NUM_ITERATION);
    after = getTick();
    div_result = (((NUM_ITERATION*1.0)/(after-before)))*TICKS_IN_SECOND;
    sprintf(num_str, "FLOPS per second = %.2f flops/s", div_result);
    println(num_str);  
    
    average = (add_result + sub_result + mult_result + div_result)/4;
    println(AVERAGE_FLOPS);  
    sprintf(num_str, "FLOPS per second = %.2f flops/s", average);
    println(num_str); 
    
    // Blink led every second;
    before = getTick();  
    
    while(1)
    {   
        after = getTick();
        if (( after - before ) == 1000)
        {
            IOA ^= (1<<1);
            before = after;
        }        
        
    }
    
}

float mult_processing(float seed, long int iteration)
{
    float data initial = seed;
    long int data i = iteration;
    while(i--)
    {
        initial *= 0.2;
    }    
    return initial;    
}

float add_processing(float seed, long int iteration)
{
    float data initial = seed;
    long int data i = iteration;
    while(i--)
    {
        initial += 0.2;
    }    
    return initial;    
}

float sub_processing(float seed, long int iteration)
{
    float data initial = seed;
    long int data i = iteration;
    while(i--)
    {
        initial -= 0.2;
    }    
    return initial;    
}

float div_processing(float seed, long int iteration)
{
    float data initial = seed;
    long int data i = iteration;
    while(i--)
    {
        initial /= 0.2;
    }    
    return initial;    
}