/* Next grapheme cluster length test.
   Copyright (C) 2010-2025 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Ben Pfaff <blp@cs.stanford.edu>, 2010. */

#include <config.h>

/* Specification. */
#include <unigbrk.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "macros.h"

static void
test_u16_grapheme_next (size_t len, ...)
{
  const uint16_t *next;
  uint16_t s[16];
  va_list args;
  size_t n;

  va_start (args, len);
  n = 0;
  for (;;)
    {
      int unit = va_arg (args, int);
      if (unit == -1)
        break;
      else if (n >= sizeof s / sizeof *s)
        abort ();

      s[n++] = unit;
    }
  va_end (args);

  next = u16_grapheme_next (s, s + n);
  if (next != s + len)
    {
      size_t i;

      if (next == NULL)
        fputs ("u16_grapheme_next returned NULL", stderr);
      else
        fprintf (stderr, "u16_grapheme_next skipped %tu units", next - s);
      fprintf (stderr, ", expected %zu:\n", len);
      for (i = 0; i < n; i++)
        fprintf (stderr, " %04x", s[i]);
      putc ('\n', stderr);
      fflush (stderr);
      abort ();
    }
}

int
main (void)
{
  static const uint16_t s[] = { 'a', 'b', 'c' };

  /* Empty string. */
  ASSERT (u16_grapheme_next (NULL, NULL) == NULL);
  ASSERT (u16_grapheme_next (s, s) == NULL);

  /* Standalone 1-unit graphemes.  */
  test_u16_grapheme_next (1, 'a', -1);
  test_u16_grapheme_next (1, 'a', 'b', -1);
  test_u16_grapheme_next (1, 'a', 'b', 'c', -1);

  /* Multi-unit, single code point graphemes. */
#define HIRAGANA_A 0x3042       /* あ: Hiragana letter 'a'. */
  test_u16_grapheme_next (1, HIRAGANA_A, -1);
  test_u16_grapheme_next (1, HIRAGANA_A, 'x', -1);
  test_u16_grapheme_next (1, HIRAGANA_A, HIRAGANA_A, -1);

  /* Combining accents. */
#define GRAVE 0x0300            /* Combining grave accent. */
#define ACUTE 0x0301            /* Combining acute accent. */
  test_u16_grapheme_next (2, 'e', ACUTE, -1);
  test_u16_grapheme_next (3, 'e', ACUTE, GRAVE, -1);
  test_u16_grapheme_next (2, 'e', ACUTE, 'x', -1);
  test_u16_grapheme_next (2, 'e', ACUTE, 'e', ACUTE, -1);

  /* CR LF handling.  */
  test_u16_grapheme_next (2, '\r', '\n', 'd', -1);

  /* Emoji modifier / ZWJ sequence. */
  test_u16_grapheme_next (5, 0x2605, 0x0305, 0x0347, 0x200D, 0x2600, -1);

  /* Regional indicators. */
  test_u16_grapheme_next (4, 0xD83C, 0xDDE9, 0xD83C, 0xDDEA, 0xD83C, 0xDDEB, 0xD83C, 0xDDF7, -1);

  /* Surrogate pairs. */
  test_u16_grapheme_next (2, 0xd83d, 0xde10, -1); /* 😐: neutral face. */
  test_u16_grapheme_next (3, 0xd83d, 0xde10, GRAVE, -1);

  return test_exit_status;
}
