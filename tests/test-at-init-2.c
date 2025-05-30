/* Test of computed initialization.
   Copyright (C) 2025 Free Software Foundation, Inc.

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
#include "at-init.h"

static int sum_of_squares;

AT_INIT (init_squares);
#ifdef __SUNPRO_C
# pragma init (init_squares)
#endif

static void
init_squares (void)
{
  int i;

  sum_of_squares = 0;
  for (i = 0; i <= 100; i++)
    sum_of_squares += i * i;
}

int
get_squares (void)
{
  return sum_of_squares;
}
