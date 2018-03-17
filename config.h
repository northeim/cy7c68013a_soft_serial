#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CPU_CLK_12MHZ   12000000L
#define CPU_CLK_24MHZ   24000000L
#define CPU_CLK_48MHZ   48000000L


#define CPU_CLK CPU_CLK_48MHZ           // CPU clock;

                    
#if CPU_CLK == CPU_CLK_12MHZ            // CPUCS PD;
    #define CPUPD   0x00                
#endif

#if CPU_CLK == CPU_CLK_24MHZ
    #define CPUPD   (1 << 3)
#endif

#if CPU_CLK == CPU_CLK_48MHZ
    #define CPUPD   (1 << 4)
#endif

#endif