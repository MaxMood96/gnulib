# copysignf.m4
# serial 4
dnl Copyright (C) 2011-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

AC_DEFUN([gl_FUNC_COPYSIGNF],
[
  AC_REQUIRE([gl_MATH_H_DEFAULTS])
  AC_REQUIRE([AC_CANONICAL_HOST])

  dnl Persuade glibc <math.h> to declare copysignf().
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])

  dnl Determine COPYSIGNF_LIBM.
  gl_MATHFUNC([copysignf], [float], [(float, float)],
    [extern
     #ifdef __cplusplus
     "C"
     #endif
     float copysignf (float, float);
    ])
  if test $gl_cv_func_copysignf_no_libm = yes \
     || test $gl_cv_func_copysignf_in_libm = yes; then
    HAVE_COPYSIGNF=1
    dnl Also check whether it's declared.
    dnl IRIX 6.5 has copysignf() in libm but doesn't declare it in <math.h>.
    AC_CHECK_DECL([copysignf], , [HAVE_DECL_COPYSIGNF=0], [[#include <math.h>]])
  else
    HAVE_COPYSIGNF=0
    HAVE_DECL_COPYSIGNF=0
    dnl On HP-UX 11.31/ia64, cc has a built-in for copysignf that redirects
    dnl to the symbol '_copysignf', defined in libm, not libc.
    case "$host_os" in
      hpux*) COPYSIGNF_LIBM='-lm' ;;
      *)     COPYSIGNF_LIBM= ;;
    esac
  fi
  AC_SUBST([COPYSIGNF_LIBM])
])
