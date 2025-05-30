# strings_h.m4
# serial 14
dnl Copyright (C) 2007, 2009-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

# Configure a replacement for <strings.h>.

AC_DEFUN_ONCE([gl_STRINGS_H],
[
  dnl Ensure to expand the default settings once only, before all statements
  dnl that occur in other macros.
  AC_REQUIRE([gl_STRINGS_H_DEFAULTS])

  gl_CHECK_NEXT_HEADERS([strings.h])
  if test $ac_cv_header_strings_h = yes; then
    HAVE_STRINGS_H=1
  else
    HAVE_STRINGS_H=0
  fi
  AC_SUBST([HAVE_STRINGS_H])

  dnl Check for declarations of anything we want to poison if the
  dnl corresponding gnulib module is not in use.
  gl_WARN_ON_USE_PREPARE([[
    /* Minix 3.1.8 has a bug: <sys/types.h> must be included before
       <strings.h>.  */
    #include <sys/types.h>
    #include <strings.h>
    ]], [ffs strcasecmp strcasecmp_l strncasecmp strncasecmp_l])
])

# gl_STRINGS_MODULE_INDICATOR([modulename])
# sets the shell variable that indicates the presence of the given module
# to a C preprocessor expression that will evaluate to 1.
# This macro invocation must not occur in macros that are AC_REQUIREd.
AC_DEFUN([gl_STRINGS_MODULE_INDICATOR],
[
  dnl Ensure to expand the default settings once only.
  gl_STRINGS_H_REQUIRE_DEFAULTS
  gl_MODULE_INDICATOR_SET_VARIABLE([$1])
])

# Initializes the default values for AC_SUBSTed shell variables.
# This macro must not be AC_REQUIREd.  It must only be invoked, and only
# outside of macros or in macros that are not AC_REQUIREd.
AC_DEFUN([gl_STRINGS_H_REQUIRE_DEFAULTS],
[
  m4_defun(GL_MODULE_INDICATOR_PREFIX[_STRINGS_H_MODULE_INDICATOR_DEFAULTS], [
    gl_MODULE_INDICATOR_INIT_VARIABLE([GNULIB_FFS])
    gl_MODULE_INDICATOR_INIT_VARIABLE([GNULIB_STRCASECMP])
    gl_MODULE_INDICATOR_INIT_VARIABLE([GNULIB_STRCASECMP_L])
    gl_MODULE_INDICATOR_INIT_VARIABLE([GNULIB_STRNCASECMP])
    gl_MODULE_INDICATOR_INIT_VARIABLE([GNULIB_STRNCASECMP_L])
  ])
  m4_require(GL_MODULE_INDICATOR_PREFIX[_STRINGS_H_MODULE_INDICATOR_DEFAULTS])
  AC_REQUIRE([gl_STRINGS_H_DEFAULTS])
])

AC_DEFUN([gl_STRINGS_H_DEFAULTS],
[
  dnl Assume proper GNU behavior unless another module says otherwise.
  HAVE_FFS=1;              AC_SUBST([HAVE_FFS])
  HAVE_STRCASECMP=1;       AC_SUBST([HAVE_STRCASECMP])
  HAVE_STRCASECMP_L=1;     AC_SUBST([HAVE_STRCASECMP_L])
  HAVE_STRNCASECMP=1;      AC_SUBST([HAVE_STRNCASECMP])
  HAVE_STRNCASECMP_L=1;    AC_SUBST([HAVE_STRNCASECMP_L])
  HAVE_DECL_STRNCASECMP=1; AC_SUBST([HAVE_DECL_STRNCASECMP])
  REPLACE_STRCASECMP=0;    AC_SUBST([REPLACE_STRCASECMP])
  REPLACE_STRCASECMP_L=0;  AC_SUBST([REPLACE_STRCASECMP_L])
  REPLACE_STRNCASECMP=0;   AC_SUBST([REPLACE_STRNCASECMP])
  REPLACE_STRNCASECMP_L=0; AC_SUBST([REPLACE_STRNCASECMP_L])
])
