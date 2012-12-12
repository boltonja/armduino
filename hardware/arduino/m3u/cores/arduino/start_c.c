/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/*
 * This file is a modified version of a file obtained from
 * CodeSourcery Inc. (now part of Mentor Graphics Corp.), in which the
 * following text appeared:
 *
 * Copyright (c) 2006, 2007 CodeSourcery Inc
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

#include <stddef.h>
#include <stdint.h>
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;

extern void __libc_init_array(void);
extern int main(int, char**, char**);
extern void init(void);

void __attribute__((noreturn)) start_c2(void) {
    uint32_t *pSrc, *pDest;


    /* Initialize the relocate segment */
    pSrc = &_etext;
    pDest = &_srelocate;

    if (pSrc != pDest) {
        for (; pDest < &_erelocate;) {
            *pDest++ = *pSrc++;
        }
    }

    /* Clear the zero segment */
    for (pDest = &_szero; pDest < &_ezero;) {
        *pDest++ = 0;
    }
    init();
    /* Initialize the C library */
    __libc_init_array();

    /* Branch to main function */
    main(0, 0, 0);

    /* Infinite loop */
    while (1);
}
void __attribute__((noreturn)) start_c(void) {
    __asm__ volatile(".fnstart \n\t"
                     "ldr   r1, =_estack \n\t"
                     "mov   sp, r1 \n\t"
                     "ldr r1,=start_c2 \n\t"
                     "bx r1 \n\t"
                     ".pool \n\t"
                     ".cantunwind \n\t"
                     ".fnend"
            );
}


