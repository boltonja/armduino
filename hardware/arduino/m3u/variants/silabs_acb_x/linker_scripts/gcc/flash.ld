/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following condition is met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
SEARCH_DIR(.)

/* Memory Spaces Definitions */
MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
  rom (rx)  : ORIGIN = 2048, LENGTH = 256K - 2048
}

/*
 * These force the linker to search for vector table symbols.
 *
 * These symbols vary by STM32 family (and also within families).
 * It's up to the build system to configure the link's search path
 * properly for the target MCU.
 */
EXTERN(__msp_init)
EXTERN(__exc_reset)
EXTERN(__exc_nmi)
EXTERN(__exc_hardfault)
EXTERN(__exc_memmanage)
EXTERN(__exc_busfault)
EXTERN(__exc_usagefault)
EXTERN(__stm32reservedexception7)
EXTERN(__stm32reservedexception8)
EXTERN(__stm32reservedexception9)
EXTERN(__stm32reservedexception10)
EXTERN(__exc_svc)
EXTERN(__exc_debug_monitor)
EXTERN(__stm32reservedexception13)
EXTERN(__exc_pendsv)
EXTERN(__exc_systick)

EXTERN(__irq_wwdg)
EXTERN(__irq_exti0)
EXTERN(__irq_exti1)
EXTERN(__irq_rtc_wkup)   
EXTERN(__irq_dma1_stream0)
EXTERN(__irq_dma1_stream1)
EXTERN(__irq_dma1_stream2)
EXTERN(__irq_dma1_stream3)
EXTERN(__irq_dma1_stream4)
EXTERN(__irq_dma1_stream5)
EXTERN(__irq_dma1_stream6)
EXTERN(__irq_dma1_stream7)
EXTERN(__irq_dma1_stream8)
EXTERN(__irq_dma1_stream9)
EXTERN(__irq_dma1_stream10)
EXTERN(__irq_dma1_stream11)
EXTERN(__irq_dma1_stream12)
EXTERN(__irq_dma1_stream13)
EXTERN(__irq_dma1_stream14)
EXTERN(__irq_dma1_stream15)
EXTERN(__irq_tim1_low)
EXTERN(__irq_tim1_high)
EXTERN(__irq_tim2_low)
EXTERN(__irq_tim2_high)
EXTERN(__irq_epca1)
EXTERN(__irq_pca1)
EXTERN(__irq_pca2)
EXTERN(__irq_usart1)
EXTERN(__irq_usart2)
EXTERN(__irq_spi1)
EXTERN(__irq_spi2)
EXTERN(__irq_spi3)
EXTERN(__irq_i2c1)
EXTERN(__irq_i2c2)
EXTERN(__irq_usb)
EXTERN(__irq_adc1)
EXTERN(__irq_adc2)      
EXTERN(__irq_cmp1)
EXTERN(__irq_cmp2)
EXTERN(__irq_capsense)
EXTERN(__irq_i2s1rx)
EXTERN(__irq_i2s1tx)
EXTERN(__irq_aes)
EXTERN(__irq_vddlow)
EXTERN(__irq_rtcfail)
EXTERN(__irq_pmatch)
EXTERN(__irq_uart1)
EXTERN(__irq_uart2)
EXTERN(__irq_dac1)
EXTERN(__irq_dac2)
EXTERN(__irq_lptimer)
EXTERN(__irq_pll)
EXTERN(__irq_vbusinvalid)
EXTERN(__irq_vreglow)

/* C runtime initialization function. */
EXTERN(start_c)

/* main entry point */
EXTERN(main)

/* Initial stack pointer value. */
EXTERN(__msp_init)
PROVIDE(__msp_init = ORIGIN(ram) + LENGTH(ram));

/* Reset vector and chip reset entry point */
EXTERN(start_c)
ENTRY(start_c)
PROVIDE(__exc_reset = start_c);

/* STM32 vector table. */
EXTERN(__sim3_vector_table)

/* Section Definitions */
SECTIONS
{        
    .text :
    {
        . = ALIGN(4);
        _sfixed = .;
        *(.sim3.interrupt_vector)
        *(.text .text.* .gnu.linkonce.t.*)
        *(.glue_7t) *(.glue_7)
        *(.rodata .rodata* .gnu.linkonce.r.*)
        *(.ARM.extab* .gnu.linkonce.armextab.*)

        /* Support C constructors, and C destructors in both user code
           and the C library. This also provides support for C++ code. */
        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))

        . = ALIGN(4);
        _efixed = .;            /* End of text section */
    } > rom

    /* .ARM.exidx is sorted, so has to go in its own output section.  */
    PROVIDE_HIDDEN (__exidx_start = .);
    .ARM.exidx :
    {
      *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > rom
    PROVIDE_HIDDEN (__exidx_end = .);

    . = ALIGN(4);
    _etext = .;

    .relocate : AT (_etext)
    {
        . = ALIGN(4);
        _srelocate = .;
        *(.ramfunc .ramfunc.*);
        *(.data .data.*);
        . = ALIGN(4);
        _erelocate = .;
    } > ram

    /* .bss section which is used for uninitialized data */
    .bss ALIGN(4) (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = . ;
        _szero = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = . ;
        _ezero = .;
    } > ram

    . = ALIGN(4);
    _end = . ;

    /* .stack_dummy section doesn't contains any symbols. It is only
       used for linker to calculate size of stack sections, and assign
       values to stack symbols later */
    .stack_dummy :
    {
        *(.stack*)
    } > ram

    /* Set stack top to end of ram, and stack limit move down by
     * size of stack_dummy section */
    __StackTop = ORIGIN(ram) + LENGTH(ram);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    PROVIDE(_sstack = __StackLimit);
    PROVIDE(_estack = __StackTop);
}
