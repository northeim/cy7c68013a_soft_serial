#ifndef _SERIAL_H_
#define _SERIAL_H_


#define BODE_48_1200    63035 //55535
#define BODE_12_1200    63035
//extern counter;

void uart_init();
void printchar(char c);
void print_debug(char *msg);

#endif