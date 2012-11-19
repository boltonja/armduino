/*! \file *********************************************************************
 *
 * \brief Provides the low-level initialization functions that called 
 * on chip startup.
 *
 * $asf_license$
 *
 * \par Purpose
 *
 * This file provides basic support for Cortex-M processor based 
 * microcontrollers.
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ******************************************************************************/

#include "sam3xa.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/* Clock settings (84MHz) */
#define SYS_BOARD_OSCOUNT   (CKGR_MOR_MOSCXTST(0x8))
#define SYS_BOARD_PLLAR     (CKGR_PLLAR_ONE \
							| CKGR_PLLAR_MULA(0xdUL) \
							| CKGR_PLLAR_PLLACOUNT(0x3fUL) \
							| CKGR_PLLAR_DIVA(0x1UL))
#define SYS_BOARD_MCKR      (PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK)

/* Clock Definitions */
#define SYS_UTMIPLL     		(480000000UL)	/* UTMI PLL frequency */

#define SYS_CKGR_MOR_KEY_VALUE	CKGR_MOR_KEY(0x37) /* Key to unlock MOR register */

/* FIXME: should be generated by sock */
uint32_t SystemCoreClock = CHIP_FREQ_MAINCK_RC_4MHZ;

/**
 * \brief Setup the microcontroller system.
 * Initialize the System and update the SystemFrequency variable.
 */
void SystemInit(void)
{

}

void SystemCoreClockUpdate(void)
{

}

/** 
 * Initialize flash.
 */
void system_init_flash(uint32_t dw_clk)
{

}

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */
