/*
 * SystemInit.c
 *
 *  Created on: 17.09.2018
 *      Author: Proro
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx.h"

uint32_t SystemCoreClock = 4000000U;

const uint8_t  AHBPrescTable[16] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
const uint8_t  APBPrescTable[8] =  {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};
const uint32_t MSIRangeTable[12] = {100000U,   200000U,   400000U,   800000U,  1000000U,  2000000U, \
                                    4000000U, 8000000U, 16000000U, 24000000U, 32000000U, 48000000U};

void SystemInit(void)
{
	  /* FPU settings ------------------------------------------------------------*/
	  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
	  #endif

	  /* Reset the RCC clock configuration to the default reset state ------------*/
	  /* Set MSION bit */
	  RCC->CR |= RCC_CR_MSION;

	  /* Reset CFGR register */
	  RCC->CFGR = 0x00000000U;

	  /* Reset HSEON, CSSON , HSION, and PLLON bits */
	  RCC->CR &= 0xEAF6FFFFU;

	  /* Reset PLLCFGR register */
	  RCC->PLLCFGR = 0x00001000U;

	  /* Reset HSEBYP bit */
	  RCC->CR &= 0xFFFBFFFFU;

	  /* Disable all interrupts */
	  RCC->CIER = 0x00000000U;

	  /* Configure the Vector Table location add offset address ------------------*/
	#ifdef VECT_TAB_SRAM
	  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
	#else
	  SCB->VTOR = FLASH_BASE; /* Vector Table Relocation in Internal FLASH */
	#endif

}

void SystemCoreClockUpdate(void)
{
  uint32_t tmp = 0U, msirange = 0U, pllvco = 0U, pllr = 2U, pllsource = 0U, pllm = 2U;

  /* Get MSI Range frequency--------------------------------------------------*/
  if((RCC->CR & RCC_CR_MSIRGSEL) == RESET)
  { /* MSISRANGE from RCC_CSR applies */
    msirange = (RCC->CSR & RCC_CSR_MSISRANGE) >> 8U;
  }
  else
  { /* MSIRANGE from RCC_CR applies */
    msirange = (RCC->CR & RCC_CR_MSIRANGE) >> 4U;
  }
  /*MSI frequency range in HZ*/
  msirange = MSIRangeTable[msirange];

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case 0x00:  /* MSI used as system clock source */
      SystemCoreClock = msirange;
      break;

    case 0x04:  /* HSI used as system clock source */
      SystemCoreClock = 16000000U;
      break;

    case 0x08:  /* HSE used as system clock source */
      SystemCoreClock = 8000000U;
      break;

    case 0x0C:  /* PLL used as system clock  source */
      /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
         SYSCLK = PLL_VCO / PLLR
         */
      pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
      pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> 4U) + 1U ;

      switch (pllsource)
      {
        case 0x02:  /* HSI used as PLL clock source */
          pllvco = (16000000U / pllm);
          break;

        case 0x03:  /* HSE used as PLL clock source */
          pllvco = (8000000U / pllm);
          break;

        default:    /* MSI used as PLL clock source */
          pllvco = (msirange / pllm);
          break;
      }
      pllvco = pllvco * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 8U);
      pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> 25U) + 1U) * 2U;
      SystemCoreClock = pllvco/pllr;
      break;

    default:
      SystemCoreClock = msirange;
      break;
  }
  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4U)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}


#ifdef __cplusplus
}
#endif
