#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "Cypress/Fx2.h"
#include "Cypress/fx2regs.h"

/* CPU Control and Status Register */
#define CLKPLL_12MHZ    (CPUCS &= ~(bmCLKSPD0 | bmCLKSPD1))
#define CLKPLL_24MHZ    (CPUCS = (CPUCS & (~bmCLKSPD1)) | bmCLKSPD0)
#define CLKPLL_48MHZ    (CPUCS = (CPUCS & (~bmCLKSPD0)) | bmCLKSPD1)

#endif