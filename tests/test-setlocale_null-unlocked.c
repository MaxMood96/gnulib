/* Test of setlocale_null_r_unlocked function.
   Copyright (C) 2019-2025 Free Software Foundation, Inc.

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

/* Written by Bruno Haible <bruno@clisp.org>, 2019.  */

#include <config.h>

/* Specification.  */
#include "setlocale_null.h"

#include <locale.h>

/* Check that SETLOCALE_NULL_ALL_MAX is a constant expression.  */
static char buf[SETLOCALE_NULL_ALL_MAX];

int
main ()
{
  /* Check that setlocale_null_r_unlocked() can be used without any
     libraries.  */
  return setlocale_null_r_unlocked (LC_ALL, buf, sizeof (buf)) != 0;
}
