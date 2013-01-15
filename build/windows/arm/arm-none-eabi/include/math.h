/* (c) Code Red Technologies. dTR */
#if !defined(__CR1_MATH_H__)
#  define __CR1_MATH_H__
#  if defined(__REDLIB__)
#    include <redlib/math.h>
#  else
#    include <newlib_inc/math.h>
#    if !defined(__NEWLIB__) && !defined(__LIBRARY_WARNING_MESSAGE__)
#      warning "Either __NEWLIB__ or __REDLIB__ should be defined when using the C library. Defaulting to __NEWLIB__"
#      define __LIBRARY_WARNING_MESSAGE__
#     endif
#  endif
#endif
