/* Test of wmemmove() function.
   Copyright (C) 2024 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

/* Specification.  */
#include <wchar.h>

#include <stddef.h>

#include "macros.h"

/* Test the library, not the compiler+library.  */
static wchar_t *
lib_wmemmove (wchar_t *s1, wchar_t const *s2, size_t n)
{
  return wmemmove (s1, s2, n);
}
static wchar_t *(*volatile volatile_wmemmove) (wchar_t *, wchar_t const *,
                                               size_t)
  = lib_wmemmove;
#undef wmemmove
#define wmemmove volatile_wmemmove

int
main (void)
{
  /* Test zero-length operations on NULL pointers, allowed by
     <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3322.pdf>.  */

  ASSERT (wmemmove (NULL, L"x", 0) == NULL);

  {
    wchar_t y[1];
    ASSERT (wmemmove (y, NULL, 0) == y);
  }

  return test_exit_status;
}