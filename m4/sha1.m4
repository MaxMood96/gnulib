# sha1.m4
# serial 12
dnl Copyright (C) 2002-2006, 2008-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

AC_DEFUN([gl_SHA1],
[
  dnl Prerequisites of lib/sha1.c.
  AC_REQUIRE([gl_BIGENDIAN])

  dnl Determine HAVE_OPENSSL_SHA1 and LIB_CRYPTO
  gl_CRYPTO_CHECK([SHA1])
])
