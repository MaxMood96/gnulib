/* getpagesize emulation for systems where it cannot be done in a C macro.

   Copyright (C) 2007, 2009-2025 Free Software Foundation, Inc.

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

/* Written by Bruno Haible and Martin Lambers.  */

#include <config.h>

/* Specification. */
#define _GL_GETPAGESIZE_INLINE _GL_EXTERN_INLINE
#include <unistd.h>

/* This implementation is only for native Windows systems.  */
#if defined _WIN32 && ! defined __CYGWIN__

# define WIN32_LEAN_AND_MEAN
# include <windows.h>

int
getpagesize (void)
{
  SYSTEM_INFO system_info;
  GetSystemInfo (&system_info);
  return system_info.dwPageSize;
}

#endif
