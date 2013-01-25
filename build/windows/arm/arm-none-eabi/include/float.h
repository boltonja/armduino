/* (c) Code Red Technologies. dTNN */
#if !defined(__CR3_FLOAT_H__)
#  define __CR3_FLOAT_H__
#  if defined(__NEWLIB__)
#    include_next <float.h>
#  else
#    include <redlib/float.h>
#    if !defined (__REDLIB__) && !defined(__LIBRARY_WARNING_MESSAGE__)
#      warning "Either __NEWLIB__ or __REDLIB__ should be defined when using the C library. Defaulting to __REDLIB__"
#      define __LIBRARY_WARNING_MESSAGE__
#    endif
#  endif
#endif
