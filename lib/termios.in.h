/* Substitute for and wrapper around <termios.h>.
   Copyright (C) 2010-2025 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#ifndef _@GUARD_PREFIX@_TERMIOS_H

#if __GNUC__ >= 3
@PRAGMA_SYSTEM_HEADER@
#endif
@PRAGMA_COLUMNS@

/* On HP-UX 11.00, some of the function declarations in <sys/termio.h>,
   included by <termios.h>, are not protected by extern "C".  Enforce
   "C" linkage for these functions nevertheless.  */
#if defined __hpux && defined __cplusplus
# include <sys/types.h>
# include <sys/ioctl.h>
extern "C" {
# include <sys/termio.h>
}
#endif

/* The include_next requires a split double-inclusion guard.  */
#if @HAVE_TERMIOS_H@
# @INCLUDE_NEXT@ @NEXT_TERMIOS_H@
#endif

#ifndef _@GUARD_PREFIX@_TERMIOS_H
#define _@GUARD_PREFIX@_TERMIOS_H

/* This file uses GNULIB_POSIXCHECK, HAVE_RAW_DECL_*.  */
#if !_GL_CONFIG_H_INCLUDED
 #error "Please include config.h first."
#endif

/* Get pid_t.  */
#include <sys/types.h>

#if ! @TERMIOS_H_DEFINES_STRUCT_WINSIZE@
/* On glibc.  */
# if @SYS_IOCTL_H_DEFINES_STRUCT_WINSIZE@
#  include <sys/ioctl.h>
# else
/* On Windows.  */
#  if !GNULIB_defined_struct_winsize
struct winsize
{
  unsigned short ws_row;
  unsigned short ws_col;
};
#   define GNULIB_defined_struct_winsize 1
#  endif
# endif
#endif

/* The definitions of _GL_FUNCDECL_RPL etc. are copied here.  */

/* The definition of _GL_WARN_ON_USE is copied here.  */


/* Declare overridden functions.  */

#if @GNULIB_TCGETSID@
/* Return the session ID of the controlling terminal of the current process.
   The argument is a descriptor if this controlling terminal.
   Return -1, with errno set, upon failure.  errno = ENOSYS means that the
   function is unsupported.  */
# if !@HAVE_DECL_TCGETSID@
_GL_FUNCDECL_SYS (tcgetsid, pid_t, (int fd), );
# endif
_GL_CXXALIAS_SYS (tcgetsid, pid_t, (int fd));
_GL_CXXALIASWARN (tcgetsid);
#elif defined GNULIB_POSIXCHECK
# undef tcgetsid
# if HAVE_RAW_DECL_TCGETSID
_GL_WARN_ON_USE (tcgetsid, "tcgetsid is not portable - "
                 "use gnulib module tcgetsid for portability");
# endif
#endif


#endif /* _@GUARD_PREFIX@_TERMIOS_H */
#endif /* _@GUARD_PREFIX@_TERMIOS_H */
