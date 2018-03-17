#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "config.h"

#define SERIAL_BODE_RATE    1200

#define BODE_CNT_VALUE      (65535 - CPU_CLK/4/SERIAL_BODE_RATE)

void uart_init();
void printchar(char c);
void print(char *msg);
void println(char *msg);

#endif