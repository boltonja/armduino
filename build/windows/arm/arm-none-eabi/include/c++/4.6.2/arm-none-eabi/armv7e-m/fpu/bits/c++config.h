/* (c) Code Red Technologies. dTR */
#if !defined(__CR2_C___4_6_2_ARM_NONE_EABI_ARMV7E_M_FPU_BITS_C__CONFIG_H__)
#  define __CR2_C___4_6_2_ARM_NONE_EABI_ARMV7E_M_FPU_BITS_C__CONFIG_H__
#  if defined(__REDLIB__)
#    include_next <c++/4.6.2/arm-none-eabi/armv7e-m/fpu/bits/c++config.h>
#  else
#    include <newlib_inc/c++/4.6.2/arm-none-eabi/armv7e-m/fpu/bits/c++config.h>
#    if !defined (__NEWLIB__) && !defined(__LIBRARY_WARNING_MESSAGE__)
#      warning "Either __NEWLIB__ or __REDLIB__ should be defined when using the C library. Defaulting to __NEWLIB__"
#      define __LIBRARY_WARNING_MESSAGE__
#    endif
#  endif
#endif
