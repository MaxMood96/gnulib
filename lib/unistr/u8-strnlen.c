/* Determine bounded length of UTF-8 string.
   Copyright (C) 1999, 2002, 2006, 2009-2025 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2002.

   This file is free software.
   It is dual-licensed under "the GNU LGPLv3+ or the GNU GPLv2+".
   You can redistribute it and/or modify it under either
     - the terms of the GNU Lesser General Public License as published
       by the Free Software Foundation, either version 3, or (at your
       option) any later version, or
     - the terms of the GNU General Public License as published by the
       Free Software Foundation; either version 2, or (at your option)
       any later version, or
     - the same dual license "the GNU LGPLv3+ or the GNU GPLv2+".

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License and the GNU General Public License
   for more details.

   You should have received a copy of the GNU Lesser General Public
   License and of the GNU General Public License along with this
   program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Ensure strnlen() gets declared.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif

#include <config.h>

/* Specification.  */
#include "unistr.h"

#if __GLIBC__ >= 2 || defined __UCLIBC__

# include <string.h>

size_t
u8_strnlen (const uint8_t *s, size_t maxlen)
{
  return strnlen ((const char *) s, maxlen);
}

#else

# define FUNC u8_strnlen
# define UNIT uint8_t
# include "u-strnlen.h"

#endif
