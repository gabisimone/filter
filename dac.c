/*
 * dac.c
 *
 */


#include "board.h"

/* P0.26 -> AOUT */
void dacInit(void)
{
	Chip_DAC_Init(LPC_DAC);  //inicializa DAC
#ifdef lpc4337_m4
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
#endif
}

void dacWrite(uint32_t v)
{
	Chip_DAC_UpdateValue(LPC_DAC, v);  //actualiza valor DAC
}
